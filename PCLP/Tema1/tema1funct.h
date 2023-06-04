#define MAX 1000
#define PLUS '+'
#define MINUS '-'
#define ORI '*'
#define DIV '/'

void delnum(int intr, int *num_count, float num[MAX]) {
  for (int i = intr; i < (*num_count); i++)
            num[i] = num[i + 1];
  (*num_count)--;
}

void delop(int intr, int num_count, char op[MAX]) {
  for (int i = intr; i < num_count - 1; i++)
    op[i] = op[i + 1];
  op[num_count - 1] = '\0';
}
