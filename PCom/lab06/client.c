#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "common.h"
#include "utils.h"
#include "list.h"

/* Max size of the datagrams that we will be sending */
#define CHUNKSIZE MAX_SIZE;
#define SENT_FILENAME "client.c"
#define SERVER_IP "172.16.0.100"

#define TICK(X)                                                                \
  struct timespec X;                                                           \
  clock_gettime(CLOCK_MONOTONIC_RAW, &X)

#define TOCK(X)                                                                \
  struct timespec X##_end;                                                     \
  clock_gettime(CLOCK_MONOTONIC_RAW, &X##_end);                                \
  printf("Total time = %f seconds\n",                                          \
         (X##_end.tv_nsec - (X).tv_nsec) / 1000000000.0 +                      \
             (X##_end.tv_sec - (X).tv_sec))

list *window;

void send_file_start_stop(int sockfd, struct sockaddr_in server_address,
                          char *filename) {

  int fd = open(filename, O_RDONLY);
  DIE(fd < 0, "open");
  int rc;
  int seq = 0;

  while (1) {
    /* Reads a chunk of the file */
    struct seq_udp d;
    int n = read(fd, d.payload, sizeof(d.payload));
    DIE(n < 0, "read");
    d.len = n;
    d.seq = seq;
    seq++;

    rc = sendto(sockfd, &d, sizeof(struct seq_udp), 0,
            (struct sockaddr *)&server_address, sizeof(server_address));
    DIE(rc < 0, "sendto");

    while (1) {
        int ack;
        rc = recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL);
        printf("ACK received\n" "ACK = %d\n", ack);
        if (ack == d.seq)
            break;
        rc = sendto(sockfd, &d, sizeof(struct seq_udp), 0,
                    (struct sockaddr *)&server_address, sizeof(server_address));
        DIE(rc < 0, "sendto");
    }

    if (n == 0) // end of file
      break;

  }
}

/* Scoate din lista segmentele care au fost primite */
int update_left_window(list *window, int seq) {
    list_entry* e = window->head;
    list_entry *prev = NULL;
    int count = 0;

    while(e != NULL && e->seq <= seq) {
        prev = e;
        e = e->next;
        free_entry(prev);
        count++;
    }

    window->head = e;
    return count;
}

int send_new_segments(list *window, int new_max_seq, int sockfd,
                      struct sockaddr_in server_address) {
    list_entry* e = window->head;
    /* Sarim peste segmentele deja trimise */
    while(e != NULL && e->seq <= window->max_seq)
        e = e->next;

    if (e != NULL) {
        /* Trimitem urmatoarele segmente pana la new_max_seq */
        while(e != NULL && e->seq <= new_max_seq) {
            e = e->next;
            sendto(sockfd, e->info, e->info_len, 0,
                   (struct sockaddr *)&server_address, sizeof(server_address));
        }
    }
    window->max_seq = new_max_seq;
    return 1;
}


void send_file_go_back_n(int sockfd, struct sockaddr_in server_address,
                      char *filename) {

  int fd = open(filename, O_RDONLY);
  DIE(fd < 0, "open");
  int rc;

  int window_size = 20;
  window->max_seq = 20;

  int seq = 0;
  while (1) {
    /* Reads the content of a file */
    struct seq_udp *d = malloc(sizeof(struct seq_udp));
    int n = read(fd, d->payload, sizeof(d->payload));
    DIE(n < 0, "read");
    d->len = n;
    d->seq = seq;

    add_list_elem(window, d, sizeof(struct seq_udp), seq);
    seq++;

    if (n == 0) // end of file
      break;
  }

  while (1) {
    for (int i = 0; i < window_size; i++) {
        list_entry* e = window->head;
        while(e != NULL && e->seq < i)
            e = e->next;
        if (e != NULL) {
            sendto(sockfd, e->info, e->info_len, 0,
                   (struct sockaddr *)&server_address, sizeof(server_address));
        }
    }

    int ack;
    rc = recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL);
    printf("ACK received\n" "ACK = %d\n", ack);
    if (rc >= 0)
        printf("removed segments: %d\n", update_left_window(window, ack));
    if (ack == window->max_seq)
        break;
  }
}

void send_a_message(int sockfd, struct sockaddr_in server_address) {
  struct seq_udp d;
  strcpy(d.payload, "Hello world!");
  d.len = strlen("Hello world!");

  /* Send a UDP datagram. Sendto is implemented in the kernel (network stack of
   * it), it basically creates a UDP datagram, sets the payload to the data we
   * specified in the buffer, and the completes the IP header and UDP header
   * using the sever_address info.*/
  int rc = sendto(sockfd, &d, sizeof(struct seq_udp), 0,
                  (struct sockaddr *)&server_address, sizeof(server_address));

  DIE(rc < 0, "send");

  /* Receive the ACK. recvfrom is blocking with the current parameters */
  int ack;
  rc = recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL);
}

int main(int argc, char *argv[]) {

  /* We use this structure to store the server info. IP address and Port.
   * This will be written by the UDP implementation into the header */
  struct sockaddr_in servaddr;
  int sockfd, rc;

  // for benchmarking
  TICK(TIME_A);


  /* Our transmission window*/
  window = create_list();

  // Creating socket file descriptor. SOCK_DGRAM for UDP
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  DIE(sockfd < 0, "socket");

  /* Set the timeout on the socket */
  struct timeval timeout;      
  timeout.tv_sec = 10;
  timeout.tv_usec = 0;
    
  rc = setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
              sizeof timeout);
  DIE(rc < 0, "setsockopt");

  // Fill the information that will be put into the IP and UDP header to
  // identify the target process (via PORT) on a given host (via SEVER_IP)
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  inet_aton(SERVER_IP, &servaddr.sin_addr);

  /* Implement and test (one at a time) each of the proposed versions for sending a
   * file.
   */
  // send_a_message(sockfd, servaddr);
  // send_file_start_stop(sockfd, servaddr, SENT_FILENAME);
    send_file_go_back_n(sockfd, servaddr, SENT_FILENAME);

  close(sockfd);

  /* Print the runtime of the program */
  TOCK(TIME_A);

  return 0;
}
