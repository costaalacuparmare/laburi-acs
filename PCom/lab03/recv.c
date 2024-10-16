#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "common.h"
#include "link_emulator/lib.h"
#include "include/utils.h"

/**
 * You can change these to communicate with another colleague.
 * There are several factors that could stop this from working over the
 * internet, but if you're on the same network it should work.
 * Just fill in their IP here and make sure that you use the same port.
 */
#define HOST "127.0.0.1"
#define PORT 10001


int main(int argc,char** argv) {
	/* Don't modify this */
	init(HOST,PORT);

	struct l3_msg t;

    /* Receive the frame from the link */

    while (1) {
        memset(&t, 0, sizeof(struct l3_msg));
        int len = link_recv(&t, sizeof(struct l3_msg));
        DIE(len < 0, "Receive message");

        uint32_t recv_sum = ntohl(t.hdr.sum);
        t.hdr.sum = 0;

        // int sum_ok = (simple_csum((void *) &t, sizeof(struct l3_msg)) == recv_sum);

        uint32_t crc = crc32((void *) &t, sizeof(struct l3_msg));

        /* Since we are sending messages with a payload of 1500 - sizeof(header), most of the times the bytes from
     	 * 30 - 1500 will be corrupted and thus when we are printing or string message "Hello world" we see no probems.
	     * This will be visible when we will be sending a file */

        int sum_ok = (crc == recv_sum);

        printf("sum(%s)=0x%08hx; crc=0x%08hx\n", sum_ok ? "GOOD" : "BAD", recv_sum, crc);

        if (sum_ok) {
            printf("ACK\n");
            link_send(&t, sizeof(struct l3_msg));
            FILE *f = fopen("recv.data", "w");
            fwrite(t.payload, sizeof(char), t.hdr.len, f);
            fclose(f);
        } else {
            printf("NACK\n");
            struct l3_msg nack;
            link_send(&nack, 0);
        }
    }
	return 0;
}
