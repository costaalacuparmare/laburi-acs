// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	while (*source != '\0') {
        *destination++ = *source++;
    }
    *destination = '\0';
    return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	while (*source != '\0' && len > 0) {
        *destination++ = *source++;
        len--;
    }
    while (len > 0) {
        *destination++ = '\0';
        len--;
    }
    return destination;
}

char *strcat(char *destination, const char *source)
{
    char* aux_string = destination + strlen(destination);
    while (*source != '\0') {
        *aux_string++ = *source++;
    }
    *aux_string = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
    char* aux_string = destination + strlen(destination);
    while (*source != '\0' && len > 0) {
        *aux_string++ = *source++;
        len--;
    }
    *aux_string++ = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    while (*str1 != '\0' && *str2 != '\0' && len > 1) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
        len--;
    }
    return *str1 - *str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++) {
        continue;
    }
	return i;
}

char *strchr(const char *str, int c)
{
	for(; *str != '\0'; str++) {
        if (*str == c)
            return (char *)str;
    }
	return NULL;
}

char *strrchr(const char *str, int c)
{
	char *aux_char = NULL;
    for (; *str != '\0'; str++) {
        if (*str == c)
            aux_char = (char *)str;
    }
	return aux_char;
}

char *strstr(const char *haystack, const char *needle)
{
	for (; *haystack != '\0'; haystack++) {
        if (*haystack == *needle) {
            const char* aux_haystack = haystack;
            const char* aux_needle = needle;
            while (*aux_haystack == *aux_needle && *aux_needle != '\0') {
                aux_haystack++;
                aux_needle++;
            }
            if (*aux_needle == '\0')
                return (char *)haystack;
        }
    }
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
    char *aux_char = NULL;
    for (; *haystack != '\0'; haystack++) {
        if (*haystack == *needle) {
            const char* aux_haystack = haystack;
            const char* aux_needle = needle;
            while (*aux_haystack == *aux_needle && *aux_needle != '\0') {
                aux_haystack++;
                aux_needle++;
            }
            if (*aux_needle == '\0')
                aux_char = (char *)haystack;
        }
    }
    return aux_char;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *char_dest = (char *)destination;
    const char *char_src = (const char *)source;
    while (num > 0) {
        *char_dest++ = *char_src++;
        num--;
    }
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
    char *char_dest = (char *)destination;
    const char *char_src = (const char *)source;
    if (char_dest < char_src) {
        while (num > 0) {
            *char_dest++ = *char_src++;
            num--;
        }
    } else {
        char_dest += num - 1;
        char_src += num - 1;
        while (num > 0) {
            *char_dest-- = *char_src--;
            num--;
        }
    }
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	char *char_ptr1 = (char *)ptr1;
    char *char_ptr2 = (char *)ptr2;
    while (num > 0) {
        if (*char_ptr1 != *char_ptr2) {
            return *char_ptr1 - *char_ptr2;
        }
        char_ptr1++;
        char_ptr2++;
        num--;
    }
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	char *char_src = (char *)source;
    while (num > 0) {
        *char_src++ = value;
        num--;
    }
	return source;
}
