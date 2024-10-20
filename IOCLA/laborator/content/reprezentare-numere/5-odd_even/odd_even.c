#include <stdio.h>
#include <stdlib.h>

//DONE
/* verifica paritatea numarului, daca e par il afiseaza binar,
daca nu, il afiseaza hexazecimal */

void print_binary(int number, int nr_bits)
{
	int i;
    char *bits;

    bits = (char *) malloc(sizeof(char) * nr_bits);

    for (i = 0; i< nr_bits; i++) {
        *(bits+i) = 1 & number;
        number >>= 1;
    }

    printf("0b");
    for( i = nr_bits - 1; i >= 0; i--) {
        printf("%d", *(bits + i));
    }
    printf("\n");

    free(bits);
}

void check_parity(int *numbers, int n) {
    int i, curr_nr;

    for (i = 0; i < n; i++) {
        curr_nr = *(numbers + i);
        printf("%5d: ", curr_nr);
        if (curr_nr & 1)
            printf("0x%x\n", curr_nr);
        else
            print_binary(curr_nr, 8);
    }
}

int main(void)
{
	int *numbers, i, *n;

    n = (int *) malloc(sizeof(int));

    printf("Size of array: "); scanf("%d", n);

    numbers = (int *) malloc(sizeof(int) * (*n));

    for (i = 0; i < *n; i++) {
        printf("Number %d: ", i + 1);
        scanf("%d", numbers + i);
    }

    check_parity(numbers, *n);
    free(n);
    free(numbers);
	return 0;
}

