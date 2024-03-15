#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
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
#define PORT 10000

/* Here we have the Frame structure */
#include "common.h"

/* Our unqiue layer 2 ID */
static int ID = 123131;

/* Function which our protocol implementation will provide to the upper layer. */
int send_frame(char *buf, int size)
{
    struct Frame frame;

    frame.frame_delim_start[0] = DLE;
    frame.frame_delim_start[1] = STX;

    frame.source = ID;
    frame.dest = ID;

    strcpy(frame.payload, buf);

    frame.frame_delim_end[0] = DLE;
    frame.frame_delim_end[1] = ETX;

    for(int i = 0; i < sizeof(struct Frame); i++) {
        send_byte(((char *)&frame)[i]);
    }
	/* if all went all right, return 0 */
	return 0;
}

int main(int argc,char** argv){
	// Don't touch this
	init(HOST,PORT);

    char buffer[6];
    strcpy(buffer, "Hello");
    send_frame(buffer, strlen(buffer));

	/* TODO 3.1: Get a timestamp of the current time copy it in the the payload */
    time_t t = time(NULL);
	/* TODO 3.0: Update the maximum size of the payload in Frame to 100 (in common.h), send the frame */
struct Frame frame;
    frame.frame_delim_start[0] = DLE;
    frame.frame_delim_start[1] = STX;

    frame.source = ID;
    frame.dest = ID;

    strcpy(frame.payload, ctime(&t));

    frame.frame_delim_end[0] = DLE;
    frame.frame_delim_end[1] = ETX;

    for(int i = 0; i < sizeof(struct Frame); i++) {
        send_byte(((char *)&frame)[i]);
    }
	/* TODO 3.0: Update the maximum size of the payload in Frame to 300, send the frame */

	return 0;
}
