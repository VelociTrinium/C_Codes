//code to check a name in a list

#include <stdio.h>
#include <string.h>

int main() 
{
	int n, i, tag=0;
	char a[100][100], b[100];
	 
	printf("Enter number of String \n");
	scanf("%d", &n);
	printf("Input the String \n");
	for(i=0; i<n; i++) 
		scanf("%s", a[i]);
		
	printf("Enter the name to be Searched \n");
	scanf("%s", b);
	for(i=0; i<n; i++)
	{
		if(strcmp(a[i], b)==0) 
		{
		tag = 1;
		break;
		}
	}
	
	if(tag == 1) 
	{
		printf("%s exists in the Bunch\n",b);
	} 
	else 
	{
		printf("%s does not exist \n",b);
	}
	
	return 0;
}
