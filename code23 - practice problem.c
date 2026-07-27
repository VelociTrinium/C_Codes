// code to solve dam water problems
#include <stdio.h>
int main()
{
	int num_sources;
	float intake, total_intake;
	
	printf("the number of inputs ");
	scanf("%d",&num_sources);
	intake = 0.0;
	
	do
	{
		printf("enter volume of intake ");
		scanf("%f", &intake);
		
		total_intake += intake;
		num_sources--;
		
	} while (num_sources != 0);
	printf("the total volume is %f",total_intake);
    
    
    return 0;

}
