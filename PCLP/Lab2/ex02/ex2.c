#include <stdio.h>
#include <unistd.h>

int main() {
	int numar = 3;
	for ( int numar = 3; numar >=1; numar --) {
		printf ( "%d\n", numar);
		sleep (1);
	}
	return 0;
}
