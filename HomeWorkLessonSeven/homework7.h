


// Тут код
int* readFileToMatrix(FILE *file, int *size) {
    	if (file == NULL) {
        	puts("Can't open file!");
    	}
    	fscanf(file, "%d", size); // Считываем количество записей
    	int *arr;
    	arr = (int*)malloc(*size * *size * sizeof(int));
	//    int arr[size][size];
    	for(int i = 0; i < *size; i++) {
        	for (int j = 0; j < *size; j++) {
            		fscanf(file, "%d", (arr + i * *size + j));
        	}
    	}
	
    	fclose(file);
	
    	return arr;
}

void printMatrix(int **arr, int size) {
    	for (int i = 0; i < size; i++) {
        	for (int j = 0; j < size; j++) {
            		printf("%d ", arr[i][j]);
        	}
        	puts("");
    	}
}

