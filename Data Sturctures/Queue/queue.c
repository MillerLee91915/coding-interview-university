#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void enqueue(Queue *q, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (q->tail == NULL)   // queue 是空的
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

int dequeue(Queue *q)
{
    if (q->head == NULL)
    {
        printf("queue empty\n");
        return -1;
    }

    Node *temp = q->head;
    int value = temp->data;

    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(temp);

    return value;
}

int empty(Queue *q)
{
    return q->head == NULL;
}

int full()
{
    return 0;
}

void init_queue(Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

int main()
{
    Queue q;
    init_queue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));

    return 0;
}
