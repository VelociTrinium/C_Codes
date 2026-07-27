// code to find 1 + 1/2 + 1/4 + 1/8 ...n terms
#include <stdio.h>
#include <math.h>
int main()
{
	int n;
	float i,t, sum=1.0;
	printf("enter the value for n ");
	scanf("%d", &n);
	
	printf("1");
	
	for (i=1.0; i<=n-1; i++)
	{
		t=(pow(2,i));
		printf(" + 1/%d", (int)t);
		sum += 1/t;
	}
	printf("\nsum = %f", sum);
	
	
	return 0;
}
