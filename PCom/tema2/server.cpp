#include "common.h"

using namespace std;

// Vector for the clients
vector<client> clients;

// Map for the topics and the clients subscribed to them
unordered_map<string, vector<string>> topics;

// Set up the UDP and TCP sockets
int socket_setup(int port, int type) {
    int sockfd = socket(AF_INET, type, 0);
    DIE(sockfd < 0, "socket");

    // Create the server address
    auto *addr = new sockaddr_in;
    memset(addr, 0, sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);

    // Bind the socket with the address
    int rc = bind(sockfd, (const struct sockaddr *) addr,
            sizeof(struct sockaddr_in));
    DIE(rc < 0, "udp bind");

    return sockfd;
}

// Handle UDP messages
int handle_udp_message(int udp_sockfd) {
    // Prepare buffer for receiving UDP message
    char buf[MAX_UDP_SIZE + MAX_TOPIC_LENGTH + 2];
    memset(buf, 0, sizeof(buf));

    auto *udp_client = new sockaddr_in;
    socklen_t udp_len = sizeof(struct sockaddr_in);

    // Receive message from UDP socket
    int rc = (int) recvfrom(udp_sockfd, buf, sizeof(buf), 0,
                            (struct sockaddr *)udp_client, &udp_len);
    DIE(rc < 0, "udp recv");

    // Create TCP message from received UDP message
    auto *tcp_message = new tcp_msg;
    memset(tcp_message, 0, sizeof(struct tcp_msg));
    memcpy(tcp_message->data, buf, sizeof(struct udp_msg));
    tcp_message->type = 1;


    // Extract topic from UDP message
    char *topic = new char[MAX_TOPIC_LENGTH + 1];
    memset(topic, 0, MAX_TOPIC_LENGTH + 1);
    memcpy(topic, (struct udp_msg *) buf, MAX_TOPIC_LENGTH);

    // If no clients are subscribed to the topic, return -1
    if (topics.find(topic) == topics.end()) {
        delete udp_client;
        delete[] topic;
        delete tcp_message;
        return -1;
    }

    // Get the subscribed clients from the topic
    vector<string> topic_subscribers = topics[topic];

    // Iterate all subscribed clients
    for (const auto& topic_subscriber : topic_subscribers) {
        // Get client with corresponding ID
        for (const auto& c : clients) {
            if (strcmp(c.id, topic_subscriber.c_str()) == 0) {
                if (c.socket >= 0) {
                    // Send TCP message to subscribed_client
                    rc = (int) send(c.socket, tcp_message,
                                    sizeof(struct tcp_msg), 0);
                    DIE(rc < 0, "tcp send");
                    break;
                }
            }
        }
    }

    delete udp_client;
    delete[] topic;
    delete tcp_message;

    return 0;
}

int handle_tcp_message(int tcp_sockfd) {
    // Get client_sockfd information
    auto *tcp_client = new sockaddr_in;
    socklen_t tcp_len = sizeof(struct sockaddr_in);

    // Allocate memory for TCP message
    auto *tcp_message = new tcp_msg;
    memset(tcp_message, 0, sizeof(tcp_msg));

    // Accept new TCP connection
    int client_sockfd = accept(tcp_sockfd, (struct sockaddr *) tcp_client,
                               &tcp_len);
    DIE(client_sockfd < 0, "accept");

    // Receive message from client_sockfd
    int rc = (int) recv(client_sockfd, tcp_message, sizeof(tcp_msg), 0);
    DIE(rc < 0, "tcp recv");

    // Get client_sockfd ID
    char *client_id = tcp_message->data;

    // Check previous connections for the client
    for (const auto& c : clients) {
        if (strcmp(c.id, client_id) == 0 && c.socket != -1) {
            // If the client is already connected, close the connection
            close(client_sockfd);
            cout << "Client " << client_id << " already connected." << '\n';
            delete tcp_client;
            delete tcp_message;
            return -1;
        }
    }

    // Update the maps with client information
    bool client_found = false;
    for (auto& c : clients) {
        if (strcmp(c.id, client_id) == 0) {
            c.socket = client_sockfd;
            client_found = true;
            break;
        }
    }

    if (!client_found) {
        // Create a new client entry if not found
        client new_client{};
        strcpy(new_client.id, client_id);
        new_client.socket = client_sockfd;
        clients.push_back(new_client);
    }

    // Print message
    auto port = ntohs(tcp_client->sin_port);
    auto *address = inet_ntoa(tcp_client->sin_addr);
    cout << "New client " << client_id << " connected from ";
    cout << address << ":" << port << endl;

    delete tcp_client;
    delete tcp_message;

    return client_sockfd;
}

