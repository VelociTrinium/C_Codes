//2D arrey +, -, * using swith case

#include <stdio.h>
#include <stdlib.h>

void enter_a(int a[10][10],int w, int e)
{
	int i,j;
	printf("\nEnter the array elements of Matrix A\n");
	for(i=0;i<w;i++)
	for(j=0;j<e;j++)
	scanf("%d",&a[i][j]);
}

void enter_b(int b[10][10],int w, int e)
{
	int i,j;
	printf("\nEnter the array elements of Matrix B\n");
	for(i=0;i<w;i++)
	for(j=0;j<e;j++)
	scanf("%d",&b[i][j]);
}

void display(int p[10][10],int w, int e)
{
	int i,j;
	printf("\nAdded matrix is:\n");
		for(i=0;i<w;i++)
		{
			for(j=0;j<e;j++)
			printf("%d\t",p[i][j]);
			printf("\n");
		}
}

void add(int a[10][10],int b[10][10],int p[10][10],int w,int e)
{
	int i,j;
	for(i=0;i<w;i++)
	for(j=0;j<e;j++)
		p[i][j]=a[i][j]+b[i][j];
}
void sub(int a[10][10],int b[10][10],int p[10][10],int w,int e)
{
	int i,j;
	for(i=0;i<w;i++)
	for(j=0;j<e;j++)
		p[i][j]=a[i][j]-b[i][j];
}
void mul(int a[10][10],int b[10][10],int p[10][10],int w,int e)
{
	int i,j,k;
	for(i=0;i<w;i++)
	for(j=0;j<e;j++)
	for(k=0;k<e;k++)
		p[i][j]+=a[i][k]+b[k][j];
}
int main()
{
	int a[10][10],b[10][10],p[10][10];
	int m,n;
	char c,t;
	
	printf("\n Enter the dimensionality of matrix ");
	scanf("%d%d",&m,&n);
	enter_a(a,m,n);
	enter_b(b,m,n);
	do{
		fflush(stdin);
		printf("\n Enter + : addition,  - : subtraction, * : multiplication : ");
		scanf("%c",&t);
		switch(t)
		{
			case '+':
				add(a,b,p,m,n);
				display(p,m,n);
				break;
			case '-':
				sub(a,b,p,m,n);
				display(p,m,n);
				break;
			case '*':
				mul(a,b,p,m,n);
				display(p,m,n);
				break;
		}
		printf("Do you want to continue ");
		fflush(stdin);
		scanf("%c",&c);
	}while(c=='y'||c=='Y');
	return 0;
}

