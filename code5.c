//code to perform simple Power
#include <stdio.h>
#include<math.h>
int main()
{
	int a,b,c;
	printf("Input the number you want to add the power to and the power to be added \n");
	scanf("%d%d", &a,&b);
	c = pow(a,b);
	printf("%d to the power %d = %d", a,b,c);
	return(0);
}
