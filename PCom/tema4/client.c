#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

// defines for the server
#define HOST_IP "34.246.184.49"
#define HOST_PORT 8080

// defines for the server paths
#define REGISTER_URL "/api/v1/tema/auth/register"
#define LOGIN_URL "/api/v1/tema/auth/login"
#define LOGOUT_URL "/api/v1/tema/auth/logout"
#define PAYLOAD_TYPE "application/json"
#define ENTER_LIBRARY_URL "/api/v1/tema/library/access"
#define BOOKS_URL "/api/v1/tema/library/books"

// command types for the user
typedef enum {
    REGISTER,  // 0
    LOGIN,   // 1
    ENTER_LIBRARY,  // 2
    GET_BOOKS,  // 3
    GET_BOOK,  // 4
    ADD_BOOK,  // 5
    DELETE_BOOK,  // 6
    LOGOUT,  // 7
    EXIT,  // 8
    INVALID_COMMAND  // 9
} command;

// global variables for cookie and JWT token
char cookie[1024] = { 0 };
char jwt_token[1024] = { 0 };

// global variable for socket
int sockfd;

// Function to parse a command received from the user based on enum types
command parse_command(char *cmd) {
    if (strstr(cmd, "register")) return REGISTER;
    if (strstr(cmd, "login")) return LOGIN;
    if (strstr(cmd, "enter_library")) return ENTER_LIBRARY;
    if (strstr(cmd, "get_books")) return GET_BOOKS;
    if (strstr(cmd, "get_book")) return GET_BOOK;
    if (strstr(cmd, "add_book")) return ADD_BOOK;
    if (strstr(cmd, "delete_book")) return DELETE_BOOK;
    if (strstr(cmd, "logout")) return LOGOUT;
    if (strstr(cmd, "exit")) return EXIT;
    return INVALID_COMMAND;
}

// Function to extract the server response
char *get_response(char *response, char *name) {
    // Use given function to extract JSON response
    char *p = basic_extract_json_response(response);
    if (p == NULL) {
        fprintf(stderr, "Invalid server response\n");
        return NULL;
    }

    // Model JSON response
    JSON_Value *root_value = json_parse_string(p);
    JSON_Object *root_object = json_value_get_object(root_value);
    char *resp = (char *) json_object_get_string(root_object, name);

    return resp;
}

/*
 * Function to parse the response from the server
 * and print the appropriate message
 * Returns 1 if the response is successful, -1 otherwise
 */
int parse_response(char* response, command cmd)
{
    // extract the response code
    int code;
    sscanf(response, "HTTP/1.1 %d", &code);

    // check if the response is successful
    if (code / 100 == 2) {
        switch (cmd) {
            case REGISTER:
                printf("SUCCESS [%d]: User has been registered!\n", code);
                break;
            case LOGIN:
                printf("SUCCESS [%d]: User has been logged in!\n", code);
                break;
            case LOGOUT:
                printf("SUCCESS [%d]: User has been logged out!\n", code);
                break;
            case ENTER_LIBRARY:
                printf("SUCCESS [%d]: User has entered the library!\n", code);
                break;
            case GET_BOOKS: {
                // extract JSON response
                char *json = basic_extract_json_response(response);
                if (json == NULL) {
                    return -1;
                }

                printf("SUCCESS [%d]: Books have been retrieved!\n", code);
                // print the JSON response
                printf("%s\n", json);
                break;
            }
            case GET_BOOK: {
                // extract JSON response
                char *json = basic_extract_json_response(response);
                if (json == NULL) {
                    return -1;
                }
                printf("SUCCESS [%d]: Book has been retrieved!\n", code);
                // print the JSON response
                printf("%s\n", json);
                break;
            }
            case ADD_BOOK:
                printf("SUCCESS [%d]: Book has been added!\n", code);
                break;
            case DELETE_BOOK:
                printf("SUCCESS [%d]: Book has been deleted!\n", code);
                break;
            case EXIT:
                printf("SUCCESS [%d]: Exiting...\n", code);
                break;
            case INVALID_COMMAND:
                fprintf(stderr, "Invalid command\n");
                break;
        }
    } else {
        // if the response is not successful, print the error message
        char *error = get_response(response, "error");
        if (error == NULL) {
            return -1;
        }

        // eliminate new line characters
        for (int i = 0; i < strlen(error); i++) {
            if (error[i] == '\n') {
                strcpy(error + i, error + i + 1);
            }
        }

        printf("ERROR [%d]: %s\n", code, error);
        return -1;
    }

    return 1;
}

