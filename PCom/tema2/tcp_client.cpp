#include "common.h"

using namespace std;

// Connect to the server
void connect_to_server(int sockfd, const char *server_ip, int port) {
    // Create the server address
    auto server_addr = new sockaddr_in;
    server_addr->sin_port = htons(port);
    server_addr->sin_family = AF_INET;
    int rc = inet_aton(server_ip, &server_addr->sin_addr);
    DIE(rc < 0, "inet_aton");

    rc = connect(sockfd, (struct sockaddr *) server_addr,
                 sizeof(struct sockaddr_in));
    DIE(rc < 0, "connect");
}

// Send the client ID to the server
void send_tcp_connect_message(int sockfd, const char *client_id) {
    // Allocate memory for the client ID
    char* tcp_client_id = new char[MAX_CLIENT_LENGTH + 1];
    memset(tcp_client_id, 0, MAX_CLIENT_LENGTH + 1);
    memcpy(tcp_client_id, client_id, std::strlen(client_id));

    // Create a new tcp message
    auto* tcp_client_msg = new tcp_msg;
    memset(tcp_client_msg, 0, sizeof(tcp_msg));
    tcp_client_msg->type = 0;
    memcpy(tcp_client_msg->data, tcp_client_id,
           MAX_CLIENT_LENGTH + 1);

    // Send the message
    int rc = (int) send(sockfd, tcp_client_msg, sizeof(tcp_msg), 0);
    DIE(rc < 0, "send");

    // Cleanup
    delete[] tcp_client_id;
    delete tcp_client_msg;
}

// Handle the subscribe and unsubscribe commands
void handle_command(int sockfd, const string& topic, int type) {
    // Check if the topic name is longer than the maximum length
    if (topic.size() > MAX_TOPIC_LENGTH) {
        return;
    }

    // Create and initialize subscribe message
    subscribe_msg sub_message{};
    memset(&sub_message, 0, sizeof(subscribe_msg));
    sub_message.type = type;
    strncpy(sub_message.topic, topic.c_str(), MAX_TOPIC_LENGTH);

    // Create and initialize TCP message
    tcp_msg tcp_message{};
    memset(&tcp_message, 0, sizeof(tcp_msg));
    tcp_message.type = 1;
    memcpy(tcp_message.data, &sub_message, sizeof(subscribe_msg));

    // Send TCP message
    int rc = (int) send(sockfd, &tcp_message, sizeof(tcp_msg), 0);
    DIE(rc < 0, "send");
}


// Used to split the command
vector<string> split(string input, const string& delimiter) {
    vector<string> tokens;
    size_t pos;
    string token;
    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        tokens.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    tokens.push_back(input);
    return tokens;
}

// Get the UDP message from the TCP message
udp_msg get_udp_message(tcp_msg tcp_server_message) {
    udp_msg udp_server_message{};
    memset(&udp_server_message, 0, sizeof(struct udp_msg));
    memcpy(udp_server_message.topic, tcp_server_message.data,
           MAX_TOPIC_LENGTH);
    memcpy(&udp_server_message.type,
           tcp_server_message.data + MAX_TOPIC_LENGTH, sizeof(unsigned char));
    memcpy(udp_server_message.data,
           tcp_server_message.data + MAX_TOPIC_LENGTH + 1,
           MAX_UDP_SIZE);
    udp_server_message.data[MAX_UDP_SIZE - 1] = 0;

    return udp_server_message;
}

// Handle the integer message
void handle_int(const udp_msg& message, const in_addr udp_addr, int udp_port) {
    // Extract the sign byte and the value
    uint8_t sign;
    memcpy(&sign, message.data, sizeof(uint8_t));

    uint32_t value;
    memcpy(&value, message.data + sizeof(uint8_t), sizeof(uint32_t));
    value = ntohl(value);

    // Print the message
    cout << inet_ntoa(udp_addr) << ":" << ntohs(udp_port);
    cout << " - " << message.topic << " - INT - " << (sign == 1 ? "-" : "");
    cout << value << '\n';
}

// Handle the short message
void handle_short(const udp_msg& message, const in_addr udp_addr, int udp_port) {
    // Extract the value
    uint16_t value;
    memcpy(&value, message.data, sizeof(uint16_t));
    value = ntohs(value);

    // Print the message
    cout << inet_ntoa(udp_addr) << ":" << ntohs(udp_port) << " - ";
    cout << message.topic << " - SHORT_REAL - " << fixed << setprecision(2);
    cout << static_cast<float>(value) / 100.00 << '\n';
}

