//code to perform simple subraction
#include <stdio.h>
int main()
{
	int a,b,c;
	printf("Input the number you want to subtract \n");
	scanf("%d%d", &a,&b);
	c = a - b;
	printf("the subraction of %d from %d is %d", b,a,c);
	return(0);
}
