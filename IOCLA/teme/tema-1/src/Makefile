CC = gcc
CFLAGS = -Wall -g

build: main

main: main.o operations.o functions.o
	$(CC) -o main $^ 

main.o: main.c
	$(CC) $(CFLAGS) -c $^

operations.o: operations.c
	$(CC) $(CFLAGS) -c $^

functions.o: functions.c
	$(CC) $(CFLAGS) -c $^

run: build
	./main ../checker/input/sensors_clear_easy_1.dat

clean:
	rm -f *.o main
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main