#include <stdio.h>
#include "tema1funct.h"

int main() {
  char op[MAX];
  int num_count = 0, pos = 0;
  float num[MAX];
  scanf("%d", & num_count);
  if (num_count != 0) {
    for (int i = 0; i < num_count; i++)
      scanf("%f", &num[i]);
    if (num_count != 1) {
      scanf("%s", op);
      while (op[0] != '\0') {
        pos = 0;
        while ( pos < num_count -1)
          if (op[pos] == DIV) {
          delop(pos, num_count, op);
          num[pos] = num[pos] / num[pos + 1];
          delnum(pos + 1, &num_count, num);
          } else {
              pos++;
            }
        pos = 0;
        while ( pos < num_count -1)
          if (op[pos] == ORI) {
          delop(pos, num_count, op);
          num[pos] = num[pos] * num[pos + 1];
          delnum(pos + 1, &num_count, num);
          } else {
              pos++;
            }
        pos = 0;
        while ( pos < num_count -1)
          if (op[pos] == MINUS) {
          delop(pos, num_count, op);
          num[pos] = num[pos] - num[pos + 1];
          delnum(pos + 1, &num_count, num);
          } else {
              pos++;
            }
        pos = 0;
        while ( pos < num_count -1)
          if (op[pos] == PLUS) {
          delop(pos, num_count, op);
          num[pos] = num[pos] + num[pos + 1];
          delnum(pos + 1, &num_count, num);
          } else {
              pos++;
            }
      }
    }
  }
  printf("%f\n", num[0]);
  return 0;
}
