/*
 * Protocoale de comunicații
 * Laborator 11 - Securitate
 * client.c
 */
#include "common.h"
#include "tea.h"
#include "utils.h"
#include "dh.h"

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void run_client(int sockfd) {
	int res;
	struct message msg;
	while (1) {
		char *s = fgets(msg.buffer, sizeof(msg.buffer), stdin);
		DIE(!s, "fgets");

		// Get rid of the newline character.
		msg.size = strlen(msg.buffer);
		msg.buffer[msg.size - 1] = 0;

		if (!strcmp(msg.buffer, "QUIT"))
			break;

		send_message(sockfd, &msg);

		res = recv_message(sockfd, &msg);
		if (res == 0) {
			puts("Server disconnected!");
			break;
		}

		DIE(msg.buffer[msg.size - 1] != '\0', "Non-string reply!");
		printf("Server reply: %s\n", msg.buffer);
	}
}

uint32_t *obtain_key_plain(int sockfd)
{
	// Generate the key and send it to Bob. Use create_key from tea.c
    // and send_message from utils.c
    uint32_t *key = create_key();

    struct message msg;
    memcpy(msg.buffer, key, KEY_SIZE);

    send_message(sockfd, &msg);

    return key;
}

uint32_t *obtain_key_dh(int sockfd)
{
	// Perform DH using the primitives in "include/dh.h". Use derive_key with the
	// secret as argument. We do this because the key and the secret don't necessarly have
	// the same size or structure.
    // mod_pow, generate_key, derive_key
    int p = 23;
    uint32_t secret = generate_secret(p);

    return derive_key(secret);
}

void run_encryption_client(int sockfd) {
	int res;
	struct message msg;

	// Comment this and uncomment the next line
	//uint32_t *key = obtain_key_plain(sockfd);
	uint32_t *key = obtain_key_dh(sockfd);
	while (1) {
		// just like run_client, read a string, send it to the
		// sever, then receive a reply and print it
		// but the request will need to be encrypted and the reply
		// decrypted
		// use the primitives in "include/tea.h"
        char *s = fgets(msg.buffer, sizeof(msg.buffer), stdin);
        DIE(!s, "fgets");

        // Get rid of the newline character.
        msg.size = strlen(msg.buffer);

        uint32_t *data = (uint32_t *)msg.buffer;

        if (!strcmp(msg.buffer, "QUIT"))
            break;

        uint8_t *encrypted_data = encrypt((uint8_t *) data, (uint32_t *) msg.size, key);

        send_message(sockfd, (struct message *)encrypted_data);

        res = recv_message(sockfd, &msg);
        // decrypt the message
        uint8_t *decrypted_data = decrypt((uint8_t *) msg.buffer,(uint32_t *) msg.size, key);

        if (res == 0) {
            puts("Server disconnected!");
            break;
        }

        printf("Server reply: %s\n", decrypted_data);
	}

	destroy_key(key);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("\n Usage: %s <ip> <port>\n", argv[0]);
		return 1;
	}

	// Parsam port-ul ca un numar
	uint16_t port;
	int rc = sscanf(argv[2], "%hu", &port);
	DIE(rc != 1, "Given port is invalid");

	// Obtinem un socket TCP pentru conectarea la server
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	// Completăm in serv_addr adresa serverului, familia de adrese si portul
	// pentru conectare
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	rc = inet_pton(AF_INET, argv[1], &serv_addr.sin_addr.s_addr);
	DIE(rc <= 0, "inet_pton");

	// Ne conectăm la server
	rc = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	DIE(rc < 0, "connect");

	//run_client(sockfd);
	run_encryption_client(sockfd);

	// Inchidem conexiunea si socketul creat
	close(sockfd);

	return 0;
}
