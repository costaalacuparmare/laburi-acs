#include <stdio.h>
#include <stdlib.h>

int prim(int x) {
    if ( x == 0 || x == 1)
        return 0;
    for ( int i = 2 ; i < x; i++)
        if ( x % i == 0 )
            return 0; 
    return 1;
}

int cmp (const void * x, const void * y) {
   return ( *(int*)x - *(int*)y );
}

int main () {
    int n, v[1000], x = 0, c = 0;
    scanf("%d", &n);
    for ( int i = 0; i < n; i++) {
        scanf("%d", &x);
        if(prim(x)) {
            v[c] = x;
            c++;
        }
    }
    qsort( v, c, sizeof(int), cmp);
    for ( int i = 0; i < c; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}
