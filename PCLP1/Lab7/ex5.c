#include <stdio.h>

#define SET_SIZE 100
typedef unsigned char SET[SET_SIZE];

void insert_in_set(SET s, unsigned int n) {
    unsigned char mask = 1 << n%8;
    s[n / 8] = s[n / 8] | mask;
}

void delete_from_set(SET s, unsigned int n) {
    unsigned char mask = 1 << n%8;
    s[n / 8] = s[n / 8] & ~mask;
}

int is_in_set(SET s, unsigned int n) {
    unsigned char mask = 1 << n%8;
    if (s[n / 8] & mask == 1)
        return 1;
    else
        return 0;
}

void delete_all_from_set(SET s) {
    for ( int i =0; i < SET_SIZE; i++)
        s[i] = s[i] & 0;
}

int card_set(SET s) {
    int card = 0;
    for ( int i = 0; i < SET_SIZE; i++) {
        unsigned char mask = 1 << 31;
        while ( mask != 0) {
            if (s[i] & mask)
                card ++;
            mask = mask >> 1;
        }
    }
    return card;
}

int main() {
    SET s;
    unsigned int n = 0;
    scanf ("%d",&n);
    insert_in_set(s,n);
    // delete_from_set(s,n);
    // is_in_set(s,n)? printf("Da\n") : printf("Nu\n");
    // delete_all_from_set(s);
    printf("%d\n",card_set(s));
    //printf("%hhd",s[n / 8]);
    return 0;
}
