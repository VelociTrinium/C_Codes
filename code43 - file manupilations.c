
#include <stdio.h>
#include <stdlib.h>

void writeToFile(const char* filename, const char* content) 
{
    FILE* file = fopen(filename, "a");
    fprintf(file, "%s", content);
    fclose(file);
}

void addToFile(const char* filename, const char* content) 
{
    FILE* file = fopen(filename, "a");
    fprintf(file, "%s", content);
    fclose(file);
}

void readFile(const char* filename) 
{
    FILE* file = fopen(filename, "r");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

int main() 
{
    const char* filename = "example.txt";
    const char* initialContent = "This is the initial content.\n";
    const char* additionalContent = "This is the additional content.\n";

    writeToFile(filename, initialContent);

    addToFile(filename, additionalContent);

    printf("File content:\n");
    readFile(filename);

    return 0;
}
