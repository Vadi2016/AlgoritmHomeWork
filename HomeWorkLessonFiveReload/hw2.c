#include <stdio.h>
#include <malloc.h>

/*
 * 2. Добавить в программу “реализация стека на основе односвязного списка” проверку на выделение памяти.
 * Если память не выделяется, то выводится соответствующее сообщение. Постарайтесь создать ситуацию,
 * когда память не будет выделятся.
 */

#define MaxN 100
#define T int

struct TNode
{
    T value;
    struct TNode *next;
};
typedef struct TNode Node;

struct Stack
{
    Node *head;
    int size;
    int maxSize;
};

typedef struct Stack Stack;

Stack stack;

void add(Stack *stack, T data);
T pop(Stack *stack);
void init(Stack *stack, int maxSize);
void printStack(Stack *stack);

int main() {
    init(&stack, MaxN);
    for (int i = 0; i < MaxN + 1; i++) {
        add(&stack, i + 1);
    }
    printStack(&stack);

    return 0;
}

void add(Stack *stack, T value)
{
    if (stack->size >= stack->maxSize){
        printf("Error: stack overflow\n");
        return;
    }
    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = stack->head;
    stack->head = tmp;
    stack->size++;
}

T pop(Stack *stack)
{
    if (stack->size == 0) {
        printf("Error: stack is empty\n");
        return NULL;
    }
    Node *next;
    T value = stack->head->value;
    next = stack->head;
    stack->head = stack->head->next;
    free(next);
    stack->size--;
    return value;
}

void init(Stack *stack, int maxSize)
{
    stack->maxSize = maxSize;
    stack->head = NULL;
}

void printStack(Stack *stack)
{
    Node *current = stack->head;
    while (current!= NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
}