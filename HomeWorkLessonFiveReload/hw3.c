#include <stdio.h>
#include <malloc.h>
#include <memory.h>

/*
 * 3. Ќаписать программу, котора€ определ€ет, €вл€етс€ ли введенна€ скобочна€ последовательность правильной.
 * ѕримеры правильных скобочных выражений: (), ([])(), {}(), ([{}]),? ?неправильных? ?Ч? ?)(,? ?())({),? ?(,? ?])}),? ?([(])
 * ?дл€? ?скобок? ?[,(,{. Ќапример:? ?(2+(2*2))? ?или? ?[2/{5*(4+7)}]
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

int checkBrackets(char *chars, Stack *stack){
    int length = strlen(chars);
    for (int i = 0; i < length; i++) {
        char current = chars[i];
        if (current == '{' || current == '[' || current == '(') {
            push(stack, chars[i]);
        }
        if (current == '}' && pop(stack) != '{') {
            return 0;
        }
        if (current == ']' && pop(stack) != '[') {
            return 0;
        }
        if (current == ')') {
            char tmp = pop(stack);
            if (tmp != '(')
                return 0;
        }
    }
    if (stack->size == 0) return 1; else return 0;
}

int main() {
    init(&stack, MaxN);
//    char *string = "(2+(2*2))";
    char *string = "(2+(2{*2)}[])";
//    char *string = "(2+(2*2)[]{({hi}world)})";
    printStack(&stack);
    printf("The string %s: has %s brackets", string, checkBrackets(string, &stack) ? "right" : "wrong");

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