//code printing the multiplication table
#include <stdio.h>
#include <math.h>
int main()
{
	int n,i,t;
	printf("print the number you want a table of, and the number of times to be printed ");
	scanf("%d%d", &n,&t);
	
	for (i=1; i<=t; i++)
		printf("%d * %d = %d\n", n,i,(n*i));
	return(0);
}
