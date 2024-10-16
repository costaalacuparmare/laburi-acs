#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "common.h"
#include "link_emulator/lib.h"
#include <arpa/inet.h>
#include "include/utils.h"

#define HOST "127.0.0.1"
#define PORT 10000


int main(int argc,char** argv) {
	init(HOST,PORT);

	/* Look in common.h for the definition of l3_msg */
	struct l3_msg t;
    memset(&t, 0, sizeof(struct l3_msg));
	/* We set the payload */
	sprintf(t.payload, "Hello World from my PC");
	t.hdr.len = strlen(t.payload) + 1;

	/* Add the checksum */
	/* Note that we compute the checksum for both header and data. Thus
	 * we set the checksum equal to 0 when computing it */
	t.hdr.sum = 0;

	/* Since sum is on 32 bits, we have to convert it to network order */
	// t.hdr.sum = htonl(simple_csum((void *) &t, sizeof(struct l3_msg)));

    t.hdr.sum = htonl(crc32((void *) &t, sizeof(struct l3_msg)));
	/* Send the message */
	link_send(&t, sizeof(struct l3_msg));

    struct l3_msg g;
    memset(&g, 0, sizeof(struct l3_msg));
    link_recv(&g, sizeof(struct l3_msg));

	if (g.hdr.len == 0) {
        link_send(&t, sizeof(struct l3_msg));
    }

	return 0;
}
