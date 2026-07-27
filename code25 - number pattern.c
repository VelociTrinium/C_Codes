//code to generate a number pattern
/* 1
 * 12
 * 123
 * 1234
 * 123
 * 12
 * 1*/
 
#include <stdio.h>
int main()
{
	int n, i, j;
	
	printf("enter a number ");
	scanf("%d",&n);
	
	for (i=1;i<=n; i++)
	{
		for (j=1; j<=i; j++)
			printf("%d",j);
		printf("\n");
	}
		
	for (i=n-1; i>=1; i--)
	{
		for (j=1; j<=i; j++)
			printf("%d",j);
		printf("\n");
	}
	
	return 0;
}
