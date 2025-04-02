# Networking Protocols - 2nd Homework

### Constantinescu Vlad 324CB

> ***Note: the readme was written using markdown rules, but the script to build
> the task required a plain text file.***

The archive contains:

- `server.c` - the server implementation and the main function
- `tcp_client.c` - the client implementation and the main function
- `common.h` - header file containing the headers, structures, and constants used
- `Makefile` - used to compile the server and client
- `readme.txt` - the readme file

### Custom Structures
- `subscribe_msg`: structure used to store the data received from the client
    - `type`: the type of message, 0 for unsubscribe, 1 for subscribe
    - `topic`: the topic to subscribe/unsubscribe to
    

- `tcp_msg`: structure used to store the data received from the TCP client
    - `type`: the type of the message
    - `data`: the message itself
    

- `udp_msg`: structure used to store the data received from the UDP client
    - `topic`: the topic of the message
    - `type`: the type of the message
    - `data`: the message itself


- `client`: structure used to store the data of a client
    - `id`: the identifier of the client
    - `socket`: the socket of the client

### Data Structures Used by the Server

`vector<client> clients`: vector used to store the clients connected to the server

`unordered_map<string, vector<client>> topic_clients`: map used to store the clients subscribed to a topic

### Server Functions
`socket_setup`: Sets up the TCP and UDP sockets

`handle_udp_message`: Handles the UDP message received by the server

`handle_tcp_message`: Handles the TCP message received by the server

`handle_disconnect`: Handles the disconnection of a client

`handle_command`: Handles the commands (subscribe/ unsubscribe) received by the server

`handle_client_message`: Handles the messages received by the server

`monitor_file_descriptors`: Monitors the file descriptors for incoming messages

### Client Functions

`connect_to_server`: Connects the client to the server

`send_tcp_connect_message`: Sends a TCP message to the server to connect

`handle_command`: Handles the commands received by the client

`split`: Splits a string into tokens

`get_udp_message`: Gets the UDP message received by the client

`handle_int`: Handles the integer message received by the client

`handle_short`: Handles the short real message received by the client

`handle_float`: Handles the float message received by the client

`handle_string`: Handles the string message received by the client

`handle_udp_message`: Handles the UDP message received by the client

`monitor_file_descriptors`: Monitors the file descriptors for incoming messages

### Tasks and Implementation Details
- The server is implemented using a TCP and a UDP socket.
- The server can handle multiple clients connected at the same time.
- Used file sets instead of epoll because the server is not required to handle
a large number of clients.
- Both disable stdout buffering and Nagle's algorithm.
- Both use a loop to handle multiple clients with multiplexing.
- The server monitors the file descriptors for incoming messages: TCP, UDP, and
STDIN.
  1. TCP message:
    - If the message is a connection message, the server checks if the client
       is already connected and refuses the connection if it is.
    - If the message is a subscribe/unsubscribe message, the server adds or
       removes the client from the list of clients subscribed to the topic.
  2. UDP message:
    - The server reads the message and creates a new TCP message with the
       received data.
    - The server checks if there are clients subscribed to the topic and sends
       the message to them.
  3. STDIN message:
    - The server reads the command and checks if it is "exit".
    - If the command is "exit", the server closes all connections and exits.
    - If the command is not "exit", the server continues to monitor the file
       descriptors.
- The client is implemented using a TCP socket.
- The client can connect to the server and send messages.
- The client can handle multiple types of messages:
    1. Integer (1): extract the sign byte and the number, check the sign byte
    and display the number.
    2. Short real (2): extract the short real number and divide by 100 and display
      it.
    3. Float (3): extract the sign byte, the number, and the power.
    Divide the number by 10 ^ power and check the sign byte and display the number.
  4. String message: display the message.

### Important Notes
- The wildcard characters are not implemented.
- The server does not support rapid fire messages.

