//code printing the fibonacci series
#include <stdio.h>
#include <math.h>
int main()
{
	int a,b,c,t;
	printf("Till when you want the fibonacci series ");
	scanf("%d",&t);
	for (a=b=1; a<=t;)
	{
		printf("%d ",a);
		c=a+b;
		a=b;
		b=c;
	}
	return(0);
}
