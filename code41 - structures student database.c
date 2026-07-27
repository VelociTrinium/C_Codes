//code to make student structure databse
#include <stdio.h>

struct studentdb 
{
    char name[100];
    int regno, m[5], total;
    float avg;
};

void display(struct studentdb *s) 
{
    s->total = 0;
    for (int j = 0; j < 5; j++) 
        s->total += s->m[j];
        
    s->avg = (s->total) / 5.0;
    printf("\nThe total marks are %d\n", s->total);
    printf("The average is %f\n\n", s->avg);
    for (int j = 0; j < 5; j++) 
    {
        if (s->m[j] >= 90) 
        {
            printf("Grade A in Subject %d\n", j + 1);
        } 
        else if (s->m[j] >= 80) 
        {
            printf("Grade B in Subject %d\n", j + 1);
        } 
        else if (s->m[j] >= 70) 
        {
            printf("Grade C in Subject %d\n", j + 1);
        } 
        else if (s->m[j] >= 60) 
        {
            printf("Grade D in Subject %d\n", j + 1);
        } 
        else if (s->m[j] >= 50) 
        {
            printf("Grade E in Subject %d\n", j + 1);
        } 
        else 
        {
            printf("Failed in Subject %d\n", j + 1);
        }
    }

    if (s->avg >= 90) 
    {
        printf("\nOverall grade is A\n");
    } 
    else if (s->avg >= 80) 
    {
        printf("\nOverall grade is B\n");
    } 
    else if (s->avg >= 70) 
    {
        printf("\nOverall grade is C\n");
    } 
    else if (s->avg >= 60) 
    {
        printf("\nOverall grade is D\n");
    } 
    else if (s->avg >= 50) 
    {
        printf("\nOverall grade is E\n");
    }
     else 
    {
        printf("\nOverall grade is Fail\n");
    }
}

int main() 
{
    struct studentdb s[100];
    int n,i,j;

    printf("\nEnter the number of students: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) 
    {
        printf("Enter the name of the student\n");
        scanf("%s", s[i].name);
        printf("Enter the registration number of the student\n");
        scanf("%d", &s[i].regno);
        printf("Enter the marks in all 5 subjects\n");
        for (j = 0; j < 5; j++)
            scanf("%d", &s[i].m[j]);
        display(&s[i]);
    }	
		
    return 0;
}

