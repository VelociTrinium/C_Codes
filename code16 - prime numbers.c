// Generate all prime numbers from 1 to 300
#include <stdio.h>
int main( )
{
	int i, n = 1 ,num;
	printf ( "\nPrime numbers between 1 and " ) ;
	scanf("%d",&num);
	printf("\n1\t");
	for ( n = 1 ; n <= num ; n++ )
	{
		i = 2 ;
		for ( i = 2 ; i < n ; i++ )
		{
			if ( n % i == 0 ) 
			break ; 
		}
		if ( i == n ) 
		printf ("%d\t", n ) ; 
	}
	return 0 ; 
} 
