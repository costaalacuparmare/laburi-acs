build:
		gcc -g -std=c99 -o tema3 main.c functions.c task1.c task2.c
run:
		./tema3 2
clean:
		rm tema3
		rm *.out
valgrind:
		valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./tema3