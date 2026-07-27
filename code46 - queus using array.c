#include <stdio.h>
#include <string.h>

#define STR_MAX_SIZE 100
#define STR_MAX_LENGTH 100
#define MAX_SIZE 100


int int_arr[MAX_SIZE];
int int_f = -1;
int int_r = -1;

int int_empty() 
{
    return (int_f == -1 && int_r == -1);
}

int int_full() 
{
    return (int_r == MAX_SIZE - 1);
}

void int_enqueue(int x) 
{
    if (int_full()) 
    {
        printf("\nInteger Queue is Full!");
    } 
    else 
    {
        if (int_empty()) 
        {
            int_f = int_r = 0;
        } 
        else 
        {
            int_r++;
        }
        int_arr[int_r] = x;
    }
}

void int_dequeue() 
{
    if (int_empty()) 
    {
        printf("\nInteger Queue is Empty!");
    } 
    else 
    {
        if (int_f == int_r) 
        {
            int_f = int_r = -1;
        } 
        else 
        {
            int_f++;
        }
    }
}

void int_display() {
    if (int_empty()) {
        printf("\nInteger Queue is Empty!");
    } else {
        printf("\nFront=%d, Rear=%d", int_arr[int_f], int_arr[int_r]);
    }
}

void int_displayAll() {
    if (int_empty()) {
        printf("\nInteger Queue is Empty!");
    } else {
        printf("\nQueue elements: ");
        for (int i = int_f; i <= int_r; i++) {
            printf("%d ", int_arr[i]);
        }
    }
}

void test_int_queue() {
    printf("\n\nTesting Integer Queue:");
    int_enqueue(0);
    int_enqueue(1);
    int_enqueue(2);
    int_enqueue(3);
    int_enqueue(4);
    int_displayAll();
    int_display();
    int_dequeue();
    int_dequeue();
    int_displayAll();
    int_display();
    int_dequeue();
    int_dequeue();
    int_displayAll();
    int_display();
    int_dequeue();
    int_dequeue();
    int_displayAll();
}


char str_arr[STR_MAX_SIZE][STR_MAX_LENGTH];
int str_f = -1;
int str_r = -1;

int str_empty() {
    return (str_f == -1 && str_r == -1);
}

int str_full() {
    return (str_r == STR_MAX_SIZE - 1);
}

void str_enqueue(const char* x) {
    if (str_full()) {
        printf("\nString Queue is Full!");
    } else {
        if (str_empty()) {
            str_f = str_r = 0;
        } else {
            str_r++;
        }
        strncpy(str_arr[str_r], x, STR_MAX_LENGTH - 1);
        str_arr[str_r][STR_MAX_LENGTH - 1] = '\0'; // Ensure null-termination
    }
}

void str_dequeue() {
    if (str_empty()) {
        printf("\nString Queue is Empty!");
    } else {
        if (str_f == str_r) {
            str_f = str_r = -1;
        } else {
            str_f++;
        }
    }
}

void str_display() {
    if (str_empty()) {
        printf("\nString Queue is Empty!");
    } else {
        printf("\nFront=%s, Rear=%s", str_arr[str_f], str_arr[str_r]);
    }
}

void str_displayAll() {
    if (str_empty()) {
        printf("\nString Queue is Empty!");
    } else {
        printf("\nQueue elements: ");
        for (int i = str_f; i <= str_r; i++) {
            printf("%s ", str_arr[i]);
        }
    }
}

void test_str_queue() {
    printf("\n\nTesting String Queue:");
    str_enqueue("Hello");
    str_enqueue("World");
    str_enqueue("Queue");
    str_enqueue("Implementation");
    str_enqueue("In C");
    str_displayAll();
    str_display();
    str_dequeue();
    str_dequeue();
    str_displayAll();
    str_display();
    str_dequeue();
    str_dequeue();
    str_displayAll();
    str_display();
    str_dequeue();
    str_dequeue();
    str_displayAll();
}


int main() {
    test_int_queue();
    test_str_queue();
    return 0;
}
