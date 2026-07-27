// code to find sum of  1 +1/1! + 1/2! + 1/3! ....
#include <stdio.h>
int main()
{
	int n;
	float i,t, sum=1.0;
	printf("enter the value for n ");
	scanf("%d", &n);
	
	printf("1");
	
	for (i=1.0; i<=n-1; i++)
	{
		t=i/(i+1);
		printf(" + %d/%d", (int)i,(int)(i+1));
		sum += t;
	}
	printf("\nsum = %f", sum);
	
	
	return 0;
}





