#include <stdio.h>

int main () {
    int a[100][100], b[100][100];
    int lina, cola, linb, colb;
    int p = 0;
    scanf("%d%d",&lina,&cola);
    for ( int i = 0; i < lina; i++)
        for ( int j = 0; j < cola; j++)
            scanf("%d",&a[i][j]);
    scanf("%d%d", &linb, &colb);
    for ( int i = 0; i < linb; i++)
        for ( int j = 0; j < colb; j++)
            scanf("%d",&b[i][j]);
    if ( cola != linb)
        printf("Nu se poate efectua operatia de inmultire cu aceste matricE!\n");
    if ( cola == linb) {
        printf("A * B\n");
        for ( int i = 0; i < lina; i++) {
            for ( int j = 0; j < colb; j++) {
                p = 0;
                for ( int k = 0; k < cola; k++)
                    p += a[i][k] * b[k][j]; 
                printf ("%d ",p);
            }
            printf("\n");
         }
    }
    if ( colb == lina) {
        printf("B * A\n");
        for ( int i = 0; i < linb; i++) {
             for ( int j = 0; j < cola; j++) {
                p = 0;
                for ( int k = 0; k < colb; k++)
                    p += b[i][k] * a[k][j]; 
                printf ("%d ",p);
            }
            printf("\n");
         }
    }
return 0;
}            
