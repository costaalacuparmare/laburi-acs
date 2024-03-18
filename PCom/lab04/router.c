#include <arpa/inet.h> /* ntoh, hton and inet_ functions */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "protocols.h"
#include <string.h>

/* Routing table */
struct route_table_entry *rtable;
int rtable_len;

/* Mac table */
struct mac_entry *mac_table;
int mac_table_len;

/*
 Returns a pointer (eg. &rtable[i]) to the best matching route, or NULL if there
 is no matching route.
*/
struct route_table_entry *get_best_route(uint32_t ip_dest) {
    for (int i = 0; i < rtable_len; i++) {
        if ((rtable[i].mask & ip_dest) == rtable[i].prefix) {
            return &rtable[i];
        }
    }
    return NULL;
}

struct mac_entry *get_mac_entry(uint32_t given_ip) {
    for (int i = 0; i < mac_table_len; i++) {
        if (mac_table[i].ip == given_ip) {
            return &mac_table[i];
        }
    }
	return NULL;
}

int main(int argc, char *argv[])
{
	int interface;
	char packet[MAX_LEN];
	int packet_len;

	/* Don't touch this */
	init();

	/* Code to allocate the MAC and route tables */
	rtable = malloc(sizeof(struct route_table_entry) * 100);
	/* DIE is a macro for sanity checks */
	DIE(rtable == NULL, "memory");

	mac_table = malloc(sizeof(struct  mac_entry) * 100);
	DIE(mac_table == NULL, "memory");
	
	/* Read the static routing table and the MAC table */
	rtable_len = read_rtable("rtable.txt", rtable);
	mac_table_len = read_mac_table(mac_table);

	while (1) {
		/* We call get_packet to receive a packet. get_packet returns
		the interface it has received the data from. And writes to
		len the size of the packet. */
		interface = recv_from_all_links(packet, &packet_len);
		DIE(interface < 0, "get_message");
		printf("We have received a packet\n");
		
		/* Extract the Ethernet header from the packet. Since protocols are
		 * stacked, the first header is the ethernet header, the next header is
		 * at m.payload + sizeof(struct ether_header) */
		struct ether_header *eth_hdr = (struct ether_header *) packet;
		struct iphdr *ip_hdr = (struct iphdr *)(packet + sizeof(struct ether_header));

		/* Check if we got an IPv4 packet */
		if (eth_hdr->ether_type != ntohs(ETHERTYPE_IP)) {
			printf("Ignored non-IPv4 packet\n");
			continue;
		}
        uint16_t old_check = ip_hdr->check;
        ip_hdr->check = 0;
        if (ntohs(old_check) != ip_checksum((uint16_t *)ip_hdr, sizeof(struct iphdr))) {
            printf("Ignored packet with bad checksum\n");
            continue;
        }
        struct route_table_entry *best_router = get_best_route(ip_hdr->daddr);
        if (best_router == NULL) {
            printf("Ignored packet with no route\n");
            continue;
        }

        if (ip_hdr->ttl < 1) {
            printf("Ignored packet with TTL < 1\n");
            continue;
        }
        ip_hdr->ttl--;
        ip_hdr->check = ~(~old_check + ~((uint16_t)(ip_hdr->ttl + 1)) +
                (uint16_t)ip_hdr->ttl) - 1;

        struct mac_entry *best_mac = get_mac_entry(best_router->next_hop);
        if (best_mac == NULL) {
            printf("Ignored packet with no MAC entry\n");
            continue;
        }
        memcpy(eth_hdr->ether_dhost, best_mac->mac, 6);
        get_interface_mac(best_router->interface, eth_hdr->ether_shost);
        send_to_link(best_router->interface, packet, packet_len);
	}
}
