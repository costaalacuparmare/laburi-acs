/*  & = op. referentiere * = adresa dereferentiere (afis ce se afla in adrs x)
    functie cu pointer: int (*p) (int) = foo; *p(2);
    DIMENSIUNE / ALECOARE pointer:
    1) int *p; p = malloc( 100 * sizeof ( int)) if p ( p ==NULL) return fail;
    2) p = calloc ( 100, sizeof ( int));
    NEALOCARE pointer:
    free ( p);
    pentru modificare intr-o fct: foo( int * x) blabla int main() { int x; foo ( &x);
*/


