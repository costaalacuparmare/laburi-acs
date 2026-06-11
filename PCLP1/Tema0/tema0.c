#include <stdio.h>
#include "var.h"

int main() {
        int elem_max = 0;
        printf("Introduceti valoarea numarului natural N:\n");
        scanf("%d", &elem_max);

        for (int elem_crt = 0; elem_crt <= elem_max; elem_crt++) {
                if (elem_crt != 0) {
                        if (elem_crt % DIVIZOR1 == 0 && elem_crt % DIVIZOR2 == 0) {
                                printf("TrickOrTreat");
                        } else {
                                if (elem_crt % DIVIZOR1 == 0) {
                                        printf("Trick");
                                } else {
                                        if (elem_crt % DIVIZOR2 == 0)
                                                printf("Treat");
                                        else
                                                printf("%d", elem_crt);
                                  }
                          }
                if ( elem_crt < elem_max)
                        printf(" ");
                }
        }
        return 0;
}
