/*Perform the following using C program without using string related functions
a. String length 
b. String copy 
c. String reverse 
d. String concatenation 
e. String compare 
f. Verifying whether string is a palindrome or not. */

#include <stdio.h>
#include <string.h>

int Str_Length(char a[100])
{
    int i, l=0;

    for(i=0; a[i] != '\0'; i++)
        l++;
    
    return l;
}

int main()
{
	int i, len_a, len_b, x;
	char a[100], b[100];
	char a_copy[100], a_reverse[100], a_concat[100];
    char s;

    printf("Enter a String a ");
    scanf("%s", a);

    printf("Enter a String b ");
    scanf("%s", b);

    len_a = Str_Length(a);
    len_b = Str_Length(b);
    
    for(i=0; i<len_a; i++)
		a_concat[i]=a[i];
		
	a_concat[len_a] = ' ';

    printf("1. String length \n2. String copy \n3. String reverse \n4. String concatenation \n5. String compare \n6. Verifying whether string is a palindrome or not \n");
    

    
    do {
		printf("What would u like to perform ");
		scanf("%d", &x);
        switch(x)
        {
        case 1:
            printf("Lenght of a is %d\n", len_a);
            printf("Lenght of a is %d\n", len_b);
            break;

        case 2:
            for(i=0; i<len_a; i++)
                a_copy[i]=a[i]; 
            printf("The copy of '%s' string is %s", a, a_copy);
            break;
        
        case 3:
            for(i=0; i<len_a; i++)
                a_reverse[i]=a[(len_a-i-1)]; 
            printf("The reversal of '%s' string is %s", a, a_reverse);
            break;

        case 4:
            for(i=0; b[i]!='\0'; i++)
            {
                a_concat[len_a+i+1]=b[i];
            }
            printf("The concatination of '%s' and '%s' string is %s", a, b, a_concat);
            break;

        case 5:
            if (len_a != len_b)
            {
                printf("The strings a and b are not the same");
            }

            else
            {
                for(i=0; i<len_a; i++)
                {
                    if (a[i]!=b[i])
                    {
                        printf("The strings a and b are not the same");
                        break;
                    }
                }

                if (i == len_a) 
                { 
                    printf("The strings a and b are the same \n");
                }
            }
            break;

        case 6:
            for(i=0; i<len_a; i++)
                a_reverse[i]=a[(len_a-i-1)];

           for(i=0; i<len_a; i++)
                {
                    if (a[i]!=a_reverse[i])
                    {
                        printf("The strings is not a palendrome");
                        break;
                    }
                }

                if (i == len_a) 
                { 
                    printf("The strings is a palendrome \n");
                }
            break;
        }
    x=0;
    printf("\n Do you want to continue (y/n)? \n");
    scanf("%s", &s);
    } while (s == 'y');

    return 0;
}




