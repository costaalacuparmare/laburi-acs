#include <stdio.h>

int is_even(int n) {
    int mask = 1;
    return n & mask;
}

int pow2( int n) {
    int nr = 1;
    return nr << n;
}

int flip_bits(int n) {
    return ~n;
}

void print_bits(int n) {
    unsigned int mask = 1 << 31;
    printf("%d in cod binar este: ", n);
    while ( mask != 0) {
        if(n & mask)
            printf("1");
        else
            printf("0");
        mask = mask >> 1;
    }
    printf("\n");
}

int is_power2( int n) {
    unsigned int mask = 1 << 31;
    int contor = 0;
    while ( mask != 0) {
        if(n & mask)
            contor ++;
        mask = mask >> 1;
    }
    if( contor == 1)
        return 1;
    else
        return 0;
}

int main() {
    int n = 5;
    if(is_even(n))
        printf("%d este impar\n", n);
    else
        printf("%d este par\n", n);
    printf("Nr la puterea %d este %d\n", n, pow2(n));    
    printf("Nr inversat pe biti este %d\n", flip_bits(n));
    print_bits(n);
    if( is_power2(n) == 1)
        printf("%d este puterea lui 2\n", n);
    else
        printf("%d nu este puterea lui 2\n", n);
    return 0;
}
