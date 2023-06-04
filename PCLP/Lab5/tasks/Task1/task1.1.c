#include <stdio.h>
#include <stdlib.h>

int main () { 
    int n, v[100];
    scanf("%d", &n);
    for ( int i = 0; i < n ; i++)
        scanf("%d", &v[i]);
    for ( int i = 0; i < n; i++)
        if ( v[i] % v[n-1] == 0)
            printf("%d ", v[i]);
    return 0;
}
