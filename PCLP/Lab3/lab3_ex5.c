#include <stdio.h>

int main() {
    long long int nr = 0, invers = 0;
    scanf("%lld", &nr);
    long long int cp = nr;
    while ( cp != 0) {
        invers = invers * 10 + cp % 10;
        cp /= 10;
    }
    if ( invers == nr)
        printf("Numar este palindorm\n");
    else
        printf("Numarul nu este palindrom\n");
    return 0;
}
