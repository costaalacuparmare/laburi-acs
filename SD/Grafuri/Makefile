CC = gcc
CFLAGS = -Wall -g

build: graf

graf: graf-L.c test-graf.c
	$(CC) $(CFLAGS) $^ -o $@

run:
	./graf

.PHONY: clean
clean:
	rm -f *.o *~ graf
