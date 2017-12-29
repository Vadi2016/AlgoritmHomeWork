#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <ctype.h>

/*
 * 5. **Реализовать алгоритм перевода из инфиксной записи арифметического выражения в постфиксную.
 */

#define MaxN 100
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

void add(Stack *stack, T data);
T pop(Stack *stack);
void init(Stack *stack, int maxSize);
void printStack(Stack *stack);

int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return 1;
    else return 0;
}

int isNumberOrLetter(char c) {
    if (!(isOperator(c) || c == '(' || c == ')')) return 1;
    else return 0;
}

int getPriority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case '(':
        case ')':
            return 0;
        default:
            return -1;
    }
}

int isEmptyStack(Stack *stack) {
    if (stack->size == 0) return 1;
    else return 0;
}

T getHead(Stack *stack) {
    if (isEmptyStack(stack) == 1) return NULL;
    else return stack->head->value;
}

void infixToPostfix(char *in, char *out, int inLength) {
    int pos = 0;
    // Флаг, чтобы понимать, что закончилось одно число и можно отделить его от следующего пробелом
    int isCompleteNumber = 0;
    for (int i = pos; i < inLength; i++) {
        char current = in[i];

        if(isspace(current)) continue;

        if (current == '(') {
            add(&stack, current);
            continue;
        }

        // Выкидываем из стека все знаки до предыдущей скобки
        if (current == ')') {
            while (isEmptyStack(&stack) != 1 && getHead(&stack) != '(') {
                current = pop(&stack);
                out[pos] = current;
                pos++;
            }
            pop(&stack); // Убираем скобку "(" из стека
            continue;
        }

        if (isOperator(current)) {
            isCompleteNumber = 1; // Если встретили оператор, то пора отделять числа друг от друга
            if (getHead(&stack) == NULL) {
                add(&stack, current);
                continue;
            }
            if (getPriority(current) > getPriority(getHead(&stack))) {
                add(&stack, current);
            } else {
                char tmp = ' ';
                // Пока не достигнем меньшего по приоритету знака в стеке, выкидываем все знаки
                while (isEmptyStack(&stack) != 1 && tmp != '(' && getPriority(current) <= getPriority(getHead(&stack))) {
                    tmp = pop(&stack);
                    out[pos] = tmp;
                    pos++;
                }
                add(&stack, current);
            }
            continue;
        }

        // Вставляем разделитель чисел, если нужно
        if (i > 0 && isCompleteNumber && isNumberOrLetter(out[pos - 1])) {
            out[pos] = ' ';
            pos++;
        }
        isCompleteNumber = 0;
        out[pos] = current;
        pos++;
    }

    Node *node = stack.head;
    while (node!= NULL) {
        out[pos] = node->value;
        pos++;
        node = node->next;
    }

    out[pos] = '\0'; // Отсекаем все случайные символы в массиве
}

int main() {
    init(&stack, MaxN);
//    char *infix = "a + b * c / (d - e * f ^ (g + h) * k) ^ i";
    char *infix = "11 + 12 * 13 / (14 - 15 * 16 ^ (17 + 18) * 19) ^ 20";
//    char *infix = "1145 + 14512 * 53113 / (45141 - 1545 * 15436 ^ (1437 + 143584) * 435149) ^ 24350";
//    char *infix = "2 ^ 5 * 3 + 6";
    int infixLength = strlen(infix);
    char postfix[infixLength * 2];
    infixToPostfix(infix, postfix, infixLength);
    printf("infix = %s\n", infix);
    printf("postfix = %s\n", postfix);

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
    printf("printStack(): ");
    Node *current = stack->head;
    while (current!= NULL) {
        printf("%c ", current->value);
        current = current->next;
    }
    puts("");
}