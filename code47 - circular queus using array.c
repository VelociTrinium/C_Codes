#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 5
#define STR_MAX_LENGTH 100

typedef struct 
{
    int data[MAX_SIZE];
    int front, rear;
    int size;
} IntQueue;

void int_init(IntQueue *q) 
{
    q->front = q->rear = -1;
    q->size = 0;
}

bool int_isEmpty(IntQueue *q) 
{
    return q->size == 0;
}

bool int_isFull(IntQueue *q) 
{
    return q->size == MAX_SIZE;
}

bool int_enqueue(IntQueue *q, int value) 
{
    if (int_isFull(q)) 
    {
        printf("Integer Queue is full!\n");
        return false;
    }
    if (int_isEmpty(q)) 
    {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
    q->size++;
    return true;
}

bool int_dequeue(IntQueue *q, int *value) 
{
    if (int_isEmpty(q)) 
    {
        printf("Integer Queue is empty!\n");
        return false;
    }
    *value = q->data[q->front];
    if (q->front == q->rear) 
    {
        q->front = q->rear = -1;
    } 
    else 
    {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    q->size--;
    return true;
}

typedef struct 
{
    char data[MAX_SIZE][STR_MAX_LENGTH];
    int front, rear;
    int size;
} StringQueue;

void str_init(StringQueue *q) 
{
    q->front = q->rear = -1;
    q->size = 0;
}

bool str_isEmpty(StringQueue *q) 
{
    return q->size == 0;
}

bool str_isFull(StringQueue *q) 
{
    return q->size == MAX_SIZE;
}

bool str_enqueue(StringQueue *q, const char *value) 
{
    if (str_isFull(q)) 
    {
        printf("String Queue is full!\n");
        return false;
    }
    if (str_isEmpty(q)) 
    {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    strncpy(q->data[q->rear], value, STR_MAX_LENGTH-1);
    q->data[q->rear][STR_MAX_LENGTH-1] = '\0';
    q->size++;
    return true;
}

bool str_dequeue(StringQueue *q, char *value) 
{
    if (str_isEmpty(q)) 
    {
        printf("String Queue is empty!\n");
        return false;
    }
    strncpy(value, q->data[q->front], STR_MAX_LENGTH-1);
    value[STR_MAX_LENGTH-1] = '\0';
    if (q->front == q->rear) 
    {
        q->front = q->rear = -1;
    } 
    else 
    {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    q->size--;
    return true;
}

void test_int_queue() 
{
    IntQueue q;
    int_init(&q);
    int val;
    
    printf("\nTesting Integer Queue:\n");
    for (int i = 0; i < MAX_SIZE+1; i++) 
    {
        printf("Enqueue %d: %s\n", i, int_enqueue(&q, i) ? "Success" : "Failed");
    }
    
    while (int_dequeue(&q, &val)) 
    {
        printf("Dequeued: %d\n", val);
    }
    
    printf("Dequeue empty: %s\n", int_dequeue(&q, &val) ? "Success" : "Failed");
}

void test_str_queue() 
{
    StringQueue q;
    str_init(&q);
    char val[STR_MAX_LENGTH];
    const char *test[] = {"Hello", "World", "Queue", "Test", "Overflow", NULL};
    
    printf("\nTesting String Queue:\n");
    for (int i = 0; test[i]; i++) 
    {
        printf("Enqueue '%s': %s\n", test[i], 
               str_enqueue(&q, test[i]) ? "Success" : "Failed");
    }
    
    while (str_dequeue(&q, val)) 
    {
        printf("Dequeued: '%s'\n", val);
    }
    
    printf("Dequeue empty: %s\n", str_dequeue(&q, val) ? "Success" : "Failed");
}

int main() 
{
    test_int_queue();
    test_str_queue();
    return 0;
}