void handle_disconnect(client curr_client, fd_set &read_fds,
                       fd_set &temp_fds) {
    // Print message
    cout << "Client " << curr_client.id << " disconnected." << endl;

    // Get client's socket
    int client_sockfd = curr_client.socket;

    // Remove the client from the clients vector
    for (auto& client : clients) {
        if (client.socket == client_sockfd) {
            client.socket = -1;
            break;
        }
    }

    // Close the connection
    close(client_sockfd);

    // Update the file descriptors set
    FD_CLR(client_sockfd, &read_fds);
    FD_CLR(client_sockfd, &temp_fds);
}

void handle_command(const client& curr_client, const string &topic, int type) {
    // Get the subscribed clients to the topic
    auto subscribers = topics[topic];

    //Find the client in the list of subscribers
    auto client_id = find(subscribers.begin(), subscribers.end(),
                          curr_client.id);
    // If the client can be found in the list of subscribers, remove it
    if (type == 0 && client_id != subscribers.end()) {
        subscribers.erase(client_id);
    }

    // If the client is not already subscribed, add it to the list
    if (type == 1 && client_id == subscribers.end()) {
        subscribers.emplace_back(curr_client.id);
    }

    // Update the topic's subscribers with the new list.
    topics[topic] = subscribers;
}

// Function to compare a topic with a wildcard topic - UNSUCCESSFUL

//bool equal_wildcard_topic(const string& existing_topic, const string& wildcard_topic) {
//    int i = 0, j = 0, last_pos_j = -1, last_pos_i = 0;
//    while (i < existing_topic.size() && j < wildcard_topic.size()) {
//        if (existing_topic[i] == '*' && i == existing_topic.size() - 1) {
//            return true;
//        } else if (existing_topic[i] != wildcard_topic[j] && existing_topic[i] != '+' && existing_topic[i] != '*') {
//            if (last_pos_j == - 1) {
//                return false;
//            } else {
//                j = last_pos_j;
//                i = last_pos_i;
//                continue;
//            }
//        } else if (existing_topic[i] == '*') {
//            i++;
//            while (j < wildcard_topic.size() && wildcard_topic[j] != existing_topic[i]) {
//                j++;
//            }
//            if (j == wildcard_topic.size()) {
//                return false;
//            } else {
//                last_pos_j = j + 1;
//                last_pos_i = i - 1;
//            }
//        }
//        i++;
//        j++;
//        if (i == existing_topic.size() && j == wildcard_topic.size() && last_pos_j == -1) {
//            j = last_pos_j;
//            i = last_pos_i;
//        }
//    }
//    if (i < existing_topic.size() || j < wildcard_topic.size()) {
//        if (i == existing_topic.size() - 1 && j == wildcard_topic.size() && wildcard_topic[j] == '*') {
//            return true;
//        }
//        return false;
//    } else {
//        return true;
//    }
//}
//
//void handle_command(const client& curr_client, const string &topic, int type) {
//    // Check if the topic contains wildcard characters
//    bool wildcard_present = (topic.find('*') != string::npos || topic.find('+') != string::npos);
//
//    // Get the subscribed clients to the topic
//    auto& subscribers = topics[topic];
//
//    // If the topic contains wildcard characters
//    if (wildcard_present) {
//        // Iterate through existing topics to find matches
//        for (auto& entry : topics) {
//            const string& existing_topic = entry.first;
//
//            // Check if the existing topic matches the wildcard pattern
//            if (equal_wildcard_topic(existing_topic, topic)) {
//                // Find the client in the list of subscribers for the existing topic
//                auto client_id = find(subscribers.begin(), subscribers.end(),
//                                      curr_client.id);
//
//                // If the client can be found in the list of subscribers, remove it
//                if (type == 0 && client_id != subscribers.end()) {
//                    subscribers.erase(client_id);
//                }
//
//                // If the client is not already subscribed, add it to the list
//                if (type == 1 && client_id == subscribers.end()) {
//                    subscribers.emplace_back(curr_client.id);
//                }
//            }
//        }
//    } else {
//        // Find the client in the list of subscribers
//        auto client_id = find(subscribers.begin(), subscribers.end(),
//                              curr_client.id);
//
//        // If the client can be found in the list of subscribers, remove it
//        if (type == 0 && client_id != subscribers.end()) {
//            subscribers.erase(client_id);
//        }
//
//        // If the client is not already subscribed, add it to the list
//        if (type == 1 && client_id == subscribers.end()) {
//            subscribers.emplace_back(curr_client.id);
//        }
//    }
//}


