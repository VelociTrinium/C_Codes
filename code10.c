//code printing the odd/even series
#include <stdio.h>
#include <math.h>
int main()
{
	int o,e,t;
	printf("print til when you want the odd/even series");
	scanf("%d",&t);
	for (o=1; o<=t; o+=2)
		printf("%d ",o);
	printf("\n");
	for (e=2; e<=t; e+=2)
		printf("%d ",e);
	return(0);
}
