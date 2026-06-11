#include <stdio.h>

int Var1 (int n) //Varianta clasica
{
	if ( n % 2 == 0)
		printf("Par ");
        else
		printf("Impar ");
	printf("Prin varianta clasica\n");
}

int Var2 (int  n) //Varianta pe biti
{
	if ( (n & 1) == 1)
		printf("Impar ");
	else
		printf("Par ");
	printf("Prin varianta pe biti\n");
}

int main()
{
	int numar = 0;
	scanf("%d", &numar);
	Var1(numar);
	Var2(numar);
	return 0;
}
	

