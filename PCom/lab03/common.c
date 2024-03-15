#include "common.h"

uint8_t simple_csum(uint8_t *buf, size_t len) {
	uint32_t sum = 0;
    uint8_t checksum;

	for (int i = 0; i < len; i++) {
        sum += *((uint8_t *)buf + i);
	}

    checksum = sum % 256;
	return checksum;
}

uint32_t crc32(uint8_t *buf, size_t len)
{
    uint32_t crc = -1;
    const uint32_t POLY = 0xEDB88320;
	/* Iterate through each byte of buff */
    for (int i = 0; i < len; i++) {
        /* Iterate through each bit */
        crc ^= *(buf + i);
        for (int j = 0; j < 8; j++) {
            /* If the bit is 1, compute the new reminder */
            if (crc & 1) {
                crc = (crc >> 1) ^ POLY;
            } else {
                crc = crc >> 1;
            }
        }
    }
	/* By convention, we negate the crc */
	crc = ~crc;
    return crc;
}
