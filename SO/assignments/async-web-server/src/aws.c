// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>
#include <sys/eventfd.h>
#include <libaio.h>
#include <errno.h>

#include "aws.h"
#include "utils/util.h"
#include "utils/debug.h"
#include "utils/sock_util.h"
#include "utils/w_epoll.h"

/* server socket file descriptor */
static int listenfd;

/* epoll file descriptor */
static int epollfd;

static int aws_on_path_cb(http_parser *p, const char *buf, size_t len)
{
	struct connection *conn = (struct connection *)p->data;

	memcpy(conn->request_path, buf, len);
	conn->request_path[len] = '\0';
	conn->have_path = 1;

	return 0;
}

static void connection_prepare_send_reply_header(struct connection *conn)
{
	/* prepare the connection buffer to send the reply header. */
	conn->send_len = snprintf(conn->send_buffer, BUFSIZ, "HTTP/1.1 200 OK\r\n"
														 "Content-Type: text/html\r\n"
														 "Content-Length: %ld\r\n"
														 "Connection: keep-alive\r\n"
														 "\r\n", conn->file_size);
	conn->state = STATE_SENDING_HEADER;
}

static void connection_prepare_send_404(struct connection *conn)
{
	/* prepare the connection buffer to send the 404 header. */
	conn->send_len = snprintf(conn->send_buffer, BUFSIZ, "HTTP/1.1 404 Not Found\r\n"
														 "Content-Type: text/html\r\n"
														 "Content-Length: 0\r\n"
														 "Connection: keep-alive\r\n"
														 "\r\n");
	conn->state = STATE_SENDING_404;
}

static enum resource_type connection_get_resource_type(struct connection *conn)
{
	/* get resource type depending on request path/filename: static, dynamic or none. */
	if (strstr(conn->request_path + 1, AWS_REL_STATIC_FOLDER) == conn->request_path + 1)
		conn->res_type = RESOURCE_TYPE_STATIC;
	else if (strstr(conn->request_path + 1, AWS_REL_DYNAMIC_FOLDER) == conn->request_path + 1)
		conn->res_type = RESOURCE_TYPE_DYNAMIC;
	else
		conn->res_type = RESOURCE_TYPE_NONE;

	return conn->res_type;
}

struct connection *connection_create(int sockfd)
{
	/* initialize connection structure on given socket. */
	struct connection *conn = calloc(1, sizeof(struct connection));

	conn->sockfd = sockfd;
	return conn;
}

void connection_start_async_io(struct connection *conn)
{
	/* start asynchronous operation on connection socket. */
	conn->ctx = 0;
	io_setup(1, &conn->ctx);
	if (conn->file_size - conn->file_pos < BUFSIZ)
		conn->send_len = conn->file_size - conn->file_pos;
	else
		conn->send_len = BUFSIZ;
	io_prep_pread(&conn->iocb, conn->fd, conn->send_buffer, conn->send_len, conn->file_pos);
	conn->piocb[0] = &conn->iocb;
	io_submit(conn->ctx, 1, conn->piocb);
}

void connection_remove(struct connection *conn)
{
	/* remove connection handler. */
	int rc = w_epoll_remove_ptr(epollfd, conn->sockfd, conn);

	DIE(rc < 0, "w_epoll_remove_ptr");

	close(conn->sockfd);

	/* closes the file descriptor if it was opened */
	if (conn->fd)
		close(conn->fd);

	free(conn);
}

void handle_new_connection(void)
{
	/* handle a new connection request on the server socket. */
	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr;
	struct connection *conn;

	/* accept new connection. */
	int sockfd = accept(listenfd, (SSA *) &addr, &addrlen);

	DIE(sockfd < 0, "accept");

	/* set socket to be non-blocking. */
	fcntl(sockfd, F_SETFL, O_NONBLOCK);

	/* instantiate new connection handler. */
	conn = connection_create(sockfd);

	/* add socket to epoll. */
	w_epoll_add_ptr_in(epollfd, sockfd, conn);

	/* initialize HTTP_REQUEST parser. */
	http_parser_init(&conn->request_parser, HTTP_REQUEST);

	conn->request_parser.data = conn;

	/* debug log */
	dlog(LOG_DEBUG, "New connection accepted. Socket: %d\n", sockfd);
}

