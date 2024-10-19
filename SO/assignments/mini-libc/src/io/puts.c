#include <stdio.h>
#include <internal/syscall.h>
#include <internal/io.h>
#include <string.h>

int puts(const char *str)
{
    int ret = 0;
    ret = write(1, str, strlen(str));
    if (ret < 0) {
        return -1;
    }
    ret = write(1, "\n", 1);
    if (ret < 0) {
        return -1;
    }
    return ret + 1;
}
