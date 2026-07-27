// code For Tower of Hanoi using recurtion
#include <stdio.h>
#include <math.h>

void toh(int n, char fromrod, char torod, char auxrod)
{
	if (n==1)
	{
		printf("\n move disk 1 from rod %c to rod %c", fromrod, torod);
		return;
	}
	toh(n-1, fromrod, auxrod, torod);
	printf("\n move disk %d from rod %c to rod %c", n, fromrod, torod);
	toh(n-1, auxrod, torod, fromrod);
}

int main()
{
	int n;
	printf("Enter value for n: ");
	scanf("%d", &n);
	toh(n, 'A', 'C', 'B');
	
	return 0;
}