void receive_data(struct connection *conn)
{
	/* receive message on socket stored in recv_buffer in struct connection. */
	char *rc = NULL;

	while (!(rc = strstr(conn->recv_buffer, "\r\n\r\n"))) {
		char buffer[BUFSIZ] = {0};
		ssize_t bytes_recv = recv(conn->sockfd, buffer, BUFSIZ, 0);

		DIE(bytes_recv < 0, "recv");
		conn->recv_len += bytes_recv;
		if (bytes_recv == 0) {
			conn->state = STATE_CONNECTION_CLOSED;
			return;
		}
		strcat(conn->recv_buffer, buffer);
	}
	/* debug log */
	dlog(LOG_DEBUG, "Received data from socket %d. Data: %s\n", conn->sockfd, conn->recv_buffer);
	rc[4] = 0;
	conn->recv_len = strlen(conn->recv_buffer);
	conn->state = STATE_REQUEST_RECEIVED;
	parse_header(conn);
}

int connection_open_file(struct connection *conn)
{
	/* open file and update connection fields. */
	conn->fd = open(conn->request_path + 1, O_RDONLY);
	if (conn->fd < 0) {
		perror("open");
		return -1;
	}

	/* debug log */
	dlog(LOG_DEBUG, "Opening file: %s\n", conn->request_path + 1);

	struct stat st;

	fstat(conn->fd, &st);
	conn->file_size = st.st_size;
	return conn->fd;
}

void connection_complete_async_io(struct connection *conn)
{
	/* complete asynchronous operation on connection socket. */
	struct io_event events[1];
	int rc = io_getevents(conn->ctx, 1, 1, events, NULL);

	DIE(rc < 0, "io_getevents");
	connection_send_data(conn);
}

int parse_header(struct connection *conn)
{
	/* parse the HTTP header and extract the file path. */
	http_parser_settings settings_on_path = {
			.on_message_begin = 0,
			.on_header_field = 0,
			.on_header_value = 0,
			.on_path = aws_on_path_cb,
			.on_url = 0,
			.on_fragment = 0,
			.on_query_string = 0,
			.on_body = 0,
			.on_headers_complete = 0,
			.on_message_complete = 0
	};
	http_parser_execute(&conn->request_parser, &settings_on_path,
						conn->recv_buffer, conn->recv_len);
	connection_get_resource_type(conn);
	return conn->have_path;
}

enum connection_state connection_send_static(struct connection *conn)
{
	/* send static data using sendfile */
	off_t offset = 0;
	ssize_t sent = 0;

	while (conn->send_len < conn->file_size) {
		sent = sendfile(conn->sockfd, conn->fd, &offset, conn->file_size);

		if (sent == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
			perror("sendfile");
			return -1;
		}
		conn->send_len += sent;
	}
	return STATE_DATA_SENT;
}

int connection_send_data(struct connection *conn)
{
	/*
	 * send as much data as possible from the connection send buffer.
	 * returns the number of bytes sent or -1 if an error occurred
	 */

	/* debug log */
	dlog(LOG_DEBUG, "Sending dynamic content asynchronously.\n");

	int rc = 0;
	int sent = 0;

	conn->file_pos += conn->send_len;
	if (conn->file_size - conn->file_pos > 0) {
		rc = w_epoll_update_ptr_inout(epollfd, conn->sockfd, conn);
		DIE(rc < 0, "w_epoll_update_ptr_inout");
	} else {
		conn->state = STATE_DATA_SENT;
	}
	while (conn->send_pos < conn->send_len) {
		sent = send(conn->sockfd, conn->send_buffer + conn->send_pos, conn->send_len - conn->send_pos, 0);
		DIE(sent < 0, "send");
		conn->send_pos += sent;
	}
	conn->send_pos = 0;
	return conn->send_len;
}

int connection_send_dynamic(struct connection *conn)
{
	/* starts an asynchronous operation to send dynamic data. and updates the connection state. */
	if (conn->state != STATE_SENDING_DATA)
		conn->state = STATE_SENDING_DATA;
	connection_start_async_io(conn);
	connection_complete_async_io(conn);
	return 0;
}

