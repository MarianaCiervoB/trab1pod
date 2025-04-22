#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Parametros:
 *   vetor - ponteiro para o vetor a ser impresso
 *   tam - tamanho do vetor
 *   vet - ponteiro para o vetor de destino
 *   limite - valor maximo para os numeros aleatorios
*/

/* Imprime um vetor de inteiros separados por virgula
static void print(int *vetor, int tam) {
    int cont;
    for(cont = 0; cont < tam; cont++) {
        if(cont == tam - 1) printf("%d\n", vetor[cont]);
        else printf("%d, ", vetor[cont]);
    }
}
*/

/* Gera numeros aleatorios e armazena em um vetor */
void geraN(int *vet, int tam, int limite) {
    int i;
    for(i = 0; i < tam; i++) {
        vet[i] = rand() % (limite + 1);
    }
}

/* Ordenacao parcial usando uma variacao do Shell Sort */
void parcOrdAsc(int *vet, int tam) {
    int i, j, k = 0, temp;
    int gaps[8] = {701,301,132,57,23,10,4,2};

    while (gaps[k] > ((tam / 2) - 1)) {
        k++;
    }
    while(gaps[k] >= 1) {
        for(i = gaps[k]; i < tam; i++) {
            temp = vet[i];
            j = i - gaps[k];
            while(j >= 0 && temp < vet[j]) {
                vet[j + gaps[k]] = vet[j];
                j -= gaps[k];
            }
            vet[j + gaps[k]] = temp;
        }
        k++;
    }
}

/* Ordenacao por insercao (usado pelo Bucket Sort) */
void insertionSort(int *vet, int tam) {
    int i, j, key;
    for(i = 1; i < tam; i++) {
        key = vet[i];
        j = i - 1;
        while(j >= 0 && vet[j] > key) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = key;
    }
}

/* Ordenacao por baldes (Bucket Sort) */
void bucketSortTradicional(int *vet, int tam) {
    int max_val = vet[0];
    int i, j, index = 0;

    /* Cria os baldes */
    int num_buckets = tam;
    int **buckets = (int **)malloc(num_buckets * sizeof(int *));
    int *bucket_sizes = (int *)calloc(num_buckets, sizeof(int));

    /* Aloca memoria para cada balde */
    for(i = 0; i < num_buckets; i++) {
        buckets[i] = (int *)malloc(tam * sizeof(int));
    }
    /* Encontra o maior valor */
    for(i = 1; i < tam; i++) {
        if(vet[i] > max_val) max_val = vet[i];
    }
    /* Distribui os elementos nos baldes */
    for(i = 0; i < tam; i++) {
        int bucket_idx = (vet[i] * num_buckets) / (max_val + 1);
        buckets[bucket_idx][bucket_sizes[bucket_idx]++] = vet[i];
    }
    /* Ordena cada balde e concatena os resultados */
    for(i = 0; i < num_buckets; i++) {
        if(bucket_sizes[i] > 0) {
            insertionSort(buckets[i], bucket_sizes[i]);
            for(j = 0; j < bucket_sizes[i]; j++) {
                vet[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);
    }
    /* Libera memoria */
    free(buckets);
    free(bucket_sizes);
}

/* Troca dois elementos */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Ordena por implementação do QuickSort iterativo */
void quickSort(int *vet, int tam) {
    int *stack;
    int top = -1;
    int high, low, pivot, i, j, partition;
    
    /* Cria uma pilha manual */
    stack = malloc(tam * sizeof(int));
    
    /* Empilha os limites inicial e final */
    stack[++top] = 0;
    stack[++top] = tam - 1;

    while (top >= 0) {
        /* Desempilha os limites */
        high = stack[top--];
        low = stack[top--];
        
        /* Particiona o vetor */
        pivot = vet[high];
        i = low - 1;
        
        for (j = low; j <= high - 1; j++) {
            if (vet[j] < pivot) {
                i++;
                swap(&vet[i], &vet[j]);
            }
        }
        swap(&vet[i + 1], &vet[high]);
        partition = i + 1;
        
        /* Empilha os subarrays esquerdo e direito */
        if (partition - 1 > low) {
            stack[++top] = low;
            stack[++top] = partition - 1;
        }
        
        if (partition + 1 < high) {
            stack[++top] = partition + 1;
            stack[++top] = high;
        }
    }
    
    free(stack);
}

/* Implementação do Merge Sort */
void merge(int *vet, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L, *R;

    /* Cria arrays temporários */
    L = malloc(n1 * sizeof(int));
    R = malloc(n2 * sizeof(int));

    /* Copia dados para os arrays temporários */
    for (i = 0; i < n1; i++)
        L[i] = vet[l + i];
    for (j = 0; j < n2; j++)
        R[j] = vet[m + 1 + j];

    /* Merge os arrays temporários de volta ao array principal */
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            j++;
        }
        k++;
    }
    /* Copia os elementos restantes de L[] */
    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }
    /* Copia os elementos restantes de R[] */
    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(int *vet, int l, int r) {
    int m;
    if (l < r) {
        m = l + (r - l) / 2;
        mergeSort(vet, l, m);
        mergeSort(vet, m + 1, r);
        merge(vet, l, m, r);
    }
}