/*
 * Function to handle the register command
 * Sends a POST request to the server with the username and password
 * and prints the response from the server
 */
void handle_register() {
    // define the username and password
    char *username = calloc(BUFLEN, sizeof(char));
    char *password = calloc(BUFLEN, sizeof(char));

    // read the username and password from the user
    printf("username=");
    fgets(username, BUFLEN, stdin);
    printf("password=");
    fgets(password, BUFLEN, stdin);

    // check if the username and password contain spaces
    if (strstr(username, " ") != NULL ||
        strstr(password, " ") != NULL) {
        printf("ERROR: Credentials cannot contain spaces!\n");
        return;
    }

    // create JSON payload
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "username", username);
    json_object_set_string(root_object, "password", password);

    // create payload string
    char *payload = calloc(BUFLEN, sizeof(char));
    strcpy(payload, json_serialize_to_string_pretty(root_value));

    // free JSON
    json_value_free(root_value);

    // create POST request
    char *message = compute_post_request(HOST_IP, REGISTER_URL, PAYLOAD_TYPE,
                                         &payload, 1, NULL, 0, NULL);
    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    parse_response(response, REGISTER);

    // free memory
    free(username);
    free(password);
    free(payload);
    free(response);
    free(message);
}

/*
 * Function to handle the login command
 * Sends a POST request to the server with the username and password
 * and prints the response from the server
 * Also extracts the cookie from the response
 * and stores it in the global variable
 */
void handle_login() {
    // define the username and password
    char *username = calloc(BUFLEN, sizeof(char));
    char *password = calloc(BUFLEN, sizeof(char));

    // read the username and password from the user
    printf("username=");
    fgets(username, BUFLEN, stdin);
    printf("password=");
    fgets(password, BUFLEN, stdin);

    // check if the username and password contain spaces
    if (strstr(username, " ") != NULL || strstr(password, " ") != NULL) {
        printf("ERROR: Credentials cannot contain spaces!\n");
        return;
    }

    // create JSON payload
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "username", username);
    json_object_set_string(root_object, "password", password);

    // create payload string
    char *payload = calloc(BUFLEN, sizeof(char));
    strcpy(payload, json_serialize_to_string_pretty(root_value));

    // free JSON
    json_value_free(root_value);

    // create POST request
    char *message = compute_post_request(HOST_IP, LOGIN_URL, PAYLOAD_TYPE,
                                         &payload, 1, NULL, 0, NULL);

    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    int rc = parse_response(response, LOGIN);

    // if the response is not appropriate, free memory and return
    if (rc < 0) {
        free(username);
        free(password);
        free(payload);
        free(response);
        free(message);
        return;
    }

    // extract the cookie from the response
    char* cookie_begin = strstr(response, "Set-Cookie:");
    char* cookie_end = strchr(cookie_begin, ';');
    cookie_begin += strlen("Set-Cookie:");
    memcpy(cookie, cookie_begin, cookie_end - cookie_begin);

    // free memory
    free(username);
    free(password);
    json_free_serialized_string(payload);
    free(response);
    free(message);
}

/*
 * Function to handle the enter_library command
 * Sends a GET request to the server with the cookie
 * and prints the response from the server
 * Also extracts the JWT token from the response
 * and stores it in the global variable
 */
void handle_enter_library() {
    // check if the user is logged in first
    if (strlen(cookie) == 0) {
        printf("ERROR: To enter the library, you need to login first!\n");
        return;
    }

    // add cookie to vector for the request
    char **cookies = calloc(1, sizeof(char *));
    cookies[0] = cookie;

    // create GET request
    char *message = compute_get_request(HOST_IP, ENTER_LIBRARY_URL,
                                        NULL, cookies, 1, NULL);
    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    int rc = parse_response(response, ENTER_LIBRARY);
    // if the response is not appropriate, free memory and return
    if (rc < 0) {
        free(cookies);
        free(response);
        free(message);
        return;
    }

    // extract JWT token
    char* jwt_begin = strstr(response, "{\"token\":\"");
    char* jwt_end = strchr(jwt_begin, '}');
    jwt_begin += strlen("{\"token\":\"");
    memcpy(jwt_token, jwt_begin, jwt_end - jwt_begin);
    jwt_token[strlen(jwt_token) - 1] = 0;

    // free memory
    free(cookies);
    free(response);
    free(message);
}

