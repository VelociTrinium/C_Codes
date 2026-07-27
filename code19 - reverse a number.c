// to reverse a number
#include <stdio.h>
int main()
{
	int num, revnum = 0;
	printf("enter a number ");
	scanf("%d", &num);
	
	while (num != 0)
	{
		revnum = revnum*10 + num%10;
		num /= 10;
	}
	
	printf("%d", revnum);
	
	return 0;
}
