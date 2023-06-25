#include <stdio.h>

int main() {
    int nr = 0, nr_prime = 0;
    scanf("%d", &nr);
    while ( nr >= 0) {
        int contor = 0;
        for ( int div = 2; div <= nr/2; div++)
            if ( nr % div == 0) {
                contor++;
                printf("%d ", div);
            }
        if ( contor == 0) {
            printf("PRIM");
            nr_prime++;
        }
        printf("\n");
        scanf("%d", &nr);            
    }
    printf("S-au gasit %d numere prime.\n", nr_prime);
    return 0;
}
