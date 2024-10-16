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

#define HOST1 "54.170.241.232"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd1, sockfd2;

    char data[] = "application/x-www-form-urlencoded";
    char **login = malloc(2 * sizeof(char *));
    login[0] = malloc(100 * sizeof(char));
    login[1] = malloc(100 * sizeof(char));

    sockfd1 = open_connection(HOST1, 8080, AF_INET, SOCK_STREAM, 0);
    sockfd2 = open_connection("37.139.20.5", 80, AF_INET, SOCK_STREAM, 0);

    strcpy(login[0], "username=student");
    strcpy(login[1], "password=student");

    // Ex 1.1: GET dummy from main server
    message = compute_get_request(HOST1, "/api/v1/dummy", NULL, NULL, 0);
    puts("Ex1.1:");
    puts(message);
    send_to_server(sockfd1, message);
    response = receive_from_server(sockfd1);
    puts(response);

    printf("\n");

    // Ex 1.2: POST dummy and print response from main server
    message = compute_post_request(HOST1, "/api/v1/dummy", data, login, 2, NULL, 0);
    puts("Ex1.2:");
    puts(message);
    send_to_server(sockfd1, message);
    response = receive_from_server(sockfd1);
    puts(response);

    printf("\n");

    // Ex 2: Login into main server
    message = compute_post_request(HOST1, "/api/v1/auth/login", data, login, 2, NULL, 0);
    puts("Ex2:");
    puts(message);
    send_to_server(sockfd1, message);
    response = receive_from_server(sockfd1);
    puts(response);

    // Ex 3: GET weather key from main server

    // search for the Set-Cookie key in the response
    char *cookie = strstr(response, "Set-Cookie: ");
    char *cookie_end = strstr(cookie, ";");
    char *cookie_value = malloc(cookie_end - cookie - 12);
    strncpy(cookie_value, cookie + 12, cookie_end - cookie - 12);

    char **cookies = malloc(1 * sizeof(char *));
    cookies[0] = malloc(100 * sizeof(char));
    strcpy(cookies[0], cookie_value);

    message = compute_get_request(HOST1, "/api/v1/weather/key", NULL, cookies, 1);
    puts ("Ex3:");
    puts(message);
    send_to_server(sockfd1, message);
    response = receive_from_server(sockfd1);
    puts(response);

    printf("\n");

    // Ex 4: GET weather data from OpenWeather API
    char *key = strstr(response, "key");
    char *key_end = strstr(key, "\"}");
    char *key_value = malloc(key_end - key - 7);
    strncpy(key_value, key + 6, key_end - key - 6);
    printf ("%s\n", key_value);

    char *query_params = malloc(100 * sizeof(char));
    sprintf(query_params, "lat=1.1&lon=1.1&appid=%s", key_value);

    message = compute_get_request("api.openweathermap.org", "/data/2.5/weather", query_params, NULL, 0);
    puts("Ex4:");
    puts(message);
    send_to_server(sockfd2, message);
    response = receive_from_server(sockfd2);
    puts(response);

    printf("\n");

    // Ex 5: POST weather data for verification to main server
    strcpy(response,strstr(response, "{"));
    char **body_data = malloc(1 * sizeof(char));
    body_data[0] = malloc(1000 * sizeof(char));
    sprintf(body_data[0], "data=%s", response);
    message = compute_post_request(HOST1, "/api/v1/weather/1.1/1.1", data, body_data, 1, NULL, 0);
    puts("Ex5:");
    send_to_server(sockfd1, message);
    response = receive_from_server(sockfd1);
    puts(response);

    printf("\n");

    // Ex 6: Logout from main server
    message = compute_get_request(HOST1, "/api/v1/auth/logout", NULL, NULL, 0);
    puts("Ex6:");
    puts(message);
    send_to_server(sockfd1, message);
    response = receive_from_server(sockfd1);
    puts(response);

    // free the allocated data at the end!
    free(message);
    free(response);
    for (int i = 0; i < 2; i++) {
        free(login[i]);
    }
    free(login);
    free (cookies[0]);
    free(cookies);
    free(cookie_value);
    free(key_value);
    free(query_params);
    free(body_data[0]);
    free(body_data);

    close_connection(sockfd1);
    close_connection(sockfd2);
    return 0;
}
