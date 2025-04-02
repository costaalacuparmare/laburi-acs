CC = g++
CFLAGS = -Wall -g

all: server subscriber

server:
	$(CC) $(CFLAGS) -o server server.cpp

subscriber:
	$(CC) $(CFLAGS) -o subscriber tcp_client.cpp

.PHONY: clean

zip:
	zip -r archive.zip Makefile server.cpp tcp_client.cpp common.h readme.txt

clean:
	rm -f server subscriber
