#include "common.h"

#include <sys/socket.h>
#include <sys/types.h>

int recv_all(int sockfd, void *buffer, size_t len) {
    size_t bytes_received = 0;
    size_t bytes_remaining = len;
    char *buff = buffer;
    while (bytes_remaining) {
        int received = recv(sockfd, buff, bytes_remaining, 0);
        if (received <= 0)
            return bytes_received;
        bytes_received += received;
        bytes_remaining -= received;
        buff += received;
    }
    return bytes_received;
}

int send_all(int sockfd, void *buffer, size_t len) {
    size_t bytes_sent = 0;
    size_t bytes_remaining = len;
    char *buff = buffer;
    while(bytes_remaining) {
        int sent = send(sockfd, buff, bytes_remaining, 0);
        if (sent <= 0)
            return bytes_sent;
        bytes_sent += sent;
        bytes_remaining -= sent;
        buff += sent;
    }
    return bytes_sent;
}