void handle_input(struct connection *conn)
{
	/* handle input information: may be a new valid requests or notification */

	/* debug log */
	dlog(LOG_DEBUG, "Parsed HTTP header. Request path: %s\n", conn->request_path);

	switch (conn->state) {
	case STATE_INITIAL:
		/* initial state, receive data from the client */
		receive_data(conn);
		break;
	case STATE_ASYNC_ONGOING:
		/* asynchronous IO ongoing, check for completion */
		connection_complete_async_io(conn);
		break;
	case STATE_REQUEST_RECEIVED:
		/* request received, handle input */
		connection_prepare_send_reply_header(conn);
		w_epoll_update_ptr_inout(epollfd, conn->sockfd, conn);
		break;
	case STATE_SENDING_404:
		/* sending 404, send the 404 header */
		connection_prepare_send_404(conn);
		w_epoll_update_ptr_inout(epollfd, conn->sockfd, conn);
		break;
	default:
		/* invalid state, close the connection */
		printf("shouldn't get here %d\n", conn->state);
		conn->state = STATE_CONNECTION_CLOSED;
		break;
	}
}

void handle_output(struct connection *conn)
{
	/* handle output information: may be a new valid requests or notification */

	/* debug log */
	dlog(LOG_DEBUG, "Sending data to socket %d. Data length: %ld\n", conn->sockfd, conn->send_len);

	ssize_t sent = 0;

	switch (conn->state) {
	case STATE_SENDING_HEADER:
		/* sending header, send the prepared header */
		while (conn->send_pos < conn->send_len) {
			sent = send(conn->sockfd, conn->send_buffer + conn->send_pos, conn->send_len - conn->send_pos, 0);
			DIE(sent < 0, "send");
			conn->send_pos += sent;
		}
		conn->send_pos = 0;
		conn->state = STATE_SENDING_DATA;
		break;
	case STATE_SENDING_DATA:
		/* sending data, send the data */
		if (conn->res_type == RESOURCE_TYPE_DYNAMIC)
			connection_send_dynamic(conn);
		else if (conn->res_type == RESOURCE_TYPE_STATIC)
			conn->state = connection_send_static(conn);
		break;
	case STATE_SENDING_404:
		/* sending 404, send the 404 header */
		while (conn->send_pos < conn->send_len) {
			sent = send(conn->sockfd, conn->send_buffer + conn->send_pos, conn->send_len - conn->send_pos, 0);
			DIE(sent < 0, "send");
			conn->send_pos += sent;
		}
		conn->send_pos = 0;
		conn->state = STATE_DATA_SENT;
		break;
	default:
		/* invalid state, close the connection */
		conn->state = STATE_CONNECTION_CLOSED;
	}
}

void handle_client(uint32_t event, struct connection *conn)
{
	/* handle new client using input and output functions */

	/* debug log */
	dlog(LOG_DEBUG, "Handling events for socket %d. Events: %u\n", conn->sockfd, event);

	if (event & EPOLLOUT) {
		handle_output(conn);
	} else if (event & EPOLLIN) {
		receive_data(conn);
		if (conn->state == STATE_CONNECTION_CLOSED) {
			connection_remove(conn);
			return;
		}
		if (connection_open_file(conn) == -1)
			conn->state = STATE_SENDING_404;
		handle_input(conn);
	}

	if (event & (EPOLLHUP | EPOLLERR))
		conn->state = STATE_CONNECTION_CLOSED;

	if (conn->state == STATE_CONNECTION_CLOSED)
		connection_remove(conn);
}

int main(void)
{
	int rc = 0;

	/* initialized multiplexing. */
	epollfd = w_epoll_create();
	DIE(epollfd < 0, "w_epoll_create");

	/* create server socket. */
	listenfd = tcp_create_listener(AWS_LISTEN_PORT, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	/* add server socket to epoll object */
	rc = w_epoll_add_fd_in(epollfd, listenfd);
	DIE(rc < 0, "w_epoll_add_fd_in");

	/* debug log */
	dlog(LOG_INFO, "Server waiting for connections on port %d\n", AWS_LISTEN_PORT);

	/* server main loop */
	while (1) {
		struct epoll_event rev;

		/* wait for events. */
		rc = w_epoll_wait_infinite(epollfd, &rev);
		DIE(rc < 0, "w_epoll_wait_infinite");

		if (rev.data.fd == listenfd && rev.events & EPOLLIN) {
			/* new connection request */
			handle_new_connection();
		} else {
			/* socket communication */
			handle_client(rev.events, rev.data.ptr);
		}
	}

	return 0;
}
