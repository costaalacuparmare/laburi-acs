CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = converter.c
TARGET = main

.PHONY: all build run clean

all: build

build: $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: build
	  ./$(TARGET) $(INPUT) $(OUTPUT)

zip:
	zip -r vcostantinescu2109_324CB_Tema2.zip $(SRC) converter.h Makefile ../README.md

clean:
	rm -f $(TARGET) *.o