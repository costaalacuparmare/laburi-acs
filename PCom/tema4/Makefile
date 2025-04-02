CC=gcc
CFLAGS=-I.

client: client.c requests.c helpers.c buffer.c parson.c
	$(CC) -o client client.c requests.c helpers.c buffer.c parson.c -Wall

run: client
	./client

valgrind: client
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./client < in

archive:
	zip -r 324CB_Constantinescu_Vlad_Tema4PC.zip *.c *.h Makefile README.md

clean:
	rm -f *.o client
