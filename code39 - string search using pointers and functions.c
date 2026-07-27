// Function to search for a substring in a main string
#include <stdio.h>
#include <string.h>

void searchSubstring(char* str, char* substr, int l3, int l4) 
{
    int i,count = 0;
    for (i = 0; i <= l3 - l4; i++)
    {
        if (strncmp(&str[i], substr, l4) == 0)
        {
            count = 1;
            break;
        }
    }

    if (count == 1)
    {
        printf("Substring found, %s in %s\n", substr, str);
    }
    else
    {
        printf("Substring does not exist in string\n");
    }

}

int main() 
{
    char str[100], substr[100];
    int l1, l2;
    
    printf("Enter main string: ");
    scanf("%s", str);
    l1 = strlen(str);
    
    printf("Enter substring: ");
    scanf("%s", substr);
    l2 = strlen(substr);

    searchSubstring(str, substr, l1, l2);

    return 0;
}
