// code to find nCr or nPr using functions (with arguments and with return) - [int fact(int num), return f]
//no argument and no return - [void message]
//with argument and no return - [int argument_1, return 0]
//no argument and with return - [void argument_2, return c]

#include <stdio.h>
#include <math.h>

int fact(int num);
void message();
int argument_1(int num);
int argument_2();


int main()
{
	int n, r, ncr, npr;
	
	printf("enter values for n and r ");
	scanf("%d%d", &n, &r);
	
	if (n>=r)
	{
		ncr = (fact(n))/(fact(r)*fact(n-r));
		npr = (fact(n))/(fact(n-r));
		
		printf("ncr = %d\nnpr = %d", ncr, npr);
	}
	else
	printf("\n!n cannot be less than r!");
	

	return 0;
}

int fact(int num)
{
	int i, f=1;
	for (i=1; i<=num; i++)
		f *= i;
	return (f);
}	

void message()
{
	printf("This is a Void message");
}

int argument_1(int num)
{
	int a;
	a = num<<2;
	printf("%d left shift twice is %d", num, a);
	return 0;
}

int argument_2()
{
	int a = 2, b = 3, c;
	c = pow(a,b);
	return c;
}
