//code for finding the greatest number
#include <stdio.h>
#include <math.h>
int main()
{
	int a,b,c;
	printf("input 3 numbers \n");
	scanf("%d%d%d", &a,&b,&c);
	if ((a>b)&&(a>c))
		printf("%d is the greatest",a);
	else
	{
		if (b>c)
		printf("%d is the greatest",b);
		
		else
		printf("%d is the greatest",c);
	}
	return(0);
}
