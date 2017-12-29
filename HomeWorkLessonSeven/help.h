#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memory.h>

void printarray(int *arr, int len)
{
	printf("[");
	for (int i = 0; i < len; i++) {
		printf("%2i", arr[i]);
		if (i + 1 < len) {
			printf(", ");
		}
	}
	printf("]\n");
}

//srand(time(NULL));
void fill_array(int *arr, int len)
{
	//srand(time(NULL));
	for (int i = 0; i < len; i++) {
		arr[i] = rand() % 100;
	}
}

/*
* swap function
*/
void swap(int *x, int *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;

}