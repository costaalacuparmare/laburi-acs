#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <cctype>
#include <vector>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstring>

// Constants
#define MAX_TOPIC_LENGTH 50
#define MAX_UDP_SIZE 1500
#define MAX_TCP_SIZE 1601
#define MAX_CLIENTS 128
#define MAX_CLIENT_LENGTH 10

// Error verification macro
#define DIE(assertion, call_description)                                       \
  do {                                                                         \
    if (assertion) {                                                           \
      fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                       \
      perror(call_description);                                                \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

// Structs

// Struct for the subscribe message
struct subscribe_msg {
    int type;
    char topic[MAX_TOPIC_LENGTH];
};

// Struct for the TCP message
struct tcp_msg {
    char type;
    char data[MAX_TCP_SIZE];
};

// Struct for the UDP message
struct udp_msg {
    char topic[MAX_TOPIC_LENGTH];
    unsigned char type;
    char data[MAX_UDP_SIZE];
};

struct client {
    char id[MAX_CLIENT_LENGTH];
    int socket;
};