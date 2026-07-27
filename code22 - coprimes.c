//code to test coprime numbers
#include <stdio.h>
int main()
{
	int n1, n2, dividend, divisor, remainder;
	printf("enter 2 numbers: ");
	scanf("%d%d", &n1,&n2);
	(n1>n2?(dividend = n1,divisor = n2):(dividend = n2,divisor = n1));
	remainder = dividend%divisor;
	while(remainder != 0)
	{
		dividend = divisor;
		divisor = remainder;
		remainder = dividend % divisor;
	}
	printf("%d is the GCD\n",divisor);
	(divisor == 1 ? printf("%d and %d are co-prime", n1, n2) : printf("%d and %d are not co-prime", n1, n2));
	return 0;
}

