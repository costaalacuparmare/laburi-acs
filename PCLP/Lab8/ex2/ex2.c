//fct string
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_length(char *s) {
    int contor = 0;
    int i = 0;
    while ( s[i] != '\0') {
        contor ++;
        i ++;
    }
    return contor;
}

char * strdel(char *s, int pos, int n) {
    strcpy(s+pos,s+pos+n);
    return s;
}

char * strins (char *s1, int pos, char *s2) {
    char *t = malloc ( 100 * sizeof( char));
    strcpy(t,s1+pos+1);
    strcpy(s1+pos+1,s1+str_length(s1)+1);
    strcat(s1,s2);
    strcat(s1,t);
    return s1;
}

int eq_mask(char *sir, char *masca) {
    if ( str_length(sir) != str_length(masca))
        return 0;
    for ( int i = 0; i < str_length(sir); i++)
        if ( masca[i] != '?' && masca[i] != sir[i])
            return 0;
    return 1;
}   

int eqcuv(char *cuv, char **tablou) {
    int i = 0;
    while ( tablou[i] != '\0') {
        if ( strcmp(tablou[i],cuv) == 0)
            return 1;
        i++;
    }
    return 0;
}
 
int main () {
    char *s1 = malloc (20);
    char *s2 = malloc(20);
    char *s = malloc(20);
    char *sir = malloc ( 100 * sizeof ( char));
    char *masca = malloc ( 100 * sizeof ( char));
	char *tablou[100] = {"curs1", "curs2", "curs3"};
	char *cuv1 = "curs2", *cuv2 = "curs5";
	printf("curs2 %s in tablou\n",(eqcuv(cuv1, tablou)) ? "este" : "nu este");
	printf("curs5 %s in tablou\n",(eqcuv(cuv2, tablou)) ? "este" : "nu este");
	return 0;	
}
