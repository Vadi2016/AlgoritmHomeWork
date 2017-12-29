#include <stdio.h>
#include <malloc.h>

/*
 * 4. *Создать функцию, копирующую односвязный список (то есть создает в памяти копию  односвязного? ?списка,?
 * ?без? ?удаления? ?первого? ?списка).
 */

#define MaxN 1000
#define T int

struct TNode {
    T value;
    struct TNode *next;
};
typedef struct TNode Node;

void listAdd(Node **head, T value);
void listCopy(Node *from, Node **to);
void printList(Node *head, char *title);

int main() {
    Node *head1 = NULL;
    printList(head1, "list 1:");
    for (int i = 1; i <= 10; i++) {
        listAdd(&head1, i);
    }
    printList(head1, "list 1:");

    Node *head2 = NULL;
    listCopy(head1, &head2);
    printList(head2, "list 2:");

    listAdd(&head1, 20);
    listAdd(&head2, 30);
    printList(head1, "list 1:");
    printList(head2, "list 2:");

    return 0;
}

void listAdd(Node **head, T value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    printf("Added: %2d\n", node->value);

    if (*head == NULL) {
        *head = node;
        return;
    }
    Node *tmp = *head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = node;
}

void listCopy(Node *from, Node **to) {
    if (from == NULL) {
        printf("Error: can't copy list. Head is NULL\n");
        return;
    }
    *to = NULL;

    Node *current = (Node*)malloc(sizeof(Node));
    current->value = from->value;
    current->next = NULL;
    *to = current;
    from = from->next;

    while (from != NULL) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->value = from->value;
        newNode->next = NULL;

        current->next = newNode;
        current = current->next;

        from = from->next;
    }
}

void printList(Node *head, char *title) {
    Node *tmp = head;
    printf("Print %s\n", title);
    if (head == NULL) {
        printf("Error: can't print empty list. Head is NULL\n");
        return;
    }
    while (tmp != NULL) {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    puts("");
}