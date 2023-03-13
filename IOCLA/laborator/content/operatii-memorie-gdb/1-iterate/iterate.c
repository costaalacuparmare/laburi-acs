#include <stdio.h>

/*
 * Afisati adresele elementelor din vectorul "v" impreuna cu valorile
 * de la acestea.
 * Parcurgeti adresele, pe rand, din octet in octet,
 * din 2 in 2 octeti si apoi din 4 in 4.
 */

int main(void)
{
	int v[] = {0xCAFEBABE, 0xDEADBEEF, 0x0B00B135, 0xBAADF00D, 0xDEADC0DE};
    int n;
    // pentru a afisa din 4 in 4 octeti
    int *p =  v;
    n = 0;
    while(n < 5*sizeof(int)) {
        printf("%p -> 0x%x\n", p, *p);
        p+=1;
        n+=4;
    }
    printf("\n");
    //pentru a afisa din 2 in 2 octeti
    unsigned short *p1 = (unsigned short *) v;
    n = 0;
    while(n < 5*sizeof(int)) {
        printf("%p -> 0x%x\n", p1 , *p1);
        p1+=1;
        n+=2;
    }
    return 0;
}
