#include "utils.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#define BLOCK_SIZE 8
#define KEY_BLOCKS 4
#define KEY_SIZE (KEY_BLOCKS * sizeof(uint32_t))
#define PAD_COUNT(size) (BLOCK_SIZE - ((size) % BLOCK_SIZE))


/**
 * This is an implementation of a the Tiny Encryption Algorithm.
 * https://citeseer.ist.psu.edu/viewdoc/download;jsessionid=C08E8409ADF484095568965A1EBF3E5E?doi=10.1.1.45.281&rep=rep1&type=pdf
 *
 * Although the main aim of TEA was to be "tiny", hence easy to implement, it's
 * surprisingly secure!
 * However, here is an excellent summary of why it is not more frequently used
 * in practice: https://crypto.stackexchange.com/a/16193
 */
void encrypt_block(uint32_t *v, const uint32_t *k)
{
	uint32_t y = v[0], z = v[1], sum = 0;      /* set up */
	uint32_t delta = 0x9E3779B9;               /* a key schedule constant */
	for (int i = 0; i < 32; i++) {             /* basic cycle start */
		sum += delta;
		y += ((z << 4) + k[0]) ^ (z + sum) ^ ((z >> 5) + k[1]);
		z += ((y << 4) + k[2]) ^ (y + sum) ^ ((y >> 5) + k[3]);
	} /* end cycle */
	v[0] = y;
	v[1] = z;
}

void decrypt_block(uint32_t *v, const uint32_t *k)
{
	uint32_t sum=0xC6EF3720, y = v[0], z = v[1];
	uint32_t delta = 0x9E3779B9;
	
	for (int i = 0; i < 32; i++) {    /* basic cycle start */
		z -= ((y<<4) + k[2]) ^ (y + sum) ^ ((y>>5) + k[3]);
		y -= ((z<<4) + k[0]) ^ (z + sum) ^ ((z>>5) + k[1]);
		sum -= delta;
	} /* end cycle */
	v[0] = y;
	v[1] = z;
}

/**
 * Notice that TEA can only encrypt blocks of 8 octets at a time.
 * In fact, every "block cipher" has some "block size" on which it operates.
 * Thus, a problem occurs when the input length is not a multiple of that block
 * size; we need to pad the input.
 *
 * However, this problem is not trivial, and many security, as well as usability
 * issues, could result from improper padding.
 * The scheme used here is adapated from the PKCS padding method.
 */
uint8_t *pad(uint8_t *plaintext, uint32_t size)
{
	uint32_t pad_count = PAD_COUNT(size);
	uint8_t pad_byte = pad_count;

	uint8_t *padded_plaintext = malloc(size + pad_count);
	DIE(padded_plaintext == NULL, "malloc");

	memcpy(padded_plaintext, plaintext, size);
	memset(padded_plaintext + size, pad_byte, pad_count);

	return padded_plaintext;
}

/**
 * TEA is a "block cipher". A block cipher operates on a single block of data.
 * In TEA's case this block is 8 bytes long.
 * What if we need to encrypt more data? Then we need a "block cipher mode of
 * operation", a way of specifying how to process more than one block of data.
 *
 * Here, we use the most simple one imaginable: we split the data into
 * block-sized chunks (padding as needed), than encrypt each one individually.
 * This is called "electronic codebook (ECB)" and it is a disastrously bad mode
 * of operation. To see why, wikipedia has a nice visual illustration about
 * using ECB to encrypt the contents of a bitmap:
 * https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Electronic_codebook_(ECB)
 *
 * We only use it here didactically, for its simplicity.
 */
uint8_t *encrypt(uint8_t *plaintext, uint32_t *size, const uint32_t *k)
{
	uint8_t *cipher = pad(plaintext, *size);
	*size = *size + PAD_COUNT(*size);

	for (int i = 0; i < *size; i += BLOCK_SIZE) {
		encrypt_block((uint32_t *)(cipher + i), k);
	}

	return cipher;
}

uint8_t *decrypt(uint8_t *cipher, uint32_t *size, const uint32_t *k)
{
	uint8_t *plaintext;

	// We'll peak at the padding byte to know in advice how big the
	// plaintext is.
	uint32_t last_block[BLOCK_SIZE / sizeof(uint32_t)];
	uint32_t nonpad_size = *size - BLOCK_SIZE;
	memcpy(last_block, cipher + nonpad_size, BLOCK_SIZE);
	decrypt_block(last_block, k);
	uint8_t pad_byte = last_block[1] >> 24;
	
	uint32_t new_size = *size - pad_byte;
	plaintext = malloc(new_size);
	DIE(!plaintext, "malloc");

	memcpy(plaintext, cipher, nonpad_size);
	for (int i = 0; i < nonpad_size; i += BLOCK_SIZE) {
		decrypt_block((uint32_t *)(plaintext + i), k);
	}

	memcpy(plaintext + nonpad_size, last_block, (BLOCK_SIZE - pad_byte));
	*size = new_size;

	return plaintext;
}

uint32_t *create_key()
{
	/**
	 * Randomness is essential in cryptography.
	 * For many objects (keys, nonces, initalization vectors etc.) we need
	 * to be able to generate random data.
	 *
	 * Usually computers do not generate "random" data, but
	 * "pseudo-random" data, which is generated by some deterministic logic,
	 * starting from a particular value (seed) and only "seems random".
	 *
	 * What is essential for a pseudo-random number generator (PRNG) is for
	 * its output to be **unpredictable**: no matter how much data produced
	 * by it we already observed, it should be infeasible for us to predict
	 * the next bit with a probability better than 50%.
	 *
	 * The PRNGs used for language libraries, like the "rand" function
	 * from libc, are usually quite bad at this task. That's why you might
	 * see warnings such as "The pseudo-random generators of this module
	 * should not be used for security purposes."
	 *
	 * Here, we will rely on Linux's random number generation.
	 */
	int fd = open("/dev/urandom", O_RDONLY);
	DIE(fd == -1, "open /dev/urandom");

	uint32_t *k = malloc(KEY_SIZE);
	int res = read(fd, k, KEY_SIZE);
	DIE(res == -1, "read");

	return k;
}

void destroy_key(uint32_t *k)
{
	/*
	 * It's generally good practice to overwrite the key in memory and to do
	 * this is as quick as possible.
	 *
	 * This is because of reasons like: if the app is compromised and an
	 * attacker could get arbitrary reads of the process's memory space,
	 * then at least they wouldn't have all the time in the world to find
	 * the bytes of the key still lingering.
	 *
	 * This however is just a demonstration for didactical purpose and NOT
	 * NECESSARILY THE CORRECT way to do it.
	 *
	 * For an overview of why this problem is more complicated than it
	 * seems, we recommend reading Paul Grubbs' answer here:
	 * https://crypto.stackexchange.com/a/10000
	 */
	memset(k, 0, KEY_SIZE);
	free(k);
}