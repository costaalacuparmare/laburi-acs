#include <stdio.h>

void multiarr( int lina,int cola,int linb,int colb, int a[100][100], int b[100][100], int c[100][100]) {
    for ( int i = 0; i < lina; i++)
            for ( int j = 0; j < colb; j++)
                for ( int k = 0; k < cola; k++)
                    c[i][j] += a[i][k] * b[k][j];
}
int main () {
    int a[100][100], c[100][100], b[100][100];
    int lina, cola, pow;
    int p = 0;
    scanf("%d%d",&lina,&cola);
    for ( int i = 0; i < lina; i++)
        for ( int j = 0; j < cola; j++)
            scanf("%d",&a[i][j]);
    scanf("%d",&pow);
    for ( int i = 0; i < lina; i++)
            for ( int j = 0; j < cola; j++)
                b[i][j] = a[i][j]; 
    if ( cola != lina)
        printf("Operatie invalida\n");
    else {
        while ( pow-1 > 0) {         
        multiarr(lina, cola, lina, cola, b, a, c);
        for ( int i = 0; i < lina; i++)
            for ( int j = 0; j < cola; j++)
                b[i][j] = c[i][j];
        /*for ( int i = 0; i < lina; i++) {
            for ( int j = 0; j < cola; j++)
                printf("%d ",c[i][j]);
            printf("\n");
        }*/
        for ( int i = 0; i < lina; i++)
            for ( int j = 0; j < cola; j++)
                c[i][j] = 0;
        pow--;
        }
        for ( int i = 0; i < lina; i++) {
            for ( int j = 0; j < cola; j++)   
                printf ("%d ",b[i][j]);
            printf("\n");
        }
    }
return 0;
}
