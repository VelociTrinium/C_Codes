// code fpr factorial using recurtion
#include <stdio.h>
#include <math.h>

int fact(int n)
{
	if ((n==0)||(n==1))
		return 1;
	else
		return n*fact(n-1);
}

int main()
{
	int num, factorial;
	printf("Enter a number: ");
	scanf("%d", &num);
	factorial = fact(num);
	printf("%d! = %d", num, factorial);
	return 0;
}