// Handle the float message
void handle_float(const udp_msg& message, in_addr udp_addr, int udp_port) {
    // Extract the sign byte, the value and the power
    uint8_t sign_byte;
    memcpy(&sign_byte, message.data, sizeof(uint8_t));

    uint32_t value;
    memcpy(&value, message.data + sizeof(uint8_t), sizeof(uint32_t));

    uint8_t power;
    memcpy(&power, message.data + sizeof(uint8_t) + sizeof(uint32_t), sizeof(uint8_t));

    value = ntohl(value);
    auto float_value = (float) (value);

    for (int i = 0; i < power; i++) {
        float_value /= 10;
    }

    cout << inet_ntoa(udp_addr) << ":" << ntohs(udp_port) << " - ";
    cout << message.topic << " - FLOAT - " << fixed << setprecision(power);
    cout << (sign_byte == 1 ? "-" : "") << float_value << '\n';
}

// Handle the string message
void handle_string(const udp_msg& message, const in_addr udp_addr, int udp_port) {
    cout << inet_ntoa(udp_addr) << ":" << ntohs(udp_port) << " - ";
    cout << message.topic << " - STRING - " << message.data << '\n';
}

// Handle the UDP message
void handle_udp_message(const udp_msg& message, const in_addr udp_addr, int udp_port) {
    switch (message.type) {
        case 0:
            handle_int(message, udp_addr, udp_port);
            break;
        case 1:
            handle_short(message, udp_addr, udp_port);
            break;
        case 2:
            handle_float(message, udp_addr, udp_port);
            break;
        case 3:
            handle_string(message, udp_addr, udp_port);
            break;
    }
}

// Monitor file descriptors to read from stdin and the server
void monitor_file_descriptors(int sockfd) {
    // Initialize the file descriptor set
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(0, &read_fds);
    FD_SET(sockfd, &read_fds);

    int max_fd = sockfd;

    while (true) {

        // Copy the file descriptor set for select
        fd_set temp_fds;
        FD_ZERO(&temp_fds);
        temp_fds = read_fds;

        // Select the file descriptors that are ready to be read
        int rc = select(max_fd + 1, &temp_fds, nullptr,
                        nullptr, nullptr);
        DIE(rc < 0, "select");

        // Check if standard input is ready to be read
        if (FD_ISSET(STDIN_FILENO, &temp_fds)) {

            // Get the input from the user
            string user_input;
            getline(cin, user_input);

            // Split the input into command and topic
            auto input_vector = split(user_input, " ");
            string command = input_vector[0];
            string topic = input_vector[1];

            // Handle subscribe command
            if (command == "subscribe") {
                // Call the function to handle the command
                handle_command(sockfd, topic, 1);

                // Server sends confirmation
                int reply;
                rc = (int) recv(sockfd, &reply, 1, 0);
                DIE(rc < 0, "recv");

                // Print success message
                if (reply == 1) {
                    cout << "Subscribed to topic." << '\n';
                }

                continue;
            }

            // Handle unsubscribe command
            if (command == "unsubscribe") {
                // Call the function to handle the command
                handle_command(sockfd, topic, 0);

                // Server sends confirmation
                int reply;
                rc = (int) recv(sockfd, &reply, 1, 0);
                DIE(rc < 0, "recv");

                // Print success message
                if (reply == 0) {
                    cout << "Unsubscribed from topic." << '\n';
                }

                continue;
            }

            // Handle exit command
            if (command == "exit") {
                break;
            }

            // Read from the server
        } else {

            // Create tcp receive message
            tcp_msg tcp_server_message{};
            memset(&tcp_server_message, 0, sizeof(struct tcp_msg));
            rc = (int) recv(sockfd, &tcp_server_message,
                            sizeof(struct tcp_msg), 0);
            DIE(rc < 0, "recv");

            // Check if server closed connection or the message is empty
            if (rc == 0) {
                break;
            } else if (tcp_server_message.type != 1) {
                continue;
            }

            // Create udp message
            udp_msg udp_server_message = get_udp_message(tcp_server_message);

            // Get the IP and port

            in_addr udp_addr{};
            memset(&udp_addr, 0, sizeof(struct in_addr));
            memcpy(&udp_addr,
                   tcp_server_message.data + sizeof(struct udp_msg),
                   sizeof(struct in_addr));

            int udp_port;
            memcpy(&udp_port, tcp_server_message.data +
                    sizeof(struct udp_msg)+ sizeof(in_addr),
                    sizeof(uint16_t));

            udp_port = ntohs(udp_port);

            // Handle the UDP message
            handle_udp_message(udp_server_message, udp_addr, udp_port);
        }
    }
}


int main(int argc, char *argv[]) {

    // Disable buffering
    setvbuf(stdout, nullptr, _IONBF, BUFSIZ);

    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(sockfd < 0, "socket");

    // Disable Nagle's algorithm
    int flag = 1;
    int rc = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY,
                    (char *) &flag, sizeof(int));
    DIE(rc < 0, "nagle");

    // Useful to have port as integer
    int port = stoi(argv[3]);

    // Connect to the server
    connect_to_server(sockfd, argv[2], port);

    // Send the client ID to the server
    send_tcp_connect_message(sockfd, argv[1]);

    // Monitor file descriptors
    monitor_file_descriptors(sockfd);

    // Close the connection
    close(sockfd);

    return 0;
}
