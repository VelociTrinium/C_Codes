#include <stdio.h>

void encpt(char* str, int k) 
{
    k = k % 26;

    for (int i = 0; str[i] != '\0'; i++) 
    {
        char ch = str[i];
        if (ch >= 'A' && ch <= 'Z') 
        {
            str[i] = ((ch - 'A' + k) % 26) + 'A';
        }
        
        else if (ch >= 'a' && ch <= 'z') 
        {
            str[i] = ((ch - 'a' + k) % 26) + 'a';
        }
    }
}

int main() 
{
    char str[100];
    int k;
    
    printf("Enter a String: ");
	scanf("%s", str);
	printf("Enter a number for Encryption: ");
	scanf("%d", &k);

    encpt(str, k);
    printf("Encrypted string: %s\n", str);

    return 0;
}