/*
 * Function to handle the get_books command
 * Sends a GET request to the server with the JWT token
 * and prints the response from the server
 */
void handle_get_books() {
    // check if the user entered the library
    if (strlen(jwt_token) == 0) {
        printf("ERROR: ");
        printf("To access books, you need to enter the library first!\n");
        return;
    }

    // create GET request
    char *message = compute_get_request(HOST_IP, BOOKS_URL, NULL, NULL,
                                        0, jwt_token);

    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    int rc = parse_response(response, GET_BOOKS);
    // if the response is not appropriate, free memory and return
    if (rc < 0) {
        free(response);
        free(message);
        return;
    }

    // free memory
    free(response);
    free(message);
}

/*
 * Function to handle the get_book command
 * Sends a GET request to the server with the book id and JWT token
 * and prints the response from the server
 * Also extracts the book from the response
 * and prints it
 */
void handle_get_book() {
    // check if the user entered the library
    if (strlen(jwt_token) == 0) {
        printf("ERROR: ");
        printf("To access books, you need to enter the library first!\n");
        return;
    }

    // read the book id from the user
    char *id = calloc(BUFLEN, sizeof(char));
    printf("id=");
    fgets(id, BUFLEN, stdin);
    if (id == NULL || id[0] == '\n') {
        printf("ERROR: Book id cannot be empty!\n");
        return;
    }
    id[strlen(id) - 1] = 0;

    // create URL for the request with the book id
    char *url = calloc(BUFLEN, sizeof(char));
    strcpy(url, BOOKS_URL);
    strcat(url, "/");
    strcat(url, id);

    // add cookie to vector for the request
    char **cookies = calloc(1, sizeof(char *));
    cookies[0] = cookie;

    // create GET request
    char *message = compute_get_request(HOST_IP, url, NULL, NULL, 0, jwt_token);

    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    int rc = parse_response(response, GET_BOOK);
    // if the response is not appropriate, free memory and return
    if (rc < 0) {
        free(response);
        free(message);
        return;
    }

    // free memory
    free(response);
    free(message);
    free(url);
    free(id);
    free(cookies);
}

/*
 * Function to handle the add_book command
 * Sends a POST request to the server with the book details and JWT token
 * and prints the response from the server
 */
void handle_add_book() {
    // check if the user entered the library
    if (strlen(jwt_token) == 0) {
        printf("ERROR: ");
        printf("To create a book, you need to enter the library first!\n");
        return;
    }

    // read book title, author, genre, publisher, page count
    char *title = calloc(BUFLEN, sizeof(char));
    char *author = calloc(BUFLEN, sizeof(char));
    char *genre = calloc(BUFLEN, sizeof(char));
    char *publisher = calloc(BUFLEN, sizeof(char));
    char *page_count_str = calloc(BUFLEN, sizeof(char));

    // check if the fields are empty
    int check = 1;

    // read the book details from the user
    printf("title=");
    fgets(title, BUFLEN, stdin);
    if (title == NULL || title[0] == '\n'){
        check = 0;
    } else {
        title[strlen(title) - 1] = 0;
    }

    // read the book details from the user
    printf("author=");
    fgets(author, BUFLEN, stdin);
    if (author == NULL || author[0] == '\n') {
        check = 0;
    } else {
        author[strlen(author) - 1] = 0;
    }

    // read the book details from the user
    printf("genre=");
    fgets(genre, BUFLEN, stdin);\
    if (genre == NULL || genre[0] == '\n') {
        check = 0;
    } else {
        genre[strlen(genre) - 1] = 0;
    }

    // read the book details from the user
    printf("publisher=");
    fgets(publisher, BUFLEN, stdin);
    if (publisher == NULL || publisher[0] == '\n') {
        check = 0;
    } else {
        publisher[strlen(publisher) - 1] = 0;
    }
    // page count must be a number
    printf("page_count=");
    fgets(page_count_str, BUFLEN, stdin);
    if (page_count_str == NULL || page_count_str[0] == '\n') {
        check = 0;
    } else {
        page_count_str[strlen(page_count_str) - 1] = 0;
    }

    int page_count = atoi(page_count_str);

    // check if the fields are empty
    if (check == 0) {
        printf("ERROR: Fields cannot be empty!\n");
        return;
    }

    // check if the page count is a positive number
    if (page_count == 0 || page_count < 0) {
        printf("ERROR: Page count must be a positive number!\n");
        return;
    }

    // create JSON payload
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    json_object_set_string(root_object, "title", title);
    json_object_set_string(root_object, "author", author);
    json_object_set_string(root_object, "genre", genre);
    json_object_set_string(root_object, "publisher", publisher);
    json_object_set_number(root_object, "page_count", page_count);

    // create payload string
    char *payload = calloc(BUFLEN, sizeof(char));
    strcpy(payload, json_serialize_to_string_pretty(root_value));

    // add cookie to vector for the request
    char **cookies = calloc(1, sizeof(char *));
    cookies[0] = cookie;

    // create POST request
    char *message = compute_post_request(HOST_IP, BOOKS_URL, PAYLOAD_TYPE,
                                         &payload, 1, cookies, 1, jwt_token);

    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    parse_response(response, ADD_BOOK);

    // free memory
    free(title);
    free(author);
    free(genre);
    free(publisher);
    free(payload);
    free(response);
    free(message);
    free(cookies);
}

