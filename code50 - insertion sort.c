#include <stdio.h>
#include <string.h>

void insertion_sort_int(int arr[], int n) 
{
    for (int i = 1; i < n; i++) 
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void insertion_sort_str(char arr[][100], int n) 
{
    for (int i = 1; i < n; i++) 
    {
        char key[100];
        strcpy(key, arr[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) 
        {
            strcpy(arr[j + 1], arr[j]);
            j--;
        }
        strcpy(arr[j + 1], key);
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
    insertion_sort_int(int_arr, n1);
    printf("\nSorted integer array: ");
    print_int_array(int_arr, n1);
    
    printf("\n-----\n");

    printf("\nOriginal string array:- ");
    print_str_array(str_arr, n2);
    insertion_sort_str(str_arr, n2);
    printf("\nSorted string array:- ");
    print_str_array(str_arr, n2);

    return 0;
}
