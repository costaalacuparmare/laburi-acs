#include <stdio.h>

int main() {
    unsigned int N = 0, Smax= 0, Nmax = 0;
    printf("N=");
    scanf("%d", &N);
    for ( int i = 3; i < N; i++) {
        int Sd = 0;
        for ( int d = 2; d <= i/2; d++)
            if ( i % d == 0)
                Sd += d;
        if ( Sd >= Smax) {
            Smax = Sd;
            Nmax = i;
        }
    }
    printf("%d\n", Nmax);
    return 0;
}
