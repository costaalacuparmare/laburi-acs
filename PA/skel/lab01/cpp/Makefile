CC = g++
CFLAGS = -Wall -Wextra -std=c++17

build:
	$(CC) $(CFLAGS) task-1/main.cpp
	$(CC) $(CFLAGS) struct.cpp -o struct
	$(CC) $(CFLAGS) class.cpp -o class
	$(CC) $(CFLAGS) constructor.cpp -o constructor
	$(CC) $(CFLAGS) template.cpp -o template

.PHONY: clean
clean:
	rm -f gigel
	rm -f struct
	rm -f class
	rm -f constructor
	rm -f template
