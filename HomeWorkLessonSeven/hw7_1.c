#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "homework7.h"

/*
 * 1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.
 */

int main(int argc, char* argv[]) {
    	FILE* file = fopen("hw7_data.txt", "r");
    	int size = 0;
    	readFileToMatrix(file, &size);
	fclose(file);	
    	return 0;
}