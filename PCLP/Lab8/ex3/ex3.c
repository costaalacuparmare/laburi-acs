#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    double x = 2;
    double tablou[100] = {sqrt(x), sin(x), cos(x), tan(x), exp(x), log(x)};
    int i = 0;
    while (tablou[i] != '\0');
        printf("%lf ",tablou[i]);
    printf("\n");
    return 0;
}
