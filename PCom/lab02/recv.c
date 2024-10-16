#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"
#include "include/utils.h"
#include <time.h>

/**
 * You can change these to communicate with another colleague.
 * There are several factors that could stop this from working over the
 * internet, but if you're on the same network it should work.
 * Just fill in their IP here and make sure that you use the same port.
 */
#define HOST "127.0.0.1"
#define PORT 10001

#include "common.h"

/* Our unique layer 2 ID */
static int ID = 123131;

/* Function which our protocol implementation will provide to the upper layer. */
int recv_frame(char *buf, int size)
{
    buf[0] = recv_byte();
    buf[1] = recv_byte();

    while ((buf[0] != DLE) && (buf[1] != STX)) {
        buf[0] = buf[1];
        buf[0] = recv_byte();
    }

    int nr_bytes = 0;

    for (int i = 2; i < 2 + 2 * sizeof(int); i++) {
        buf[i] = recv_byte();
        nr_bytes++;
    }

    for (int i = 2 + 2 * sizeof(int); i < size; i++) {
        buf[i] = recv_byte();
        nr_bytes++;
    }

    if (((struct Frame *)buf)->dest != ID) {
        return -1;
    }
	/* If everything went well return the number of bytes received */
	return nr_bytes;
}

/* Function to get the time difference */
int get_time_difference(char *payload)
{
    time_t t = time(NULL);
    return t - atoi(payload);
}

int main(int argc,char** argv){
	/* Don't modify this */
	init(HOST,PORT);

    char buffer[32];
    int size = recv_frame(buffer, 32);
    if (size == -1)
        printf("Message not sent to me\n");
    else
        printf("Received: %d\n", size);

    struct Frame *frame = (struct Frame *)buffer;
    printf("Source: %d\n", frame->source);
    printf("Dest: %d\n", frame->dest);
    printf("Payload: %s\n", frame->payload);

	/* TODO 3: Measure latency in a while loop for any frame that contains
	 * a timestamp we receive, print frame_size and latency */
    while (1) {
        char buffer[100];
        int size = recv_frame(buffer, 32);
        if (size == -1) {
            printf("Message not sent to me\n");
            break;
        } else
            printf("Received: %d\n", size);

        struct Frame *frame = (struct Frame *)buffer;
        printf("Source: %d\n", frame->source);
        printf("Dest: %d\n", frame->dest);
        printf("Payload: %s\n", frame->payload);
        printf("Latency: %d\n", get_time_difference(frame->payload));
    }
	printf("[RECEIVER] Finished transmission\n");
	return 0;
}
