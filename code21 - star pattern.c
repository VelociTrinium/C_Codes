// code to make a star pattern
#include <stdio.h>
int main()
{
	int i,j,n;
	printf("how many lines to create ");
	scanf("%d", &n);
	for (i=1; i<=n; i++)
	{
		for(j=1; j<=i; j++)
			printf("**");
		printf("\n");
		
	}
	
	return 0;
}
