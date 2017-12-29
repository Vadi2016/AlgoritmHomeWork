#include <stdio.h>
#include <malloc.h>

/*
 * 1. Реализовать? ?перевод? ?из? ?10? ?в? ?2? ?систему? ?счисления? ?с? ?использованием? ?стека.
 */

#define MaxN 1000
#define T char

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

void push(Stack *stack, T data);
T pop(Stack *stack);
void init(Stack *stack, int maxSize);
void printStack(Stack *stack);

void printBinary(int n, Stack *stack){
    while (n > 0) {
        if (n & 1){
            push(stack, '1');
        } else {
            push(stack, '0');
        }
        n >>= 1;
    }
}

int main() {
    init(&stack, MaxN);
    printBinary(135, &stack);
    printStack(&stack);

    return 0;
}

void push(Stack *stack, T value)
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
        printf("%c ", current->value);
        current = current->next;
    }
}