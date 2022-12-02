#include <stdio.h>
#include <stdlib.h>

int nr_div(int x) {
    int d = 2;
    for ( int i = 2 ; i < x/2; i++)
        if ( x % i == 0 )
            d ++; 
    return d;
}

int cmp (const void * x, const void * y) {
   int * p1 = (int *) x;
   int * p2 = (int *) y;
   return nr_div(*p1) - nr_div(*p2);
}

int main () {
    int n, v[1000], x = 0, c = 0;
    scanf("%d", &n);
    for ( int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    qsort( v, n, sizeof(int), cmp);
    printf("\n");
    for ( int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}
