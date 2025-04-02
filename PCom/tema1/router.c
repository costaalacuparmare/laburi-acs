#include "queue.h"
#include "lib.h"
#include "protocols.h"
#include <arpa/inet.h>
#include <string.h>

// Router table
struct route_table_entry *rtable;
int rtable_len;

// ARP table
struct arp_table_entry *arp_table;
int arp_table_len;

// uses binary search to find the best route for a given IP
struct route_table_entry *get_best_route(uint32_t ip_dest) {
    int left = 0;
    int right = rtable_len - 1;
    struct route_table_entry *best_router = NULL;
    while (left <= right) {
        int mid = (left + right) / 2;
        if ((ip_dest & rtable[mid].mask) ==
            (rtable[mid].prefix & rtable[mid].mask)) {
            best_router = &rtable[mid];
            right = mid - 1;
        } else if (ntohl(ip_dest & rtable[mid].mask) >
                   ntohl(rtable[mid].prefix & rtable[mid].mask)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return best_router;
}

// searches the arp table to find the mac address of a given IP
struct arp_table_entry *get_arp_entry(uint32_t given_ip) {
    for (int i = 0; i < arp_table_len; i++) {
        if (arp_table[i].ip == given_ip) {
            return &arp_table[i];
        }
    }
    return NULL;
}

// send the packet back to the client if the router is the destination
void send_icmp_echo(char *buf, int interface, struct ether_header* eth_hdr,
                    size_t len) {
    // create new ETHERNET header to change the destination with the source
    struct ether_header new_eth_hdr;
    uint8_t dest_aux[6];

    memcpy(dest_aux, eth_hdr->ether_dhost, 6);
    memcpy(eth_hdr->ether_dhost, eth_hdr->ether_shost, 6);
    memcpy(new_eth_hdr.ether_shost, dest_aux, 6);

    struct icmphdr *icmp_hdr = (struct icmphdr *)
            (buf + sizeof(struct ether_header) + sizeof(struct iphdr));

    icmp_hdr->type = 0;
    icmp_hdr->code = 0;
    icmp_hdr->checksum = 0;
    icmp_hdr->un.gateway = 0;

    // compute the new checksum
    icmp_hdr->checksum = htons(checksum((uint16_t *)icmp_hdr,
                                        (sizeof(struct iphdr) + sizeof(struct icmphdr) + 8)));

    send_to_link(interface, buf, len);
}

// send an ICMP request (for Time Exceeded and Destination Unreachable errors)
void send_icmp_error(char *buf, int interface, struct iphdr *ip_hdr,
                     struct ether_header* eth_hdr, uint8_t type) {

    // create the new buffer to send with the ICMP request
    int new_buf_size = sizeof(struct ether_header) +
                       2 * sizeof(struct iphdr) + sizeof(struct icmphdr) + 8;
    // adds bites for the original buffer
    char new_buf[new_buf_size + 7 * 8];

    // create new ETHERNET header to change the destination with the source
    struct ether_header new_eth_hdr;

    get_interface_mac(interface, new_eth_hdr.ether_dhost);
    memcpy(new_eth_hdr.ether_dhost, eth_hdr->ether_shost, 6);
    new_eth_hdr.ether_type = eth_hdr->ether_type;

    // create new IPv4 header to modify the header for an ICMP request
    struct iphdr new_ip_hdr;

    new_ip_hdr.ttl = 255;
    new_ip_hdr.daddr = ip_hdr->saddr;
    new_ip_hdr.saddr = inet_addr(get_interface_ip(interface));
    new_ip_hdr.check = 0;
    new_ip_hdr.ihl = 5;
    new_ip_hdr.version = 4;
    new_ip_hdr.tos = 0;
    new_ip_hdr.tot_len = htons(new_buf_size - sizeof(struct ether_header));
    new_ip_hdr.frag_off = 0;
    new_ip_hdr.protocol = 1;
    new_ip_hdr.id = 1;

    // compute the new checksum
    new_ip_hdr.check = checksum((uint16_t *)&new_ip_hdr, sizeof(struct iphdr));

    /*
     * The new buffer for ICMP requests contains:
     * new ETHERNET header
     * new IPv4 header
     * old IPv4 header
     * the first 64 bites of the original buffer
     */
    memcpy(new_buf, &new_eth_hdr, sizeof(struct ether_header));
    memcpy(new_buf + sizeof(struct ether_header), &new_ip_hdr,
           sizeof(struct iphdr));
    memcpy(new_buf + (new_buf_size - sizeof(struct iphdr)), ip_hdr,
           sizeof(struct iphdr));
    memcpy(new_buf + new_buf_size,
           buf + sizeof(struct iphdr) + sizeof(struct ether_header), 64);

    // create the ICMP header with the appropriate code
    struct icmphdr *icmp_hdr = (struct icmphdr *)
            (new_buf + sizeof(struct ether_header) + sizeof(struct iphdr));

    icmp_hdr->type = type;
    icmp_hdr->code = 0;
    icmp_hdr->checksum = 0;
    icmp_hdr->un.gateway = 0;

    // compute the new checksum
    icmp_hdr->checksum = htons(checksum((uint16_t *)icmp_hdr,
                                        (sizeof(struct iphdr) + sizeof(struct icmphdr) + 8)));

    send_to_link(interface, new_buf, new_buf_size);
}

// send an ARP request to get next hop's mac address
void send_arp_request(struct route_table_entry *best_router) {

    // create the new buffer to send with the ARP request
    int new_buf_size = sizeof(struct ether_header) + sizeof(struct arp_header);
    char new_buf[MAX_PACKET_LEN];

    // create new ETHERNET header to send the ARP request
    struct ether_header new_eth_hdr;

    memset(new_eth_hdr.ether_dhost, 0xff, 6);
    get_interface_mac(best_router->interface, new_eth_hdr.ether_shost);
    new_eth_hdr.ether_type = htons(ARP_IDENTIFIER);

    // create new ARP header to send the ARP request
    struct arp_header *arp_hdr = malloc(sizeof(struct arp_header));

    arp_hdr->op = htons(ARP_REQUEST);
    arp_hdr->htype = htons(ARP_REQUEST);
    arp_hdr->ptype = htons(IPV4_IDENTIFIER);
    arp_hdr->hlen = 6;
    arp_hdr->plen = 4;
    arp_hdr->spa = inet_addr(get_interface_ip(best_router->interface));
    arp_hdr->tpa = best_router->next_hop;
    get_interface_mac(best_router->interface, arp_hdr->sha);
    memset(arp_hdr->tha, 0xff, 6);

    // copy the new ETHERNET header and the new ARP header to the new buffer
    memcpy(new_buf, &new_eth_hdr, sizeof(struct ether_header));
    memcpy(new_buf + sizeof(struct ether_header), arp_hdr,
           sizeof(struct arp_header));

    send_to_link(best_router->interface, new_buf, new_buf_size);
}

// send an ARP reply to the sender
void send_arp_reply(char *buf, int interface, struct ether_header *eth_hdr,
                    struct arp_header *arp_hdr, int len) {
    // check if the packet is for the router
    if (inet_addr(get_interface_ip(interface)) != arp_hdr->tpa) {
        printf("Ignored packet with bad IP\n");
        return;
    }

    // modify the new ETHERNET header to send the ARP reply
    memcpy(eth_hdr->ether_dhost, eth_hdr->ether_shost, 6);
    get_interface_mac(interface, eth_hdr->ether_shost);

    // modify the ARP header to send the ARP reply
    arp_hdr->op = htons(ARP_REPLY);
    memcpy(arp_hdr->tha, eth_hdr->ether_dhost, 6);
    get_interface_mac(interface, arp_hdr->sha);
    uint32_t aux = arp_hdr->tpa;
    arp_hdr->tpa = arp_hdr->spa;
    arp_hdr->spa = aux;

    // send the ARP reply with modified headers
    send_to_link(interface, buf, len);
}

// send the packets that were waiting for the MAC address
void send_waiting_packets(struct queue *packet_queue,
                          int len) {
    // create a new queue to store the packets that cannot be sent
    struct queue *new_packet_queue = queue_create();

    // send the packets that were waiting for the MAC address
    while (!queue_empty(packet_queue)) {
        // get the packet from the queue
        char *packet = queue_deq(packet_queue);

        // reconstruct the headers
        struct ether_header *packet_eth_hdr = (struct ether_header *) packet;
        struct iphdr *packet_ip_hdr = (struct iphdr *) (packet + sizeof(struct ether_header));

        // get the best route for the packet
        struct route_table_entry *best_router = get_best_route(packet_ip_hdr->daddr);

        // get the MAC address of the next hop
        struct arp_table_entry *best_mac = get_arp_entry(best_router->next_hop);

        // if the MAC address is not found, add back the packet
        if (best_mac == NULL) {
            queue_enq(new_packet_queue, packet);
            continue;
        }

        // send the packet to the next hop
        uint8_t *new_mac = best_mac->mac;
        get_interface_mac(best_router->interface, packet_eth_hdr->ether_shost);
        memcpy(packet_eth_hdr->ether_dhost, new_mac, 6);
        send_to_link(best_router->interface, packet, len);
    }

    // replace new_packet_queue with packet_queue
    while (!queue_empty(new_packet_queue)) {
        queue_enq(packet_queue, queue_deq(new_packet_queue));
    }

    free(new_packet_queue);
}

// compare function for qsort
int compare(const void *a, const void *b) {
    struct route_table_entry *entry_a = (struct route_table_entry *)a;
    struct route_table_entry *entry_b = (struct route_table_entry *)b;
    // if the prefixes are equal, compare the masks
    if (ntohl(entry_a->prefix & entry_a->mask) ==
        ntohl(entry_b->prefix & entry_b->mask))
        return ntohl(entry_a->mask) < ntohl(entry_b->mask);
    // if the prefixes are different, compare the prefixes
    return ntohl(entry_a->prefix & entry_a->mask) <
           ntohl(entry_b->prefix & entry_b->mask);
}

int main(int argc, char *argv[]) {
    char buf[MAX_PACKET_LEN];

    // Do not modify this line
    init(argc - 2, argv + 2);

    // allocate space for router table
    rtable = malloc(sizeof(struct route_table_entry) * 100000);
    DIE(rtable == NULL, "memory");
    rtable_len = read_rtable(argv[1], rtable);

    // sort the router table for the search for best route
    qsort(rtable, rtable_len, sizeof(struct route_table_entry),compare);

    // allocate space for arp table
    arp_table = malloc(sizeof(struct arp_table_entry) * 100000);
    DIE(arp_table == NULL, "memory");
    arp_table_len = 0;

    struct queue *packet_queue = queue_create();

    while (1) {
        int interface;
        size_t len;

        interface = recv_from_any_link(buf, &len);
        DIE(interface < 0, "recv_from_any_links");
        printf("We have received a packet\n");

        struct ether_header *eth_hdr = (struct ether_header *) buf;

        /* Note that packets received are in network order,
        any header field which has more than 1 byte will need to be
        converted to host order. For example, ntohs(eth_hdr->ether_type).
        The opposite is needed when sending a packet on the link, */

        // treats the IPv4 header
        if (ntohs(eth_hdr->ether_type) == IPV4_IDENTIFIER) {
            struct iphdr *ip_hdr = (struct iphdr *)
                    (buf + sizeof(struct ether_header));

            // verification of checksum
            uint16_t old_check = ip_hdr->check;
            ip_hdr->check = 0;

            if (ntohs(old_check) !=
                checksum((uint16_t *) ip_hdr, sizeof(struct iphdr))) {
                printf("Ignored packet with bad checksum\n");
                continue;
            }

            // ICMP Time Exceeded treated
            if (ip_hdr->ttl <= 1) {
                send_icmp_error(buf, interface, ip_hdr, eth_hdr,
                                ICMP_TIME_EXCEEDED);
                continue;
            }

            //checking if the router is the destination for the packet and that case resend the package back to the sender
            if (ip_hdr->daddr == inet_addr(get_interface_ip(interface))) {
                send_icmp_echo(buf, interface, eth_hdr, len);
                continue;
            }

            struct route_table_entry *best_router = get_best_route(
                    ip_hdr->daddr);

            // ICMP Destination Unreachable treated
            if (best_router == NULL) {
                send_icmp_error(buf, interface, ip_hdr, eth_hdr,
                                ICMP_DESTINATION_UNREACHABLE);
                continue;
            }

            // decrement the TTL and update the checksum
            ip_hdr->ttl--;
            ip_hdr->check = ~(~old_check + ~((uint16_t)(ip_hdr->ttl + 1)) +
                              (uint16_t) ip_hdr->ttl) - 1;

            // get the MAC address of the next hop
            struct arp_table_entry *best_mac = get_arp_entry(best_router->next_hop);

            // send an ARP request if the MAC address is not found
            if (best_mac == NULL) {
                // add the packet to the queue
                char *buf_copy = malloc(len);
                memcpy(buf_copy, buf, len);
                queue_enq(packet_queue, buf_copy);

                send_arp_request(best_router);
                continue;
            }

            // send the packet to the next hop
            memcpy(eth_hdr->ether_dhost, best_mac->mac, 6);
            get_interface_mac(best_router->interface, eth_hdr->ether_shost);
            send_to_link(best_router->interface, buf, len);
            continue;
        }

        // treats the ARP header
        if (ntohs (eth_hdr->ether_type) == ARP_IDENTIFIER) {
            struct arp_header *arp_hdr = (struct arp_header *)
                    (buf + sizeof(struct ether_header));

            // check if the packet is an ARP request
            if (ntohs(arp_hdr->op) == ARP_REQUEST) {
                send_arp_reply(buf, interface, eth_hdr, arp_hdr, len);
                continue;
            }

            // check if the packet is an ARP reply
            if (ntohs(arp_hdr->op) == ARP_REPLY) {
                // add the new entry to the ARP table
                arp_table[arp_table_len].ip = arp_hdr->spa;
                memcpy(arp_table[arp_table_len].mac, arp_hdr->sha, 6);
                arp_table_len++;

                send_waiting_packets(packet_queue, len);
                continue;
            }
        }
    }
}