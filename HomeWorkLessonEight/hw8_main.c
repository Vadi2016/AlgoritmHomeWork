#include "helpers.h"
#define SIZE	1000000

/*
 * 1. Реализовать сортировку подсчетом.
 *
 *  простой алгоритм
 int k;
 for (int i = 0; i < n; i++)
 {
	k = 0;
	for (int j = 0; j < n; j++) {
		if (arr[i] > arr[j])
			k++;
 }
 retArr[k] = arr[i];
 }
 */
int* countSort(int* arr, int n)
{
	int* retArr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		//memset(retArr[i], 0, sizeof(int));
		retArr[i] = 0;
	}
	/* квадратичный алгоритм */
	int c;

	for (int i = 0; i < n; i++) {
		c = 0;
		for (int j = 0; j < i; j++) {
			if (arr[j] <= arr[i]) {
				c++;
			}
		}
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[i]) {
				c++;
			}
		}
		retArr[c] = arr[i];
	}
	return retArr;
}

/*
 * 2. Реализовать быструю сортировку.
 */
void quickSort(int* arr, int n)
{
	int i = 0;
	int j = n - 1;

	int mid = arr[n / 2];

	do {
		while (arr[i] < mid) { i++; }
		while (arr[j] > mid) { j--; }
		if (i <= j) {
			if (arr[i] > arr[j]) { swap(&arr[i], &arr[j]); }
			i++;
			j--;
		}
	} while (i <= j);


	if (j > 0) {
		quickSort(arr, j + 1);
	}
	if (i < n) {
		quickSort(&arr[i], n -  i);
	}
}

/*
 * 3. *Реализовать сортировку слиянием.
 */
void mergeSort(int* arr, int l, int n, int size)
{
	if (n <= l) return; 
	int mid = l + (n - l) / 2;

	mergeSort(arr, l, mid,size);
	mergeSort(arr, mid + 1, n,size);

	int i = l;  
	int j = mid + 1; 
	int *tmp = (int*)malloc(n * sizeof(int));

	memcpy(tmp, arr, sizeof(int) * size);

	for (int k = l; k <= n; k++) {
		tmp[k] = arr[k];
	}

	for (int k = l; k <= n; k++) {
		if (i > mid) {
			arr[k] = tmp[j];
		}
		else if (j > n) {
			arr[k] = tmp[i];
		}
		else if (tmp[j] < tmp[i]) {
			arr[k] = tmp[j];
		}
		else {
			arr[k] = tmp[i];
			i++;
		}
	}
}

/*
 * 4. **Реализовать алгоритм сортировки со списком
 */
void listSort(int* arr, int n)
{
	int min = arr[0];
	int max = arr[0];

	for (int i = 1; i < n; i++) 	{
		if (arr[i] < min)	{
			min = arr[i];
		}
		if (arr[i] > max)	{
			max = arr[i];
		}
	}

	int *current = arr;
	int size = max - min + 1, count = 0, i;
	int* holes = malloc(size * sizeof(int));

	for (i = 0; i < size; i++) {
		holes[i] = 0;
	}

	for (i = 0; i < size; i++, current++) {
		holes[*current - min] += 1;
	}

	for (count = 0, current = &arr[0]; count < size; count++)	{
		while (holes[count]--> 0) {
			*current++ = count + min;
		}
	}
}

int main(int argc, char* argv[])
{
	int* arr = malloc(SIZE * sizeof(int));
	int* arr1 = malloc(SIZE * sizeof(int));
	int* arr2 = malloc(SIZE * sizeof(int));
	int* sortArr;

	fill_array(arr, SIZE);
	memcpy(arr1, arr, sizeof(int) * SIZE);
	memcpy(arr2, arr, sizeof(int) * SIZE);

	printarray(arr, SIZE);
	double start = clock();
	sortArr = countSort(arr, SIZE);
	printf("Count Sort = %.8lf\n", (clock() - start) / CLOCKS_PER_SEC);
	printarray(sortArr, SIZE);

	printf("\n");

	printarray(arr, SIZE);
	start = clock();
	quickSort(arr, SIZE);
	printf("Quick Sort = %.8lf\n", (clock() - start) / CLOCKS_PER_SEC);
	printarray(arr, SIZE);

	printf("\n");

	printarray(arr1, SIZE);
	start = clock();
	mergeSort(arr1, 0, SIZE - 1, SIZE);
	printf("Merge Sort = %.8lf\n", (clock() - start) / CLOCKS_PER_SEC);
	printarray(arr1, SIZE);

	printf("\n");

	printarray(arr2, SIZE);
	start = clock();
	listSort(arr2, SIZE);
	printarray(arr2, SIZE);
	printf("List Sort = %.8lf\n", (clock() - start) / CLOCKS_PER_SEC);

	printf("\n");

	return 0;
}