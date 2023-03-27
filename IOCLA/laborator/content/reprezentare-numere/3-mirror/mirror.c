#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DONE
/* inversare poz cu poz opusa
a unui sir cu operatii pe biti*/

void mirror(char *s)
{
	char aux;
    int len = strlen(s);
    int mirror_id = 0;
    for( int i = 0; i < (len >> 1); i++) {
        mirror_id = len - i - 1;
        aux = *(s + i);
        *(s + i) = *(s + mirror_id);
        *(s + mirror_id) = aux;
    }
    printf("%s\n",s);
}

int main(void)
{
    char *s = (char *) malloc(512 * sizeof(char));
    if (!s) {
        printf("Eroare malloc!!\n");
        return 0;
    }
    strcpy(s,"AnaareMere");
    printf("mirror(\"%s\") = ", s);
    mirror(s);
    free(s);
    s = NULL;
	return 0;
}

