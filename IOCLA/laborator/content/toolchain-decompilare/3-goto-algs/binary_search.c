#include <stdio.h>

int main(void)
{
	int v[] =  {1, 2, 15, 51, 53, 66, 202, 7000};
	int dest = v[2]; /* 15 */
	int start = 0;
	int end = sizeof(v) / sizeof(int) - 1;
    int contor = 0;
    int mid = 0;
    goto if1_label;

if1_label:
    if (end >= start) {
        mid = start + (end - start) / 2;
        goto if2_label;
    }
    goto print_label;
if2_label:
        if (v[mid] == dest) {
            contor = 1;
            goto print_label;
        }
        goto if3_label;
if3_label:
        if (v[mid] > dest) {
            end = mid - 1;
            goto if1_label;
        }
        start = mid + 1;
        goto if1_label;
print_label:
    if (contor) {
        printf("Element found at %d\n", mid);
        return 0;
    }
    printf("Element not found\n");
    return 0;
}