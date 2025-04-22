#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Protótipos das funções */
void generateRandomArray(int *array, int size, int max_value);
void generatePartiallySortedArray(int *array, int size, int max_value);
void partialSort(int *array, int size);
void swap(int *a, int *b);
void insertionSort(int *array, int size);
void bubbleSort(int *array, int size);  
void quickSort(int *array, int size);
void heapSort(int *array, int size);
void heapify(int *array, int size, int i);
void bucketSort(int *array, int size, int max_value);

/* Função principal */
int main() {
    int *array, *array_copy1, *array_copy2, *array_copy3, *array_copy4;
    int size, max_value, i, option;
    clock_t start, end;
    double quick_time, heap_time, bubble_time, bucket_time;

    /* Inicializa o gerador de números aleatórios */
    srand(time(NULL));

    printf("Escolha o tipo de array:\n");
    printf("1 - Array completamente aleatorio\n");
    printf("2 - Array parcialmente ordenado\n");
    printf("Opcao: ");
    scanf("%d", &option);
    
    printf("Digite o tamanho do array (ex: 1000000): ");
    scanf("%d", &size);
    
    if (size <= 0) {
        printf("Tamanho invalido.\n");
        return 1;
    }
    max_value = size;

    /* Aloca memória para os arrays */
    array = malloc(size * sizeof(int));
    array_copy1 = malloc(size * sizeof(int));
    array_copy2 = malloc(size * sizeof(int));
    array_copy3 = malloc(size * sizeof(int));
    array_copy4 = malloc(size * sizeof(int));
    
    if (!array || !array_copy1 || !array_copy2 || !array_copy3 || !array_copy4) {
        printf("Erro na alocacao de memoria.\n");
        if (array) free(array);
        if (array_copy1) free(array_copy1);
        if (array_copy2) free(array_copy2);
        if (array_copy3) free(array_copy3);
        if (array_copy4) free(array_copy4);
        return 1;
    }

    /* Gera o array de acordo com a opção escolhida */
    if (option == 1) {
        generateRandomArray(array, size, max_value);
    } else if (option == 2) {
        generatePartiallySortedArray(array, size, max_value);
    } else {
        printf("Opcao invalida.\n");
        free(array);
        free(array_copy1);
        free(array_copy2);
        free(array_copy3);
        free(array_copy4);
        return 1;
    }
    
    /* Faz cópias do array original */
    for (i = 0; i < size; i++) {
        array_copy1[i] = array[i];
        array_copy2[i] = array[i];
        array_copy3[i] = array[i];
        array_copy4[i] = array[i];
    }

    /* Testa o BubbleSort */
    start = clock();
    bubbleSort(array_copy4, size);
    end = clock();
    bubble_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    /* Testa o QuickSort */
    start = clock();
    quickSort(array_copy1, size);
    end = clock();
    quick_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    /* Testa o HeapSort */
    start = clock();
    heapSort(array_copy3, size);
    end = clock();
    heap_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    /* Testa o BucketSort */
    start = clock();
    bucketSort(array_copy2, size, max_value);
    end = clock();
    bucket_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nResultados:\n");
    printf("BubbleSort: %.2f segundos\n", bubble_time);
    printf("QuickSort: %.2f segundos\n", quick_time);
    printf("HeapSort: %.2f segundos\n", heap_time);
    printf("BucketSort: %.2f segundos\n", bucket_time);

    /* Libera a memória alocada */
    free(array);
    free(array_copy1);
    free(array_copy2);
    free(array_copy3);
    free(array_copy4);
    
    return 0;
}

/* Gera números aleatórios no vetor */
void generateRandomArray(int *array, int size, int max_value) {
    int i;
    for (i = 0; i < size; i++) {
        array[i] = rand() % (max_value + 1);
    }
}

/* Gera um array parcialmente ordenado */
void generatePartiallySortedArray(int *array, int size, int max_value) {
    generateRandomArray(array, size, max_value);
    partialSort(array, size);
}

/* Ordenação parcial usando uma variação do Shell Sort */
void partialSort(int *array, int size) {
    int i, j, k = 0, temp;
    int gaps[8] = {701, 301, 132, 57, 23, 10, 4, 2};

    while (gaps[k] > ((size / 2) - 1)) {
        k++;
    }
    
    while(gaps[k] >= 4) {
        for(i = gaps[k]; i < size; i++) {
            temp = array[i];
            j = i - gaps[k];
            while(j >= 0 && temp < array[j]) {
                array[j + gaps[k]] = array[j];
                j -= gaps[k];
            }
            array[j + gaps[k]] = temp;
        }
        k++;
    }
}

/* Função auxiliar para trocar elementos */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Implementação do Bubble Sort */
void bubbleSort(int *array, int size) {
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

/* Implementação do Insertion Sort */
void insertionSort(int *array, int size) {
    int i, j, key;
    for (i = 1; i < size; i++) {
        key = array[i];
        j = i - 1;
        
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

/* Implementação do QuickSort iterativo */
void quickSort(int *array, int size) {
    int *stack;
    int top = -1;
    int high, low, pivot, i, j, partition_index;
    
    stack = malloc(size * sizeof(int));
    
    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];
        
        pivot = array[high];
        i = low - 1;
        
        for (j = low; j <= high - 1; j++) {
            if (array[j] < pivot) {
                i++;
                swap(&array[i], &array[j]);
            }
        }
        swap(&array[i + 1], &array[high]);
        partition_index = i + 1;
        
        if (partition_index - 1 > low) {
            stack[++top] = low;
            stack[++top] = partition_index - 1;
        }
        
        if (partition_index + 1 < high) {
            stack[++top] = partition_index + 1;
            stack[++top] = high;
        }
    }
    
    free(stack);
}

void heapSort(int *array, int size) {
    int i, j;
    
    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i);
    }

    for (j = size - 1; j > 0; j--) {
        swap(&array[0], &array[j]);
        heapify(array, j, 0);
    }
}

void heapify(int *array, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left] > array[largest]) {
        largest = left;
    }

    if (right < size && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&array[i], &array[largest]);
        heapify(array, size, largest);
    }
}

/* Implementação do Bucket Sort com Insertion Sort */
void bucketSort(int *array, int size, int max_value) {
    int i, j, k, index, bucket_count;
    int bucket_range;
    int **buckets;
    int *bucket_sizes;

    bucket_count = 10; 
    bucket_range = (max_value + 1) / bucket_count + 1;

    buckets = malloc(bucket_count * sizeof(int *));
    bucket_sizes = malloc(bucket_count * sizeof(int));

    for (i = 0; i < bucket_count; i++) {
        buckets[i] = malloc(size * sizeof(int));
        bucket_sizes[i] = 0;
    }

    for (i = 0; i < size; i++) {
        index = array[i] / bucket_range;
        buckets[index][bucket_sizes[index]++] = array[i];
    }

    for (i = 0; i < bucket_count; i++) {
        insertionSort(buckets[i], bucket_sizes[i]);
    }

    k = 0;
    for (i = 0; i < bucket_count; i++) {
        for (j = 0; j < bucket_sizes[i]; j++) {
            array[k++] = buckets[i][j];
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucket_sizes);
}

/* gcc -ansi -Wall -pedantic total.c -o total */
