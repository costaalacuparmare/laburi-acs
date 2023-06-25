#include <stdio.h>
#include <math.h>

int main () {

    double a = 1, b = 2, c = -3, u = -3, v = 7;
    double delta = b * b - 4 * a * c;
    double ftcu = a*u*u + b*u + c;
    double ftcv = a*v*v + b*v + c;
    double p = 0, f = 0;
    if ( a < 0) {
        double p = (-delta)/(4*a);
        f = ftcu > ftcv ? ftcu : ftcv;
        printf("valoare maxima a functiei este %f, iar valoarea minima %f\n", f, p);
    }
    else {
        double p = (-delta)/(4*a);
        f = ftcu > ftcv ? ftcv : ftcu;
        printf("valoare maxima a functiei este %f, iar valoarea minima %f\n", p, f);
    }
    double x1 = (-b + sqrt(delta)) / (2*a);
    double x2 = (-b - sqrt(delta)) / (2*a);
    printf("radacinile din intervalul [%f,%f] sunt %f, %f.\n", u, v, x1, x2);
    return 0;
} 
