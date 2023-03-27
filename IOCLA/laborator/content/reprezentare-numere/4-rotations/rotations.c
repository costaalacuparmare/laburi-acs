#include <stdio.h>

//DONE
/* roatie in stanga si in dreapta a unui nr cu bites biti */

void rotate_left(int *number, int bits)
{
	unsigned int mask = 1;
    mask <<= (sizeof(*number) * 8 - bits);
    mask &= (*number);
    mask >>= (sizeof(*number) * 8 - bits);
    (*number) <<= bits;
    (*number) |= mask;
}

void rotate_right(int *number, int bits)
{
    unsigned int mask = 1;
    mask >>= (sizeof(*number) * 8 - bits);
    mask &= (*number);
    mask <<= (sizeof(*number) * 8 - bits);
    (*number) >>= bits;
    (*number) |= mask;
}

int main(void)
{
	int number = 0x80000000;
    printf("Before: %x\n", number);
    rotate_left(&number, 1);
    printf("After rotate left with %x bites: %d\n", 1, number);
    number = 0x00000001;
    printf("Before: %x\n", number);
    rotate_right(&number, 16);
    printf("After rotate right with %x bites: %d\n", 1, number);
	return 0;
}

