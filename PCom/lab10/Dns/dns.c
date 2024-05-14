// Protocoale de comunicatii
// Laborator 10 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo hints, *result, *p;

	// set hints
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_CANONNAME;

	// get addresses
    ret = getaddrinfo(name, NULL, &hints, &result);
    if (ret != 0) {
        return;
    }

	// iterate through addresses and print them
    for (p = result; p != NULL; p = p->ai_next) {
        struct sockaddr_in *addr = (struct sockaddr_in *)p->ai_addr;
        printf("%s\n", inet_ntoa(addr->sin_addr));
        /*
         * FOR IPv6 printf("%s\n", inet_ntop(AF_INET, &addr->sin_addr,
         * (char *)malloc(INET_ADDRSTRLEN), INET_ADDRSTRLEN));
         */
    }

	// free allocated data
    freeaddrinfo(result);
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

	// fill in address data
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_aton(ip, &addr.sin_addr);

	// get name and service
    ret = getnameinfo((struct sockaddr *)&addr, sizeof(addr), host,
            sizeof(host), service, sizeof(service), 0);
    if (ret != 0) {
       return;
    }

	// print name and service
    printf("%s %s\n", host, service);
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
