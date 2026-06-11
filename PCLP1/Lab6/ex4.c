#include <stdio.h>

int main () {
    int a[100][100];
    int dim;
    scanf("%d",&dim);
    for ( int i = 0; i < dim; i++)
        for ( int j = 0; j < dim; j++)
            scanf("%d",&a[i][j]);
    for ( int i = 0; i < dim; i++) {
            for ( int j = 0; j < dim; j++)
                if ( i <= j && i+j <= dim+1)
		            printf("%d ",a[i][j]);
    printf("\n");
    }
return 0;
}
