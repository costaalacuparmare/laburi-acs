#include <stdio.h>

int doisprezece (int nr) {
    unsigned int baza10 = 0;
    int pow2 = 1;
    while ( nr != 0) {
        if ( nr % 10 == 1)
            baza10 += pow2;
        pow2 *= 2;
        nr /= 10;
    }
    return baza10;  
}

int zecespredoi (int nr) {
    unsigned int baza2[32] = {0};
    for ( int i = 0 && nr != 0; i < 31; i++) {
        baza2[i] = nr % 2;
        nr /= 2;
    }
    printf("Numarul in baza 2 este:\n");
    for ( int i = 31; i >= 0; i--)
        printf("%d", baza2[i]);
}

int main() {
    int nr = 0, cp = 0;
    scanf("%d", &nr);
    while ( nr >= 0) {
        printf("Selectati baza in care vreti sa convertiti ( 10 / 2): ");
        scanf("%d",&cp); 
        if ( cp == 10)
            printf("Numar %d in baza 10 este %d.", nr, doisprezece(nr));
        else
            zecespredoi(nr);
        printf(".\nIntorduceti nr. negativ pt. iesire || nr. pozitiv pt. continuare: ");
        scanf("%d",&nr);
    }
    
    return 0;
}
