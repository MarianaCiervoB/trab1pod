#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Protótipos das funções */
void generateRandomArray(int *array, int size, int max_value);
void swap(int *a, int *b);
void insertionSort(int *array, int size);
void quickSort(int *array, int size);
void merge(int *array, int l, int m, int r);
void mergeSort(int *array, int l, int r);

/* Função principal */
int main() {
    int *array, *array_copy1, *array_copy2;
    int size, max_value, i;
    clock_t start, end;
    double quick_time, merge_time;

    /* Inicializa o gerador de números aleatórios */
    srand(time(NULL));

    printf("Digite o tamanho do array (ex: 1000000): ");
    scanf("%d", &size);
    
    if (size <= 0) {
        printf("Tamanho invalido.\n");
        return 1;
    }

    printf("Digite o valor maximo para os elementos: ");
    scanf("%d", &max_value);

    /* Aloca memória para os arrays */
    array = malloc(size * sizeof(int));
    array_copy1 = malloc(size * sizeof(int));
    array_copy2 = malloc(size * sizeof(int));
    
    if (!array || !array_copy1 || !array_copy2) {
        printf("Erro na alocacao de memoria.\n");
        if (array) free(array);
        if (array_copy1) free(array_copy1);
        if (array_copy2) free(array_copy2);
        return 1;
    }

    /* Gera o array aleatório */
    generateRandomArray(array, size, max_value);
    
    /* Faz cópias do array original */
    for (i = 0; i < size; i++) {
        array_copy1[i] = array[i];
        array_copy2[i] = array[i];
    }

    /* Testa o QuickSort */
    start = clock();
    quickSort(array_copy1, size);
    end = clock();
    quick_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    /* Testa o MergeSort */
    start = clock();
    mergeSort(array_copy2, 0, size - 1);
    end = clock();
    merge_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nResultados:\n");
    printf("QuickSort: %.2f segundos\n", quick_time);
    printf("MergeSort: %.2f segundos\n", merge_time);

    /* Libera a memória alocada */
    free(array);
    free(array_copy1);
    free(array_copy2);
    
    return 0;
}

/* Gera números aleatórios no vetor */
void generateRandomArray(int *array, int size, int max_value) {
    int i;
    for (i = 0; i < size; i++) {
        array[i] = rand() % (max_value + 1);
    }
}

/* Função auxiliar para trocar elementos */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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
    
    /* Cria uma pilha manual */
    stack = malloc(size * sizeof(int));
    
    /* Empilha os limites inicial e final */
    stack[++top] = 0;
    stack[++top] = size - 1;

    while (top >= 0) {
        /* Desempilha os limites */
        high = stack[top--];
        low = stack[top--];
        
        /* Particiona o array */
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
        
        /* Empilha os subarrays esquerdo e direito */
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

/* Implementação do Merge Sort */
void merge(int *array, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L, *R;

    /* Cria arrays temporários */
    L = malloc(n1 * sizeof(int));
    R = malloc(n2 * sizeof(int));

    /* Copia dados para os arrays temporários */
    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];

    /* Merge os arrays temporários de volta ao array principal */
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copia os elementos restantes de L[] */
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    /* Copia os elementos restantes de R[] */
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int *array, int l, int r) {
    int m;
    if (l < r) {
        m = l + (r - l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}
