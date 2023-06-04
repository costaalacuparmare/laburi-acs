//verifica little endian sau big endian
#include <stdio.h>

int main() {
    int x = 0xDEADBEEF;
    char *p = &x;
    printf("%hhx\n", *p);
    char little = 0xEF;
    *p == little ? printf( "Little Endian\n") : printf( "Big Eldian\n"); 
    return 0;
}
