//program to verify string related relations

#include<stdio.h>
#include<string.h>

int main()
{
	char a[20] = "Paranjay";
    char b[20] = "Singh";
    char a_copy[20];

	char string_copy[20], string_cat[20], string_cmp[20];
	int string_length;

    printf("Considering a as '%s', and b as '%s'", a, b);
    //strlen
	string_length = strlen(a);
	printf("\nlength of '%s' is %d", a, string_length);

    //strcpy
    strcpy(a_copy,b);
	printf("\ncopy of '%s' is %s", b, a_copy);

    //strcat
    printf("\nconcatination of '%s' and '%s' is ", a, b);
    strcat(a,b);
	printf("%s", a);

    //strcmp
    if(strcmp(a,a_copy)==0)
        printf("\n'%s' and '%s' are the same\n", a, a_copy);
	else
        printf("\n'%s' and '%s' are not the same\n", a, a_copy);

    
    return 0;
}
