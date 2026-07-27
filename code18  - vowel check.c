// to check the number of vowels
#include<stdio.h>
#include<math.h>
int main()
{
    char c;
    int a1=0, e1=0, i1=0, o1=0, u1=0, count=0, sum=0;
    printf("\nenter * to exit\n");
    
    do
    {
        printf("\nenter a charector ");
        scanf("%c",&c);

        switch (c)
        {
            case 'a':
            a1++;
            printf("%c is a vowel\n",c);
            break;

            case 'e':
            e1++;
            printf("%c is a vowel\n",c);
            break;
            
            case 'i':
            i1++;
            printf("%c is a vowel\n",c);
            break;
            
            case 'o':
            o1++;
            printf("%c is a vowel\n",c);
            break;

            case 'u':
            u1++;
            printf("%c is a vowel\n",c);
            break;
            
            case '*':
            printf("ending loop\n");
        }

        sum = a1 + e1 + i1 + o1 + u1;
		fflush(stdin);
		count++;

    } while (c != '*');

    printf("a =\t%d\ne =\t%d\ni =\t%d\no =\t%d\nu =\t%d\n--------\nsum = \t%d\ntotal inputs = %d",a1,e1,i1,o1,u1,sum,(count-1));
    

    return 0;
    
}
