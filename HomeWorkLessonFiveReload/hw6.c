#include <stdio.h>
#include <malloc.h>

/*
 * 6. *Реализовать? ?очередь.
 */

#define MaxN 100
#define T int

struct TNode
{
    T value;
    struct TNode *next;
};
typedef struct TNode Node;

struct Queue
{
    Node *head;
    Node *tail;
};

typedef struct Queue Queue;

void initQueue(Queue *queue);
void enqueue(Queue *queue, T value);
T dequeue(Queue *queue);
void printQueue(Queue *queue);

int main() {
    Queue queue;
    initQueue(&queue);
    printQueue(&queue);

    for (int i = 1; i <= 10; i++) {
        enqueue(&queue, i);
    }

    printQueue(&queue);

    for (int i = 1; i <= 10; i++) {
        printf("Dequeued value: %d\n", dequeue(&queue));
    }

    printQueue(&queue);

    return 0;
}

void initQueue(Queue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
}

void enqueue(Queue *queue, T value)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    if (queue->head == NULL) {
        queue->head = node;
    } else {
        queue->tail->next = node;
    }
    queue->tail = node;
}

T dequeue(Queue *queue)
{
    if (queue->head == NULL) {
        printf("Error: Queue is empty");
        return NULL;
    }
    T value = queue->head->value;
    Node *next = queue->head;
    queue->head = queue->head->next;
    free(next);
    return value;
}

void printQueue(Queue *queue)
{
    printf("printQueue(): ");
    Node *current = queue->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    puts("");
}