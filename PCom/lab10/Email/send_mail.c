/*
 * Protocoale de comunicatii
 * Laborator 10 - E-mail
 * send_mail.c
 */

#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>  
#include <unistd.h>     
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define SMTP_PORT 25
#define MAXLEN 500

/**
 * Citeste maxim maxlen octeti de pe socket-ul sockfd in
 * buffer-ul vptr. Intoarce numarul de octeti cititi.
 */
ssize_t read_line(int sockd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *buffer;

    buffer = vptr;

    for (n = 1; n < maxlen; n++) {
        if ((rc = read(sockd, &c, 1)) == 1) {
            *buffer++ = c;

            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            if (n == 1) {
                return 0;
            } else {
                break;
            }
        } else {
            if (errno == EINTR) {
                continue;
            }

            return -1;
        }
    }

    *buffer = 0;
    return n;
}

void error(const char *msg)
{
    perror(msg);
    exit(errno);
}


int open_connection(char *host_ip, int portno, int ip_type, int socket_type, int flag)
{
    struct sockaddr_in serv_addr;
    int sockfd = socket(ip_type, socket_type, flag);
    if (sockfd < 0)
        error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = ip_type;
    serv_addr.sin_port = htons(portno);
    inet_aton(host_ip, &serv_addr.sin_addr);

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    return sockfd;
}

/**
 * Trimite o comanda SMTP si asteapta raspuns de la server. Comanda
 * trebuie sa fie in buffer-ul sendbuf. Sirul expected contine
 * inceputul raspunsului pe care trebuie sa-l trimita serverul
 * in caz de succes (de exemplu, codul 250). Daca raspunsul
 * semnaleaza o eroare, se iese din program.
 */
void send_command(int sockfd, const char sendbuf[], char *expected)
{
    char recvbuf[MAXLEN];
    int nbytes;
    char CRLF[2] = {13, 10};

    printf("Trimit: %s\n", sendbuf);
    write(sockfd, sendbuf, strlen(sendbuf));
    write(sockfd, CRLF, sizeof(CRLF));

    nbytes = read_line(sockfd, recvbuf, MAXLEN - 1);
    recvbuf[nbytes] = 0;
    printf("Am primit: %s", recvbuf);

    if (strstr(recvbuf, expected) != recvbuf) {
        printf("Am primit mesaj de eroare de la server!\n");
        exit(-1);
    }
}

int main(int argc, char **argv) {
    int sockfd;
    int port = SMTP_PORT;
    char server_ip[INET_ADDRSTRLEN];
    char sendbuf[MAXLEN]; 
    char recvbuf[MAXLEN];

    if (argc != 3) {
        printf("Utilizare: ./send_msg adresa_server nume_fisier\n");
        exit(-1);
    }

    strncpy(server_ip, argv[1], INET_ADDRSTRLEN);

    // Conecteaza-te la server
    sockfd = open_connection(server_ip, port, AF_INET, SOCK_STREAM, 0);

    // se primeste mesajul de conectare de la server
    read_line(sockfd, recvbuf, MAXLEN -1);
    printf("Am primit: %s\n", recvbuf);

    // se trimite comanda de HELO
    sprintf(sendbuf, "HELO localhost");
    send_command(sockfd, sendbuf, "250");

    // trimiteti comanda de MAIL FROM
    sprintf(sendbuf, "MAIL FROM: <");
    strcat(sendbuf, "costa@ASUS-TUF-A15");
    strcat(sendbuf, ">");
    send_command(sockfd, sendbuf, "250");

    // trimiteti comanda de RCPT TO
    sprintf(sendbuf, "RCPT TO: <");
    strcat(sendbuf, "root@localhost");
    strcat(sendbuf, ">");
    send_command(sockfd, sendbuf, "250");

    // trimiteti comanda de DATA
    sprintf(sendbuf, "DATA");
    send_command(sockfd, sendbuf, "354");

    // TODO 5: trimiteti e-mail-ul (antete + corp + atasament)
    sprintf(sendbuf, "MIME-Version: 1.0\r\n");
    strcat(sendbuf, "From: <costa@ASUS-TUF-A15>\r\n");
    strcat(sendbuf, "To: <root@localhost>\r\n");
    strcat(sendbuf, "Subject: Laborator\r\n");
    strcat(sendbuf, "Content-Type: multipart/mixed; boundary=abc\r\n");
    strcat(sendbuf, "\r\n--abc\r\n");
    strcat(sendbuf, "Content-Type: text/plain\r\n");
    strcat(sendbuf, "\r\n");
    strcat(sendbuf, "Hello world! This is content\r\n Bye World\r\n");
    strcat(sendbuf,"\r\n--abc\r\n.");
    strcat(sendbuf, "Content-Type: text/plain\r\n");
    strcat(sendbuf, "Content-Disposition: attachment; filename=\"/");
    strcat(sendbuf, argv[2]);
    strcat(sendbuf, "\"\r\n\r\n");

    int fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
        exit(-1);
    }
    while (1) {
        int bytes = read(fd, sendbuf, MAXLEN);
        if (bytes <= 0) {
            break;
        }
        write(sockfd, sendbuf, bytes);
    }
    close(fd);

    strcat(sendbuf, "\r\n--abc--\r\n");
    send_command(sockfd, sendbuf, "250");

    // trimiteti comanda de QUIT
    sprintf(sendbuf, "QUIT");

    // inchideti socket-ul TCP client
    close(sockfd);

    return 0;
}
