#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*find out length without strlen
 and print the adress of chars equal to chars on i + 2^i*/

//DONE

int my_strlen(const char *str)
{
	 const char *p = str;
     while (*p != '\0') {
         p++;
     }
     int len = p - str;
     return len;
}

void equality_check(const char *str)
{
    for ( int i = 0; i < my_strlen(str); i++)
    {
        int j = (i + (1 << i)) % my_strlen(str);
        if (str[j] == str[i])
            printf("Address of %c: %p\n",str[i],&str[i]);
    }
}

int main(void)
{
    const char *s = "ababababacccbacbacbacbacbabc";
    printf("lenght = %d\n", my_strlen(s));
    equality_check(s);
	return 0;
}

