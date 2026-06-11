#include <stdio.h>

int main() {
	int nr1 = 0, nr2 = 0, nr3 = 0;
	scanf ( "%u%u%u", &nr1, &nr2, &nr3);

	if ( nr1 < nr2 + nr3 && nr2 < nr1 + nr3 && nr3 < nr1 + nr2)
		printf("DA\n");
	else
		printf("NU\n");
	return 0;
}
