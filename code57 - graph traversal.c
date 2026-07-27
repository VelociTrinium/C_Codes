#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Graph 
{
    int vertices;
    int adjMatrix[MAX][MAX];
};

struct Queue 
{
    int items[MAX];
    int front, rear;
};

struct Stack 
{
    int items[MAX];
    int top;
};

void initQueue(struct Queue *q) 

{
    q->front = -1;
    q->rear = -1;
}

void enqueue(struct Queue *q, int value) 
{
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(struct Queue *q) 
{
    if (q->front == -1) return -1;
    int item = q->items[q->front++];
    if (q->front > q->rear) q->front = q->rear = -1;
    return item;
}

void initStack(struct Stack *s) 
{
    s->top = -1;
}

void push(struct Stack *s, int value) 
{
    if (s->top == MAX - 1) return;
    s->items[++s->top] = value;
}

int pop(struct Stack *s) 
{
    if (s->top == -1) return -1;
    return s->items[s->top--];
}

void initGraph(struct Graph *g, int vertices) 
{
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            g->adjMatrix[i][j] = 0;
}

void addEdge(struct Graph *g, int src, int dest) 
{
    g->adjMatrix[src][dest] = 1;
    g->adjMatrix[dest][src] = 1;
}

void BFS(struct Graph *g, int start) 
{
    struct Queue q;
    initQueue(&q);
    int visited[MAX] = {0};

    enqueue(&q, start);
    visited[start] = 1;

    while (q.front != -1) 
    {
        int node = dequeue(&q);
        printf("%d ", node);
        
        for (int i = 0; i < g->vertices; i++) 
        {
            if (g->adjMatrix[node][i] == 1 && !visited[i]) 
            {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void DFS(struct Graph *g, int start) 
{
    struct Stack s;
    initStack(&s);
    int visited[MAX] = {0};

    push(&s, start);
    visited[start] = 1;
    printf("%d ", start);

    while (s.top != -1) 
    {
        int node = s.items[s.top];
        int found = 0;
        
        for (int i = 0; i < g->vertices; i++) 
        {
            if (g->adjMatrix[node][i] == 1 && !visited[i]) 
            {
                push(&s, i);
                visited[i] = 1;
                printf("%d ", i);
                found = 1;
                break;
            }
        }
        if (!found) pop(&s);
    }
    printf("\n");
}

int main() {
    struct Graph g;
    int vertices = 6;
    initGraph(&g, vertices);
    
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 1, 4);
    addEdge(&g, 2, 5);
    
    printf("0>>1, 0>>2, 1>>3, 1>>4, 2>>5\n");
    printf("BFS Traversal: ");
    BFS(&g, 0);
    
    printf("DFS Traversal: ");
    DFS(&g, 0);
    
    return 0;
}
