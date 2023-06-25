#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define MAX_STUD 30
 /*
 fisiere
    FILE *fp = fopen("fis.txt","r");
    if (!fp) return NULL/...;
    fclose(fp);
    ulimit -n: arata limitarea numarului de fisiere

    fseek (FILE *pFile, long offset, int whence) - repoz pointer la o anumita poz in fisier
    whence: MACRO-uri: SEEK_END (=2), SEEK_CUR (=1), SEEK_SET(=0)
    offset: dif de unde suntem si inceputul fis
    ftell(FILE *pfile) - returneaza pozitia actuala
 */
 /*
CLI param
    int main(int argc, char **argv)
    int a = atoi(argv[1]); //atoi = ascii
    strtok(char*,endptr,10)
    is_number(...)
 */
 /*
 Param variabili
    #include <stdarg.h>
    void list_args(int first,...)
    va_list args;
    va_start (args, first);
    do {
        int current = first;
        ...
        curent = va_arg(args, int);
    } while (current ...);
    va_end(args);
 */

 typedef struct data {
     int zi, luna, an;
 } data;

typedef struct student {
    char nume_stud[MAX_STUD];
    data d_nastere;
    float medie;
} student;

 void ex3_lab12 () {
     FILE *fp = fopen("fis","w");
     if (!fp) printf("Eroare la citire fisier\n");
     student *stud;
     stud = (student*) malloc(sizeof(student));
     if(!stud) printf("Error of malloc\n");
     stud->d_nastere.zi = 19;
     stud->d_nastere.an = 2003;
     stud->d_nastere.luna = 1;
     stud->medie = (float) 9.5;
     strcpy(stud->nume_stud,"Mihai Eminescu");
     printf("%s\n",stud->nume_stud);
     fprintf(fp,"%s",stud->nume_stud);
     //fwrite(stud,sizeof(student),1,fp);
     fclose(fp);
     free(stud);
 }

 int cmp (const void *a, const void *b) {
     return a - b;
 }

 int main ( int argc, char** argv) {
     if ( argc < 2) {
         printf("Gigele, cel putin doua\n");
         return -1;
     }
    for ( int i = 1; i < argc; i++)
        if( is_num()
        //tre sa iau atoi si sa pun intr-un vector local
     qsort(argv, argc, sizeof(char), cmp);

 }

 /*int main() {
    ex3_lab12();
    return 0;
}
*/