void handle_client_message(const client& curr_client, fd_set &read_fds,
                           fd_set &temp_fds) {
    // Allocate memory for client message
    auto *client_message = new tcp_msg;
    memset(client_message, 0, sizeof(struct tcp_msg));

    // Receive the data.
    int rc = (int) recv(curr_client.socket, client_message, sizeof(tcp_msg),
                        0);
    DIE(rc < 0, "client recv");

    if (rc == 0) {
        handle_disconnect(curr_client, read_fds, temp_fds);
        return;
    }

    // Check if the message is a subscribe/unsubscribe message
    if (client_message->type != 1) {
        return;
    }

    // Allocate memory for the subscribe message
    auto *sub_message = new subscribe_msg;
    memset(sub_message, 0, sizeof(struct subscribe_msg));
    memcpy(sub_message, client_message->data,
           sizeof(struct subscribe_msg));


    // Handle subscription request
    if (sub_message->type == 1) {
        // Check if the topic has any subscribers
        if (topics.find(sub_message->topic) != topics.end()) {
            handle_command(curr_client, sub_message->topic, sub_message->type);
        }
        else {
            // If topic has no subscribers, create a new list of subscribers
            vector<string> subscribers;

            // Add the client to the list of subscribers
            subscribers.emplace_back(curr_client.id);

            // Add the topic and the list of subscribers to the map
            topics.insert(make_pair(sub_message->topic,
                                           subscribers));
        }

        // Send confirmation to the client
        int flag = 1;
        rc = (int) send(curr_client.socket, &flag, 1, 0);
        DIE(rc < 0, "subscribe send");
    }

    if (sub_message->type == 0) {

        // Check if the topic has any subscribers
        if (topics.find(sub_message->topic) != topics.end()) {
            handle_command(curr_client, sub_message->topic, sub_message->type);
        }

        // Send confirmation to the client
        int flag = 0;
        rc = (int) send(curr_client.socket, &flag, 1, 0);
        DIE(rc < 0, "unsubscribe send");
    }
}

// Monitor file descriptors for incoming messages
void monitor_file_descriptors(int udp_sockfd, int tcp_sockfd) {
    // Initialize the file descriptor set
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(0, &read_fds);
    FD_SET(udp_sockfd, &read_fds);
    FD_SET(tcp_sockfd, &read_fds);

    int max_fd = max(udp_sockfd, tcp_sockfd);

    int loop = true;
    while (loop) {

        fd_set temp_fds;
        FD_ZERO(&temp_fds);
        temp_fds = read_fds;

        // Select the file descriptors that are ready to be read
        int rc = select(max_fd + 1, &temp_fds, nullptr,
                        nullptr, nullptr);
        DIE(rc < 0, "select");

        // Iterate all file descriptors
        for (int i = 0; i <= max_fd; i++) {

            // Check if the file descriptor is ready to be read
            if (FD_ISSET(i, &temp_fds)) {
                // Handle TCP client connections
                if (i == tcp_sockfd) {
                    int client = handle_tcp_message(tcp_sockfd);

                    if (client < 0) {
                        continue;
                    }

                    // Update the file descriptors set
                    FD_SET(client, &read_fds);

                    // Update the maximum file descriptor
                    max_fd = max(client, max_fd);

                    continue;
                }

                // Handle UDP messages
                if (i == udp_sockfd) {
                    rc = handle_udp_message(udp_sockfd);
                    if (rc < 0) {
                        continue;
                    } else {
                        break;
                    }
                }

                // Handle exit command
                if (i == STDIN_FILENO) {
                    string command;
                    cin >> command;
                    if (command == "exit") {
                        // Close all client connections
                        for (int j = 1; j <= max_fd; j++) {
                            // check if the file descriptor is valid
                            if (FD_ISSET(j, &read_fds) && j != udp_sockfd &&
                                j != tcp_sockfd) {
                                FD_CLR(j, &read_fds);
                                close(j);
                            }
                        }

                        // Exit the loop
                        loop = false;
                        break;
                    }

                    // If the command is not exit, ignore it
                    continue;
                }

                // Get client information
                client curr_client{};
                for (const auto& c : clients) {
                    if (c.socket == i) {
                        curr_client = c;
                        break;
                    }
                }

                // Handle client messages
                handle_client_message(curr_client, read_fds, temp_fds);
            }
        }
    }
}

int main(int argc, char *argv[]) {

    // Disable buffering
    setvbuf(stdout, nullptr, _IONBF, BUFSIZ);

    int port = stoi(argv[1]);

    // Set up the UDP socket
    int udp_sockfd = socket_setup(port, SOCK_DGRAM);

    // Set up the TCP socket
    int tcp_sockfd = socket_setup(port, SOCK_STREAM);

    int rc = listen(tcp_sockfd, MAX_CLIENTS);
    DIE(rc < 0, "listen");

    // Disable Nagle's algorithm
    int flag = 1;
    rc = setsockopt(tcp_sockfd, IPPROTO_TCP, TCP_NODELAY,
                    (const void*) &flag, sizeof(int));
    DIE(rc < 0, "nagle");

    // Monitor file descriptors for incoming messages
    monitor_file_descriptors(udp_sockfd, tcp_sockfd);

    // Close connections
    close(udp_sockfd);
    close(tcp_sockfd);

    return 0;
}