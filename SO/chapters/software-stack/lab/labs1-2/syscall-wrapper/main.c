 /* SPDX-License-Identifier: BSD-3-Clause */

#include "./syscall.h"

int main(void)
{
    char buf[9];
    buf[9] = '\0';
    int count = read(0, buf, 8);
	write(1, buf, count);
	exit(0);
	return 0;
}
