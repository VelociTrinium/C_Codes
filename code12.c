//code to check weather a number is armstrong number
#include <stdio.h>
#include <math.h>
int main()
{
	int num,n,a,b,c,t;
	printf("enter a 3 digit number ");
	scanf("%d",&num);
	n=num;
	a = num%10;
	num/=10;
	b = num%10;
	num/=10;
	c = num%10;
	t = pow(a,3)+pow(b,3)+pow(c,3);
	if (t == n)
	printf("the number %d is an armstrong number", n);
	else
	printf("the number is not a armstrong number");
	return(0);
}
