#include <stdio.h>
#include <string.h>

void swap_int(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void swap_str(char *a, char *b) 
{
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void bubble_sort_int(int arr[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                swap_int(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void bubble_sort_str(char arr[][100], int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (strcmp(arr[j], arr[j + 1]) > 0) 
            {
                swap_str(arr[j], arr[j + 1]);
            }
        }
    }
}

void print_int_array(int arr[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_str_array(char arr[][100], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        printf("%s\n", arr[i]);
    }
}

int main() {
    int int_arr[] = {54, 33, 58, 81, 12};
    int n1 = sizeof(int_arr) / sizeof(int_arr[0]);

    char str_arr[][100] = {"Jay", "Harsh", "Niranjan", "Arpit", "Saket"};
    int n2 = sizeof(str_arr) / sizeof(str_arr[0]);

    printf("Original integer array: ");
    print_int_array(int_arr, n1);
    bubble_sort_int(int_arr, n1);
    printf("\nSorted integer array: ");
    print_int_array(int_arr, n1);
    
    printf("\n-----\n");

    printf("\nOriginal string array:- ");
    print_str_array(str_arr, n2);
    bubble_sort_str(str_arr, n2);
    printf("\nSorted string array:- ");
    print_str_array(str_arr, n2);

    return 0;
}
