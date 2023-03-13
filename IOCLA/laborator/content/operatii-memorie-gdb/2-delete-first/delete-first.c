#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *delete_first(char *s, char *pattern)
{
    //okeiut
    if(strstr(s,pattern))
    {
        char *t = s;
        int i = 0;
        while(i != (strlen(s)-1))
        {
            if(strstr(t+i-(strlen(t)-strlen(pattern)),pattern) != 0)
                i++;
            else
                break;
        }
        strcpy(s+i,s+i+2);

    }
    printf("%s",s);
}

int main(void)
{
	/*
	 * TODO: Este corectă declarația variabilei s în contextul în care o să apelăm
	 * funcția delete_first deasupra sa? De ce? Modificați dacă este cazul.
	 */
	char s[] = "Ana are mere";
	char *pattern = "re";
    delete_first(s,pattern);
	// Decomentați linia după ce ați implementat funcția delete_first.
	// printf("%s\n", delete_first(s, pattern));

	return 0;
}
