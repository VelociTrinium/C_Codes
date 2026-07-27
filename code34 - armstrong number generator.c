//code to generate an armstrong number within a given range

#include <stdio.h>
#include <math.h>


int main()
{
	int a,b,i, temp, term, sum, n, m;
	static int ar[100], c=0;
	
	printf("Enter the range ");
	scanf("%d%d",&a,&b);
	
	for(i=a; i<=b; i++)
	{
		m=i;
		n=i;
		sum=0;
		
		for (a=i; a!=0; b++)
			{
				temp = a/10;
				a=temp;
			}
			
		while(n>0)
		{
			term=n%10;
			sum += pow(term,b);
			n=n/10;
		}
		
		if(sum==m)
		{
			ar[c]=m;
			c++;
		}
	}
	
	for(i=0; i<c; i++)
		printf("\n Armstrong number is %d",ar[i]);

	return 0;
}