/* (Funcao principal) Menu de escolha para testar cada algoritmo de ordenacao */
int main() {
    int *vet, *copia_vet_1, *copia_vet_2, *copia_vet_3;
    int tamVet, opcao, limite, i;
    char linha[32];
    clock_t inicio, fim;
    double tempo_bucket, tempo_quick, tempo_merge, tempo_heap;

    /* Inicializa o gerador de números aleatórios */
    srand(time(NULL));

    /* Menu de opcoes */
    printf("Escolha uma opcao:\n");
    printf("1 - Ordenar valores aleatorios\n");
    printf("2 - Ordenar valores parcialmente ordenados\n");
    printf("Opcao: ");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &opcao);

    printf("Quantidade de valores: ");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &tamVet);

    vet = (int *)malloc(sizeof(int) * tamVet);
    copia_vet_1 = (int *)malloc(sizeof(int) * tamVet);
    copia_vet_2 = (int *)malloc(sizeof(int) * tamVet);
    copia_vet_3 = (int *)malloc(sizeof(int) * tamVet);

    if (vet == NULL || copia_vet_1 == NULL /* || copia_do_vetor_para_merge == NULL || copia_do_vetor_para_heap == NULL */) {
    printf("Erro de alocacao de memoria.\n");
    return 1;
    }

    printf("Limite superior dos valores: ");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &limite);

    if (opcao == 1) {
        geraN(vet, tamVet, limite);
    } else if (opcao == 2) {
        geraN(vet, tamVet, limite);
        parcOrdAsc(vet, tamVet);
    } else {
        printf("Opcao invalida.\n");
        free(vet);
        free(copia_vet_1);
        /*
        free(copia_do_vetor_para_merge)
        free(copia_do_vetor_para_heap)
        */
        return 1;
    }

    /* Faz cópia do vetor original para ambos algoritmos */
    for (i = 0; i < tamVet; i++) {
        copia_vet_1[i] = vet[i] /* = copia_do_vetor_para_merge[i] = copia_do_vetor_para_heap[i] */ ;
    }

    /* Bucket Sort tradicional*/
    inicio = clock();
    bucketSortTradicional(vet, tamVet);
    fim = clock();
    tempo_bucket = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    /* Quick Sort */
    inicio = clock();
    quickSort(copia_vet_1, tamVet - 1);
    fim = clock();
    tempo_quick = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    /*
    MergeSort(vet, tamVet);
    printf("\n- Merge Sort:\n");
    print(vet, tamVet);

    HeapSort(vet, tamVet);
    printf("\n- Heap Sort:\n");
    print(vet, tamVet);
    */

    printf("\nTempo de execucao:\n");
    printf("- Bucket Sort: %.4f segundos\n", tempo_bucket);
    printf("- Quick Sort : %.4f segundos\n", tempo_quick);

    free(vet);
    free(copia_vet_1);
    /*
    free(copia_do_vetor_para_merge)
    free(copia_do_vetor_para_heap)
    */
    return 0;
}