/*
 * Function to handle the delete_book command
 * Sends a DELETE request to the server with the book id and JWT token
 * and prints the response from the server
 */
void handle_delete_book() {
    // check if the user entered the library
    if (strlen(jwt_token) == 0) {
        printf("ERROR: ");
        printf("To delete a book, you need to enter the library first!\n");
        return;
    }

    // read the book id from the user
    char *id = calloc(BUFLEN, sizeof(char));
    printf("id=");
    fgets(id, BUFLEN, stdin);
    if (id == NULL || id[0] == '\n') {
        printf("ERROR: Book id cannot be empty!\n");
        return;
    }
    id[strlen(id) - 1] = 0;

    // create URL for the request with the book id
    char *url = calloc(BUFLEN, sizeof(char));
    strcpy(url, BOOKS_URL);
    strcat(url, "/");
    strcat(url, id);

    // add cookie to vector for the request
    char **cookies = calloc(1, sizeof(char *));
    cookies[0] = cookie;

    // create DELETE request
    char *message = compute_delete_request(HOST_IP, url, NULL, cookies, 1, jwt_token);

    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    parse_response(response, DELETE_BOOK);

    // free memory
    free(response);
    free(message);
    free(url);
    free(id);
    free(cookies);

}

/*
 * Function to handle the logout command
 * Sends a GET request to the server with the cookie
 * and prints the response from the server
 */
void handle_logout() {

    // add cookie and let server check if the user is logged in
    char **cookies = calloc(1, sizeof(char *));
    cookies[0] = cookie;

    // create GET request
    char *message = compute_get_request(HOST_IP, LOGOUT_URL, NULL, cookies, 1, NULL);

    // send the request to the server
    send_to_server(sockfd, message);

    // receive the response from the server
    char *response = receive_from_server(sockfd);

    // parse the response and print the message
    parse_response(response, LOGOUT);

    // reset the cookie and JWT token
    memset(cookie, 0, sizeof(cookie));
    memset(jwt_token, 0, sizeof(jwt_token));

    // free memory
    free(response);
    free(message);
    free(cookies);
}

/*
 * Main function to handle the user input
 * and call the appropriate function
 * based on the command received
 */
int main(int argc, char *argv[])
{
    // allocate memory for the command
    char *in_cmd = calloc(BUFLEN, sizeof(char));

    while (1) {
        // open connection to the server
        sockfd = open_connection(HOST_IP, HOST_PORT, AF_INET, SOCK_STREAM, 0);

        // read the command from the user
        fgets(in_cmd, BUFLEN, stdin);

        // modify the command to int for checking cases
        command cmd = parse_command(in_cmd);

        // call the appropriate function based on the command
        switch (cmd) {
            case REGISTER:
                handle_register();
                break;
            case LOGIN:
                handle_login();
                break;
            case ENTER_LIBRARY:
                handle_enter_library();
                break;
            case GET_BOOKS:
                handle_get_books();
                break;
            case GET_BOOK:
                handle_get_book();
                break;
            case ADD_BOOK:
                handle_add_book();
                break;
            case DELETE_BOOK:
                handle_delete_book();
                break;
            case LOGOUT:
                handle_logout();
                break;
            // If the command is exit, close the connection and free memory
            case EXIT: {
                close_connection(sockfd);
                free(in_cmd);
                return 0;
            }
            // If the command is invalid, print an error message
            case INVALID_COMMAND:
                parse_response("HTTP/1.1 200", INVALID_COMMAND);
                break;
        }
        // close the connection after each command
        close_connection(sockfd);
    }
}
