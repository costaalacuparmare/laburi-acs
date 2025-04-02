#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"
#include "requests.h"

// computes and returns a GET request string (query_params
char *compute_get_request(char *host, char *url, char *query_params,
                          char **cookies, int cookies_count, char *token)
{
    char *message = (char *) calloc(BUFLEN, sizeof(char));
    char *line = (char *) calloc(LINELEN, sizeof(char));

    // writes the method name, URL, request params (if any) and protocol type
    if (query_params != NULL) {
        sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    // adds the host
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // add headers and/or cookies, according to the protocol format
    if (cookies != NULL) {
        char *at = line;
        at += sprintf(at, "Cookie:");
        for (int i = 0; i < cookies_count - 1; i++) {
            at += sprintf(at, " %s;", cookies[i]);
        }
        at += sprintf(at, " %s", cookies[cookies_count - 1]);
        compute_message(message, line);
    }

    // add token
    if (token != NULL) {
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }

    // add final new line
    compute_message(message, "");
    free(line);
    return message;
}

// computes and returns a POST request string (cookies can be NULL if not needed)
char *compute_post_request(char *host,char *url, char* content_type, char **body_data,
                           int body_data_fields_count, char **cookies, int cookies_count, char *token)
{
    char *message = (char *) calloc(BUFLEN, sizeof(char));
    char *line = (char *) calloc(LINELEN, sizeof(char));
    char *body_data_buffer = (char *) calloc(LINELEN, sizeof(char));

    // writes the method name, URL and protocol type
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    // adds the host
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    /*
     * adds necessary headers (Content-Type and Content-Length are mandatory)
     * in order to write Content-Length you must first compute the message size
    */
    sprintf(line, "Content-type: %s", content_type);
    compute_message(message, line);

    int data_len = 0;
    for (int i = 0; i < body_data_fields_count; i++) {
        data_len += strlen(body_data[i]);
        data_len++;
    } data_len--;

    sprintf(line, "Content-length: %d", data_len);
    compute_message(message, line);

    // adds cookies
    if (cookies != NULL) {
        char *at = line;
        at += sprintf(at, "Cookie:");
        for (int i = 0; i < cookies_count - 1; i++) {
            at += sprintf(at, " %s;", cookies[i]);
        }
        at += sprintf(at, " %s", cookies[cookies_count - 1]);
        compute_message(message, line);
    }

    // adds token
    if (token != NULL) {
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }

    // adds new line at end of header
    compute_message(message, "");

    // adds the actual payload data
    for (int i = 0; i < body_data_fields_count; i++) {
        sprintf(body_data_buffer, "%s", body_data[i]);
        compute_message(message, body_data_buffer);
    }

    free(line);
    free(body_data_buffer);
    return message;
}

// computes and returns a DELETE request string (cookies can be NULL if not needed)
char *compute_delete_request(char *host, char *url, char *query_params,
                             char **cookies, int cookies_count, char *token)
{
    char *message = (char *) calloc(BUFLEN, sizeof(char));
    char *line = (char *) calloc(LINELEN, sizeof(char));

    // writes the method name, URL, request params (if any) and protocol type
    if (query_params != NULL) {
        sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "DELETE %s HTTP/1.1", url);
    }
    compute_message(message, line);

    // adds the host
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // adds headers and/or cookies, according to the protocol format
    if (cookies != NULL) {
        char *at = line;
        at += sprintf(at, "Cookie:");
        for (int i = 0; i < cookies_count - 1; i++) {
            at += sprintf(at, " %s;", cookies[i]);
        }
        at += sprintf(at, " %s", cookies[cookies_count - 1]);
        compute_message(message, line);
    }

    // adds token
    if (token != NULL) {
        sprintf(line, "Authorization: Bearer %s", token);
        compute_message(message, line);
    }

    // adds final new line
    compute_message(message, "");
    free(line);
    return message;
}
