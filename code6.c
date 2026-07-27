//code for resolving quadratic equation
#include <stdio.h>
#include <math.h>
int main()
{
	int a,b,c;
	float d,r1,r2;
	printf("Input coefficients of a, b, c \n");
	scanf("%d%d%d", &a,&b,&c);
	
	d = (pow(b,2)-4*a*c);
	
	if (d > 0)
	{
		r1 = (-b+sqrt(d))/(2*a);
		r2 = (-b-sqrt(d))/(2*a);
		printf("roots of equation are %f, %f", r1, r2);
	}
	
	else if (d == 0)
	{
		r1 = r2 = -b/2*a;
		printf("bothe the roots are same %f",r1);
	}
	
	else
		printf("the roots are imaginary");
	
	return(0);
}
