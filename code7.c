//code for finding area of a circle
#include <stdio.h>
#include <math.h>
int main()
{
	int r;
	float area;
	printf("Input the radius of the circle \n");
	scanf("%d", &r);
	
	area = (3.14)*pow(r,2);
	printf("the area of a circle with radius %d is %f", r,area);
	
	return(0);
}
