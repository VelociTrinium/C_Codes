//code to generate pascals triangle
#include <stdio.h>
#include <math.h>
int main()
{
	int a, b, i, j;
	int num_rows, fi, fj, fij, ft=1;
	
	printf("\nEnter number of rows ");
	scanf("%d", &num_rows);
	
	
	for(i=0; i<num_rows; i++)
	{	
		/*printing part*/
		for(b = 0; b<=num_rows-i ; b++)
				printf("  ");
				
		for(j=0; j<=i; j++)
		{	
			fi=fj=fij=1;
			/*factorial of i*/
			for(a = 1; a <= i; a++)
				fi *= a;
			
			/*factorial of j*/
			for(a = 1; a<= j; a++)
				fj *= a;
			
			/*factorial of i-j*/
			for(a = 1; a<= i-j; a++)
				fij *= a;
			
			ft = fi/(fj*fij);
			printf("%4d",ft);
		}	
		printf("\n");
	}
	
	return 0;
}
