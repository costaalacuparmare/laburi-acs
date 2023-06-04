#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {	
        srand ( (unsigned)time(NULL));
	for ( int crt = 0; crt < 5; crt ++)
		printf ( "%d ", rand());
	printf ( "\n");
	return 0;
}
