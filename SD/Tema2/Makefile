build:
		touch quadtree.ppm
		gcc -g -o quadtree main.c functions.c task1.c task2.c task3.c
run:
		./quadtree -c1 1000 tests/input/test5.ppm quadtree.out
clean:
		rm quadtree
		rm *.out quadtree.ppm
valgrind:
		valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./quadtree