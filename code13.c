//code to use shift operator and incriment decrement operator 
#include <stdio.h>
#include <math.h>
int main()
{
	int num, shiftR, shiftL, inc, dre;
	printf("enter a number \n");
	scanf("%d",&num);
	shiftR = num<<2;
	printf("the number shifted to right twice = %d\n", shiftR);
	shiftL = num>>2;
	printf("the number shifted to left twice = %d\n", shiftL);
	inc = ++num;
	printf("the number icrimented = %d\n", num);
	num = --num;
	dre = --num;
	printf("the number decremented once = %d\n", dre);
	
	return(0);
}
