build:
		gcc -g -std=c99 -o quadtree main.c functions.c task1.c task2.c task3.c
run:
		./quadtree -d tests/input/test10_c2.out quadtree.ppm
clean:
		rm quadtree
		rm *.out *.ppm
valgrind:
		valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./quadtree