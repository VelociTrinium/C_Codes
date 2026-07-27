// to find the factorial of a number
#include<stdio.h>
int main()
{
	int i, a, f=1;
	printf("the number you want a factorial of ");
	scanf("%d",&i);
	
    for (a=1; a<=i; i--)
    {
        f *= i;
	}
	printf("factorial = %d",f);
	
	return 0;
}
