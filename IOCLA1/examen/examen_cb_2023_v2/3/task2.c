#include <stdio.h>
#include <stdlib.h>

#include "dns.h"

#define HACKED_BIT_INDEX 7
#define KEY 0xBADB17C8

// TODO: freestyle starts here, implement Task 2
void task2(void *entries, int size, int target_ip) {
	unsigned int mask = 1 << HACKED_BIT_INDEX;
	for (int i = 0; i < 32; i++)
		mask = (mask ^ (1 << i));
	for (int i = 0; i < size; i++) {
		struct dns_entry var = ((struct dns_entry *)entries)[i];
		var.ip ^= KEY;
		var.ip &= mask;
		if (var.ip == (unsigned int) target_ip)
			printf("%s\n", var.hostname);
	}
}
