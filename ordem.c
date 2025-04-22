#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Protótipos das funções */
void generateRandomArray(int *array, int size, int max_value);
void generatePartiallySortedArray(int *array, int size, int max_value);
void swap(int *a, int *b);
void insertionSort(int *array, int size);
void bubbleSort(int *array, int size);  
void quickSort(int *array, int size);
void merge(int *array, int l, int m, int r);
void mergeSort(int *array, int l, int r);
void heapSort(int *array, int size);
void heapify(int *array, int size, int i);
void partialSort(int *array, int size);

/* Função principal */
int main() {
    int *array, *array_copy1, *array_copy2, *array_copy3, *array_copy4;
    int size, max_value, i, option;
    clock_t start, end;
    double quick_time, merge_time, heap_time, bubble_time;

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

    printf("Digite o valor maximo para os elementos: ");
    scanf("%d", &max_value);

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

    /* Testa o MergeSort */
    start = clock();
    mergeSort(array_copy2, 0, size - 1);
    end = clock();
    merge_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    /* Testa o HeapSort */
    start = clock();
    heapSort(array_copy3, size);
    end = clock();
    heap_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nResultados:\n");
    printf("BubbleSort: %.2f segundos\n", bubble_time);
    printf("QuickSort: %.2f segundos\n", quick_time);
    printf("MergeSort: %.2f segundos\n", merge_time);
    printf("HeapSort: %.2f segundos\n", heap_time);

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
    /* Primeiro gera um array aleatório */
    generateRandomArray(array, size, max_value);
    /* Depois aplica uma ordenação parcial */
    partialSort(array, size);
}

/* Ordenação parcial usando uma variação do Shell Sort */
void partialSort(int *array, int size) {
    int i, j, k = 0, temp;
    int gaps[8] = {701, 301, 132, 57, 23, 10, 4, 2};

    /* Encontra o gap inicial apropriado */
    while (gaps[k] > ((size / 2) - 1)) {
        k++;
    }
    
    /* Aplica apenas alguns passes do Shell Sort para ordenação parcial */
    while(gaps[k] >= 4) {  /* Paramos antes de completar toda a ordenação */
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

void heapSort(int *array, int size) {
    /* Declarar TODAS as variáveis no início */
    int i, j;  
    /* Construir o heap (reorganizar o array) */
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    /* Extrair elementos do heap um por um */
    for (j = size - 1; j > 0; j--) {
        swap(&array[0], &array[j]);
        heapify(array, j, 0);
    }
}

/* Função para transformar uma subárvore em um heap */
void heapify(int *array, int size, int i) {
    int largest = i;       /* Inicializa o maior como raiz */
    int left = 2 * i + 1;  /* índice do filho esquerdo */
    int right = 2 * i + 2; /* índice do filho direito */

    /* Se o filho esquerdo é maior que a raiz */
    if (left < size && array[left] > array[largest])
        largest = left;

    /* Se o filho direito é maior que o maior até agora */
    if (right < size && array[right] > array[largest])
        largest = right;

    /* Se o maior não é a raiz */
    if (largest != i) {
        swap(&array[i], &array[largest]);
        
        /* Heapify recursivamente a subárvore afetada */
        heapify(array, size, largest);
    }
}
