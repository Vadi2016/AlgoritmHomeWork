#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>


/*
 * 3. *Разработать базу данных студентов из трёх полей “Имя”, “Возраст”, “Табельный номер” в
 * которой? ?использовать? ?все? ?знания,? ?полученные? ?на? ?уроках. Считайте данные в двоичное дерево поиска.
 * Реализуйте поиск по какому-нибудь полю базы данных,? ?например,? ?возраст? ?или? ?номер.
 */

typedef struct Student {
    char *name;
    int age;
    int id;
} Student;

typedef struct Node {
    Student *data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

// Распечатка двоичного дерева в виде скобочной записи
void printTree(Node *node) {
    if (node)
    {
        printf("%s:%d:%d",node->data->name, node->data->age, node->data->id);
        if (node->left || node->right)
        {
            printf("(");
            if (node->left)
                printTree(node->left);
            else
                printf("NULL");
            printf(",");
            if (node->right)
                printTree(node->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

// Создание нового узла
Node* getFreeNode(Student *student, Node *parent) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = student;
    tmp->parent = parent;
    return tmp;
}

// Вставка узла. Дерево сортируется по id
void insertById(Node **Root, Student *student) {
    Node *tmp = NULL;
    if (*Root == NULL)
    {
        *Root = getFreeNode(student, NULL);
        return;
    }
    tmp = *Root;
    while (tmp)
    {
        if (student->id > tmp->data->id)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = getFreeNode(student, tmp);
                return;
            }
        }
        else if (student->id < tmp->data->id)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = getFreeNode(student, tmp);
                return;
            }
        }
        else
        {
            exit(2);// дерево построено неправильно
        }
    }
}

Node* searchStudentById(Node *node, int id) {
    if (id == node->data->id) {
        printf("%s found", node->data->name);
        return node;
    }
    else if (id < node->data->id && node->left != NULL) return searchStudentById(node->left, id);
    else if (id > node->data->id && node->right != NULL) return searchStudentById(node->right, id);
    printf("Student not found");
    return NULL;
}


int main(int argc, char* argv[])
{
    Node *Tree = NULL;
    FILE* file = fopen("data_stud.txt", "r");
    if (file == NULL)
    {
        puts("Can't open file!");
        exit(1);
    }
	
    char *line = NULL;
    int length = 0;

    // Построчно читаем из файла данные студентов
    while (fgets(line, length, file) != -1 ) {
        char *token = NULL;
        Student *newStudent = (Student*) malloc(sizeof(Student));
        token = strtok(line, " "); // Разбиваем строку пробелами и получаем первую часть
        newStudent->name = (char*) malloc(strlen(token) + 1);
        strcpy(newStudent->name, token); // Обычное присвоение приведет к тому, что имя у всех студентов будет одинаковое. 
        token = strtok(NULL, " "); // Получаем вторую часть строки из файла
        newStudent->age = atoi(token);
        token = strtok(NULL, " "); // Получаем третью часть строки из файла
        newStudent->id = atoi(token);
        free(token);
        insertById(&Tree, newStudent);
    }
    fclose(file);

    printTree(Tree);

    int n = 2006;
    printf("\nSearch id %d: ", n);
    searchStudentById(Tree, n);
    n = 2001;
    printf("\nSearch id %d: ", n);
    searchStudentById(Tree, n);
    return 0;
}