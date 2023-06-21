#include <stdio.h>
#include <stdlib.h>

void task3() {
    // TODO: call secret function with correct arguments
}

void main() {
    unsigned char encrypted[] = {
        0b10011010, 0b01100111, 0b10111100, 0b10110000, 0b10111111, 0b01100001,
        0b01110010, 0b10110010, 0b10000001, 0b01100010, 0b10100110, 0b01100001,
        0b10111111, 0b01100111, 0b10110110, 0b01100101, 0b10101001};

    task2(encrypted, sizeof(encrypted));
    task3();
}
