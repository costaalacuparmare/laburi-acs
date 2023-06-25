#include <stdio.h>
#include <stdlib.h>

void task3() {
  magik(420);
}

void main() {
    unsigned char encrypted[] = {
        0b11001001, 0b01100111, 0b11101111, 0b11100011, 0b11101100, 0b01100001,
        0b01110010, 0b11100001, 0b11010010, 0b01100010, 0b11110101, 0b01100001,
        0b11101100, 0b01100111, 0b11100101, 0b01100101, 0b11111010};

    // task2(encrypted, sizeof(encrypted));
    task3();
}
