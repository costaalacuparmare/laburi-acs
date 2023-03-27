#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* delete_first(char *s, char *pattern) {
    int len_pattern = strlen(pattern);
    char *p = strstr(s, pattern);
    if (!p) return s;
    char *q = p + len_pattern;
    while (*q != '\0') {
        *p = *q;
        p++;
        q++;
    }

    *p = '\0';

    return s;
}

int main(void)
{
	char *s = "Ana are mere";
	char *pattern = "re";
    printf("%s\n", delete_first(s,pattern));
	return 0;
}
