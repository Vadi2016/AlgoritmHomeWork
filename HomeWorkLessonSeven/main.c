

/* 
 * 4. *Создать библиотеку функций для работы с графами 
 *
 * 
 */


#include "help.h"
#include "graphlibs.h"

/*
 * 1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран
 */
void readMatrix()
{
	int **amatrix;		
	int x; // size of matrix
	char *fileName = "for_1.txt";

	amatrix = graphReadAdjacencyMatrix(fileName, &x);
	printMatrix(x, x, amatrix);
}

/*
 * 2. Написать рекурсивную функцию обхода графа в глубину.
 */
void recursCirc()
{
	int **amatrix; // without init. It will do in the function
	int x; // size of matrix
	char *fileName = "for_2.txt";
	int start = 2;

	amatrix = graphReadAdjacencyMatrix(fileName, &x);
	printMatrix(x, x, amatrix);
	printf("\n");
	deepStepGraph(x, start, amatrix);
}

/*
 * 3. Написать функцию обхода графа в ширину.
 */
void bypassWidth()
{
	int **amatrix;
	int x; // size of matrix
	char *fileName = "for_3.txt";
	int start = 2;

	amatrix = graphReadAdjacencyMatrix(fileName, &x);
	printMatrix(x, x, amatrix);
	printf("\n");
	widthStepGraph(x, start, amatrix);
}

int main()
{
	readMatrix();

	printf("\n");

	recursCirc();

	printf("\n");

	bypassWidth();

	return 0;
}