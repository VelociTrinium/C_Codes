#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STR_MAX_SIZE 100
#define STR_MAX_LENGTH 100
#define MAX_SIZE 100

int int_arr[MAX_SIZE];
int int_top = -1;

void int_push(int x) 
{
    if(int_top == MAX_SIZE-1) 
    {
        printf("\nInteger Stack is Full!");
    } 
    else 
    {
        int_arr[++int_top] = x;
    }
}

void int_pop() 
{
    if(int_top == -1) 
    {
        printf("\nInteger Stack is Empty!");
    } 
    else 
    {
        int_top--;
    }
}

void int_display() {
    if(int_top == -1) 
    {
        printf("\nInteger Stack is Empty!");
    } 
    else 
    {
        printf("\nTop element: %d", int_arr[int_top]);
    }
}

void int_displayAll() 
{
    if(int_top == -1) 
    {
        printf("\nInteger Stack is Empty!");
    } 
    else 
    {
        printf("\nStack elements: ");
        for(int i = 0; i <= int_top; i++) 
        {
            printf("%d ", int_arr[i]);
        }
    }
}

void test_int_stack() 
{
    printf("\n\nTesting Integer Stack:");
    int_push(100);
    int_push(200);
    int_push(300);
    int_push(400);
    int_push(500);
    int_push(600);
    int_displayAll();
    int_display();
    int_pop();
    int_pop();
    int_displayAll();
    int_display();
    int_pop();
    int_pop();
    int_displayAll();
    int_display();
    int_pop();
    int_pop();
    int_displayAll();
    int_display();
    int_pop();
    int_pop();
    int_displayAll();
}



char str_arr[STR_MAX_SIZE][STR_MAX_LENGTH];
int str_top = -1;

void str_push(const char* x) {
    if(str_top == STR_MAX_SIZE-1) 
    {
        printf("\nString Stack is Full!");
    } 
    else 
    {
        strncpy(str_arr[++str_top], x, STR_MAX_LENGTH-1);
        str_arr[str_top][STR_MAX_LENGTH-1] = '\0';
    }
}

void str_pop() 
{
    if(str_top == -1) 
    {
        printf("\nString Stack is Empty!");
    } 
    else 
    {
        str_top--;
    }
}

void str_display() 
{
    if(str_top == -1) 
    {
        printf("\nString Stack is Empty!");
    } 
    else 
    {
        printf("\nTop element: %s", str_arr[str_top]);
    }
}

void str_displayAll() 
{
    if(str_top == -1) 
    {
        printf("\nString Stack is Empty!");
    } 
    else 
    {
        printf("\nStack elements: ");
        for(int i = 0; i <= str_top; i++) 
        {
            printf("%s ", str_arr[i]);
        }
    }
}

void test_str_stack() 
{
    printf("\n\nTesting String Stack:");
    str_push("Hello");
    str_push("World");
    str_push("Stack");
    str_push("Implementation");
    str_push("In");
    str_push("C");
    str_displayAll();
    str_display();
    str_pop();
    str_pop();
    str_displayAll();
    str_display();
    str_pop();
    str_pop();
    str_displayAll();
    str_display();
    str_pop();
    str_pop();
    str_displayAll();
    str_display();
    str_pop();
    str_pop();
    str_displayAll();
}


int main() 
{
    test_int_stack();
    test_str_stack();
    return 0;
}
