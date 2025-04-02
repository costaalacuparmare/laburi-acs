# Networking Protocols - 1st Homework

### Constantinescu Vlad 324CB

> ***Note: the readme was written using markdown rules, but the script to build
> the archive does not recognise the README with the ".md" extension***

The archive contains:

- queue.c + queue.h: Contains definitions for a generic queue data structure used for storing packets waiting for MAC address resolution.
- list.c + list.h: Contains definitions for a generic linked list data structure used for the queue implementation.
- lib.c + lib.h: Contains utility functions for handling networking tasks, such as checksum calculation and interface retrieval and MACROS.
- protocols.h: Contains structures and constants related to Ethernet, ARP, IP, and ICMP headers.
- router.c: The main implementation file that includes the router logic, packet processing, and routing functionality.
- Makefile: Used to compile the router program.
- README: Contains an overview of the router implementation, including functionality, data structures, functions, and usage instructions.

#### Router Functions
`get_best_route`: Uses binary search to find the best route for a given destination IP address. Returns a pointer to the corresponding router table entry.

`get_arp_entry`: Searches the ARP table to find the MAC address of a given IP address. Returns a pointer to the corresponding ARP table entry.

`send_icmp_echo`: Sends an ICMP echo reply back to the client if the router is the destination.

`send_icmp_error`: Sends an ICMP error message (Time Exceeded or Destination Unreachable) in response to invalid or unreachable destinations.

`send_arp_request`: Sends an ARP request to resolve the MAC address of the next hop router.

`send_arp_reply`: Sends an ARP reply in response to an ARP request and updates the ARP table.

`send_waiting_packets`: Sends packets waiting in the queue after MAC address resolution.

`compare`: Compare function for qsort used to sort the router table entries based on prefixes and masks.

#### Main Function
- Reads router table entries from a file specified by the command-line argument `argv[1]`.
- Initializes router and ARP tables.
- Receives packets from any link and processes them based on their Ethernet type (IPv4 or ARP).
- Handles IPv4 packets by forwarding, sending ICMP replies, or sending ARP requests.
- Handles ARP packets by sending ARP replies or updating the ARP table.

#### Tasks and Implementation Details
- Forward packets between different network interfaces based on the router table entries.
  Used the 4th lab's implementation as a base for the IPv4 packet processing.
- Implemented Longest Prefix Match (LPM) efficiently using binary search on a sorted router table.
- Implemented ARP table dynamically using ARP requests and replies.
- Used a queue to store packets waiting for MAC address resolution.
- Implemented ICMP error messages for Time Exceeded and Destination Unreachable.
- Sent echo replies in response to ICMP echo requests directed at the router.