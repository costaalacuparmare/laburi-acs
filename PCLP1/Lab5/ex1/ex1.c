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
    int contor = 0;
    for ( int j = 0; j < i; j++) {
        printf("%d : %d\n", j, v[j]);
        if ( v[j] % 2 != 0)
            contor++;
    }
    printf("Numar elemente impare: %d\n", contor);
    return 0;
}
