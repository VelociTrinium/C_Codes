//function to find frequency of a charector in a string
#include <stdio.h>
#include <string.h>

void fsearch(char a[], int l) 
{
    int freq[26] = {0};
    int i, j;

    for (i = 0; i < l; i++) {
        if (a[i] >= 'a' && a[i] <= 'z') 
        {
            freq[a[i] - 'a']++;
        }
    }

    for (j = 0; j < 26; j++) {
        if (freq[j] > 0) {
            printf("%c : %d\n", j + 'a', freq[j]);
        }
    }
}

int main() 
{
    int l;
    char str[100];
    
    printf("Enter the string: ");
    gets(str);
    strlwr(str);
    
    l = strlen(str);
    printf("The frequency of each elements is:\n");
    fsearch(str, l);
    
    return 0;
}
