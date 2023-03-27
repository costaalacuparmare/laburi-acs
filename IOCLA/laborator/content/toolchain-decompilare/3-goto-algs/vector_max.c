#include <stdio.h>

int main(void)
{
	int v[] = {4, 1, 2, -17, 103, 22, 6, 2};
	int max;
	int i = 1;
    int n = 7;
    max = v[0];

for_label:
    if (v[i] > max)
        max = v[i];
    i++;
    if (i >= n)
        goto exit;
    goto for_label;

exit:
    printf("%d\n", max);
    return 0;
}
