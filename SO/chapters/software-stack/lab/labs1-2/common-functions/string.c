/* SPDX-License-Identifier: BSD-3-Clause */

#include "string.h"

unsigned long strlen(const char *s)
{
	unsigned long len;

	for (len = 0; *s != '\0'; s++, len++) { }

	return len;
}

char *strcpy(char *dest, const char *src)
{
	char *d;

	for (d = dest; *src != '\0'; src++, d++)
		*d = *src;
	*d = *src;

	return dest;
}

char *strcat(char *dest, const char *src)
{
    char* ptr = dest + strlen(dest);
    while (*src != '\0') {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}