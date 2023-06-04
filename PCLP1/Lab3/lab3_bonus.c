#include <stdio.h>

int main() {
    int N = 0, x = 0, cmmdc = 0;
    scanf("%d", &N);
    scanf("%d%d", &x, &cmmdc);
    while ( x != cmmdc)
        if ( x > cmmdc)
            x -= cmmdc;
        else
            cmmdc -= x;
    
    for ( int i = 0; i < N-2; i++) {
        scanf("%d", &x);
        while ( x != cmmdc)
        if ( x > cmmdc)
            x -= cmmdc;
        else
            cmmdc -= x;
    }
    printf("Cel mai mare divizor comun al celor %d este %d\n", N, cmmdc);
    return 0;
}
        
        
