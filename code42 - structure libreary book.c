//code for handeling liberary book overdue fees
#include <stdio.h>
#include <string.h>

struct Book 
{
    char bn[50];
    int dueDate;
    int returnDate;
}b;

int calcFine(struct Book b, int dueDate, int returnDate, int fine_rate, int n) 
{
    static int daysLate;

    if (returnDate > dueDate) 
    {
        int dueYear = b.dueDate / 10000;
        int dueMonth = (b.dueDate / 100) % 100;
        int dueDay = b.dueDate % 100;
    
        int returnYear = b.returnDate / 10000;
        int returnMonth = (b.returnDate / 100) % 100;
        int returnDay = b.returnDate % 100;
    
        daysLate = (returnYear - dueYear) * 365 + (returnMonth - dueMonth) * 30 + (returnDay - dueDay);
    }
    return daysLate * fine_rate;
}

int main() 
{
    int fine_rate;
    int n;
    static int amount_total;
    
    printf("Enter the number of Books issued: ");
    scanf("%d",&n);
    struct Book b[100];
    for (int i=0; i<n; i++)
    {
		printf("\nEnter the title of the book: ");
		scanf("%s",b[i].bn);
	
		printf("Enter the due date (yyyy mm dd): ");
		scanf("%d", &b[i].dueDate);
	
		printf("Enter the reterning date (yyyy mm dd): ");
		scanf("%d", &b[i].returnDate);
	}
	printf("\nEnter the fine rate per day: ");
	scanf("%d", &fine_rate);
    
	for (int i=0; i<n; i++)
	{
		int amt = calcFine(b[i], b[i].dueDate, b[i].returnDate, fine_rate, n);
		if ( amt > 0) 
		{
			printf("The book %s is overdue.\n",b[i].bn);
			printf("Due amount: %d\n", amt);
		}
		amount_total+=amt;
	}

    if (amount_total > 0.0) 
    {
        printf("\nFine amount: %d\n", amount_total);
    } 
    else 
    {
        printf("\nNo book is not overdue.\n");
    }

    return 0;
}

