#include <stdio.h>

int main () {
    int v[100] = {0};
    int i = 0, x = 0;;
    while ( i != 20) {
        scanf("%d",&x);
        if  ( x > 0)
            v[i++] = x;
        else
            break;
    }
    for ( int j = 0; j < i; j++)
        if ( v[j] > j)
            printf("%d ", v[j]);
    printf("\n");
    return 0;
}
