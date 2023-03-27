#include <stdio.h>
#include <stdlib.h>

/* checks if the array is sorted */
static int is_sorted(int a[], int n)
{
	int i;

	for (i = 1; i < n; i++)
		if (a[i] < a[i-1])
			return 0;

	return 1;
}

/* shuffle an array */
static void shuffle(int a[], int n)
{
	int i;
	int t, r;

	for (i = 0; i < n; i++) {
		t = a[i];
		r = rand() % n;
		a[i] = a[r];
		a[r] = t;
	}
}

int main(void)
{
	int numbers[] = {1, 13, 2,  5, 3, -7};
	int i = 0;

	while (1) {
		shuffle(numbers, 6);

		if (is_sorted(numbers, 6))
			goto for_label;
	}

for_label:
	printf("%d ", numbers[i]);
    i++;
    if ( i >= 6) {
        printf("\n");
        goto exit;
    }
    goto for_label;

exit:
	return 0;
}
