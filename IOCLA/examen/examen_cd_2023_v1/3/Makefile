CFLAGS = -Wall -Wextra -m32 -Iinclude -fno-stack-protector -mpreferred-stack-boundary=2 -fno-PIC
LDFLAGS = -m32 -no-pie

# TODO compile main with task2
all: main.o secret.o
	$(CC) $(CFLAGS) $^ -o main

main.o: main.c
	$(CC) $(CFLAGS) $^ -c

# TODO add rule for task2

clean:
	rm task2.o main.o main