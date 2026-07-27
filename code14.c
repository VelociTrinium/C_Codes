//code for type conversion implisit and explisit
#include <stdio.h>
#include <math.h>
int main()
{
	int a,c,e;
	float b,d;
	
	printf ("input a int number\n");
	scanf ("%d", &a);
	b = a;
	printf ("the implicit value of %d is %f\n", a, b);
	
	printf ("input another number\n");
	scanf ("%d", &e);
	printf ("the explisit number division of %d and %d is %f\n", a,e,(float)a/e);
	
	return(0);
}
