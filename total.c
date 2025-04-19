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

/* Imprime um vetor de inteiros separados por virgula  */
static void print(int *vetor, int tam) {
    int cont;
    for(cont = 0; cont < tam; cont++) {
        if(cont == tam - 1) printf("%d\n", vetor[cont]);
        else printf("%d, ", vetor[cont]);
    }
}

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

/* Partição do QuickSort */
int partitionQS(int *vet, int low, int high) {
    int pivot = vet[high];
    int i = low - 1;
    int j;
    for(j = low; j < high; j++) {
        if(vet[j] < pivot) {
            i++;
            swap(&vet[i], &vet[j]);
        }
    }
    swap(&vet[i + 1], &vet[high]);
    return i + 1;
}

/* Ordena o vetor por QuickSort */
void quickSort(int *vet, int low, int high) {
    if(low < high) {
        int pi = partitionQS(vet, low, high);
        quickSort(vet, low, pi - 1);
        quickSort(vet, pi + 1, high);
    }
}

/* (Funcao principal) Menu de escolha para testar cada algoritmo de ordenacao */
int main() {
    int *vet, *copiavet /* , *copia_do_vetor_para_merge, *copia_do_vetor_para_heap */ ;
    int tamVet, opcao, limite, i;
    char linha[32];
    clock_t inicio = 0, fim = 0;
    double tempo_bucket, tempo_quick /* , tempo_merge, tempo_heap */ ;

    /* Inicializa semente aleatoria */
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
    copiavet = (int *)malloc(sizeof(int) * tamVet);
    /*
    copia_do_vetor_para_merge = (int *)malloc(sizeof(int) * tamVet);
    copia_do_vetor_para_heap = (int *)malloc(sizeof(int) * tamVet);
    */
    if (vet == NULL || copiavet == NULL) {
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
        free(copiavet);
        /*
        free(copia_do_vetor_para_merge)
        free(copia_do_vetor_para_heap)
        */
        return 1;
    }

    printf("\nValores gerados originalmente:\n");
    print(vet, tamVet);

    /* Faz cópia do vetor original para ambos algoritmos */
    for (i = 0; i < tamVet; i++) {
        copiavet[i] = vet[i] /* = copia_do_vetor_para_merge[i] = copia_do_vetor_para_heap[i] */ ;
    }

    /* Bucket Sort tradicional*/
    inicio = clock();
    bucketSortTradicional(vet, tamVet);
    tempo_bucket = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("\nValores ordenados com Bucket Sort:\n");
    print(vet, tamVet);

    /* Quick Sort */
    inicio = clock();
    quickSort(copiavet, 0, tamVet - 1);
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

    printf("\nTempo de execução:\n");
    printf("- Bucket Sort: %.4f segundos\n", tempo_bucket);
    printf("- Quick Sort : %.4f segundos\n", tempo_quick);

    free(vet);
    free(copiavet);
    /*
    free(copia_do_vetor_para_merge)
    free(copia_do_vetor_para_heap)
    */
    return 0;
}
