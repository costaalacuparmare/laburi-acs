#include <stdio.h>
#include "flab4.h"

int fact_i ( int n) {
    if ( n == 0)
        return 1;
    int fact = 1;
    while ( n != 0) {
        fact *= n;
        n--;
    }
    return fact;
}

int fact_r ( int n) {
    if ( n == 0)
        return 1;
    return fact_r ( n-1) * n;
}

int sumcif_i ( int n) {
    int suma = 0;
    while ( n!=0) {
        suma += n % 10;
        n /= 10;
    }
    return suma;
}

int sumcif_r ( int n) {
    if ( n == 0)
        return 0;
    return n % 10 + sumcif_r ( n/10);
}

int prim ( int n) {
    if ( n == 0 || n == 1)
        return 0;
    for ( int div = 2; div < n/2; div++)
        if ( n % div == 0)
            return 0;
    return 1;
}

int palindrom( int n) {
    int cp = n;
    int r = 0;
    while ( cp != 0) {
        r = r * 10 + (cp % 10);
        cp /= 10;
    }
    return n == r ? 1 : 0;
}

void divpalindrom ( int n) {
    int contor = 0;
    printf("Divizori Palindrom: ");
    for ( int div = 2; div <= n/2; div++)
        if ( n % div == 0 && palindrom(div) == 1) {
            contor++;
            printf("%d ", div);
        }
    printf("\nNumarul de Divizori Palindrom: %d\n", contor);
}

void sirprim ( int contor) {
    int n = 0;    
    scanf("%d",&n);
    if ( n == 0) {
        printf("Sunt %d numere prime printre numerele pozitive citite\n", contor);
        return;
    }
    if ( n < 0 || prim ( n) ==0)
            sirprim ( contor);
    if ( prim ( n) == 1)
            sirprim ( contor+1);
}
