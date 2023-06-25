#include <stdio.h>

int main() { 
    int n, v[100], k = 0;
    scanf("%d", &n);
    int max = 0;
    scanf("%d", &v[0]);
    int min = v[0];
    for ( int i = 1; i < n; i++)
        scanf("%d", &v[i]);
    for ( int i = 0; i < n; i++) {
        if ( v[i] > max)
            max = v[i];
        if ( v[i] < min)
            min = v[i];
    }
    for ( int i = 0; i < n; i++)
        if ( v[i] == max - min) {
            printf("%d", v[i]);
            k = 1;
        }
    if (!k)
        printf("0");
    printf("\n");
    return 0;
}
