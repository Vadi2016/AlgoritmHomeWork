#include <stdio.h>
#include <memory.h>

/*
 * 1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе сумма кодов? ?символов.
 */

// Хэш-функция для строки в Java
int hash(char *string) {
    int sum = 0;
    int  length = strlen(string);
    for (int i = 0; i < length; i++) {
        sum = 31 * sum + string[i];
    }
    return sum;
}

int main() {
    char *s = "Hello world!";
    printf("Hashcode for string '%s' = %d", s, hash(s));
    return 0;
}