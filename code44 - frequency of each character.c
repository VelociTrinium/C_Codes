#include <stdio.h>
#include <string.h>

int main()
{
    int freq[256] = {0};  // Supports all ASCII characters
    char str[100];

    // Taking string input
    printf("Enter the string: ");
    scanf("%[^\n]s", str);  // This handles one word; for multi-word use fgets()
    

    int n = strlen(str);

    // Count frequency of each character
    for (int i = 0; i < n; i++) {
        freq[(int)str[i]]++;  // Map characters to ASCII values
    }

    // Displaying the frequency of each character
    printf("The frequency of characters in the string is:\n");
    for (int i = 0; i < n; i++) {
        if (freq[(int)str[i]] != 0) {  // Only display for characters not yet printed
            printf("'%c' occurs %d times\n", str[i], freq[(int)str[i]]);
            freq[(int)str[i]] = 0;  // Mark as printed
        }
    }
    return 0;
}
