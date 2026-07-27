// code for fibonachi series using recurtion
#include <stdio.h>
#include <math.h>

int fibo(int n)
{
	if ((n==0)||(n==1))
		return n;
	else
		return fibo(n-1)+fibo(n-2);
}

int main()
{
	int num, i;
	printf("Enter a number: ");
	scanf("%d", &num);
	printf("\n");
	for (i=num; i>0; i--)
		printf("%d ", fibo(num-i));
	
	return 0;
}
