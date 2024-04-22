#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

#define HOST "54.170.241.232"
#define PORT 8080

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    char **body = malloc(2 * sizeof(char));
    int sockfd;

        
    // Ex 1.1: GET dummy from main server
    sockfd = open_connection(HOST, PORT, AF_INET, SOCK_STREAM, 0);
//    message = compute_get_request(HOST, "/api/v1/dummy", NULL, NULL, 0);
//    send_to_server(sockfd, message);
//    response = receive_from_server(sockfd);
//    printf("Ex1.1:\n%s\n", response);

    // Ex 1.2: POST dummy and print response from main server
    body[0] = malloc(100 * sizeof(char));
    body[1] = malloc(100 * sizeof(char));
    memcpy(body[0], "body=Hello", strlen("body=Hello"));
    message = compute_post_request(HOST, "apy/v1/dummy", "application/x-www-form-urlencoded", body, 1, NULL, 0);
    printf("%s\n", message);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("Ex1.2:\n%s\n", response);

    // Ex 2: Login into main server

    // username: student
    // password: student
    body[0] = "username=student";
    body[1] = "password=student";
    message = compute_post_request(HOST, "/api/v1/auth/login", "application/x-www-form-urlencoded", body, 2, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("Ex2:\n%s\n", response);

    // Ex 3: GET weather key from main server
    message = compute_get_request(HOST, "/api/v1/weather/key", NULL, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("Ex3:\n%s\n", response);

    sockfd = open_connection("api.openweathermap.org", 80, AF_INET, SOCK_STREAM, 0);

    // Ex 4: GET weather data from OpenWeather API
    message = compute_get_request("api.openweathermap.org", "/data/2.5/weather", "q=London,uk&appid=3b5f4b3b3b3b3b3b3b3b3b3b3b3b3b3", NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("Response from server:\n%s\n", response);

    // Ex 5: POST weather data for verification to main server
    /* Folosind cheia obținută la exercițiul anterior, implmentați o cerere de tip GET la serverul Openweather Map pentru a obține datele despre vreme, specificând un set de coordonate (latitudine, longitudine) la alegere. */
    message = compute_post_request("api.openweathermap.org", "/data/2.5/weather", "application/x-www-form-urlencoded", NULL, 0, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("Response from server:\n%s\n", response);

    // Ex 6: Logout from main server
    /* Implementați o cerere de tip GET pentru a vă deconecta de la serverul principal. */
    message = compute_get_request(HOST, "/api/v1/auth/logout", NULL, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("Response from server:\n%s\n", response);

    // BONUS: make the main server return "Already logged in!"

    // free the allocated data at the end!
    free(message);
    free(response);
    close_connection(sockfd);
    return 0;
}
