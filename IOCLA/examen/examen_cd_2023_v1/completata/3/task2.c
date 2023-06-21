#include <stdio.h>
#include <stdlib.h>

#define BROKEN_BIT_INDEX 7

// TODO: freestyle starts here, implement Task 2
void task2(void *encrypted_data, int size) {
  for (int i = 0; i < size; i ++) {
    char c = ((char *)encrypted_data)[i];
    char mask = 1 << 7;
    if ((c & mask) != 0) {
      c = c & (~mask);
      printf("%c", c);
    }
  }
}
