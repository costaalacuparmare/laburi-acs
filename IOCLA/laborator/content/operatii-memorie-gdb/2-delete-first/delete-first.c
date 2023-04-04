#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* delete_first(char *s, char *pattern) {
    int len_pattern = strlen(pattern);
    char *p = strstr(s, pattern);
    if (!p) return strdup(s);
    int lenbef = p - s;
    char *q = (char *) malloc (strlen(s) + 1 - len_pattern);
    if (!q) return strdup(s);
    strncpy(q,s,lenbef);
    strcpy(q + lenbef, p + len_pattern);

    return q;
}

int main(void)
{
	char *s = "Ana are mere";
	char *pattern = "re";
    printf("%s\n", delete_first(s,pattern));
	return 0;
}
