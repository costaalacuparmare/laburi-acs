#include <stdio.h>
#include "tema1funct.h"

int main() {
  char op[MAX];
  int num_count = 0;
  float num[MAX];
  scanf("%d", & num_count);
  if (num_count != 0) {
    for (int i = 0; i < num_count; i++)
      scanf("%f", &num[i]);
    if (num_count != 1) {
      scanf("%s", op);
      while (op[0] != '\0') {
        // using switch to avoid if repetition
        switch (op[0]) {
          case PLUS: {
            num[0] = num[0] + num[1];
            delnum(1, &num_count, num);
            break;
          }
          case MINUS: {
            num[0] = num[0] - num[1];
            delnum(1, &num_count, num);
            break;
          }
          case ORI: {
            num[0] = num[0] * num[1];
            delnum(1, &num_count, num);
            break;
          }
          case DIV: {
            num[0] = num[0] / num[1];
            delnum(1, &num_count, num);
            break;
          }
          break;
        }
        delop(0, num_count, op);
      }
    }
  }
  printf("%f\n", num[0]);
  return 0;
}
