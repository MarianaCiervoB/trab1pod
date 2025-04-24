#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define MAX_BUCKETS 10000

/* =================== Funções Auxiliares =================== */

double difTempo(clock_t t0, clock_t t1) {
    return (double)(t1 - t0) / CLOCKS_PER_SEC;
}

void insertionSort(int *arr, int n) {
    int i, chave, j;
    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

/* =================== Bucket Sort Otimizado =================== */

void bucketSort(int *array, int n) {
    int i, j, k, idx, max = 0;
    int **buckets, *bucketSizes;
    int N_BUCKETS;

    if (n <= 0) return;

    /* Limita o número de buckets para evitar excesso de alocação */
    N_BUCKETS = (int)sqrt(n);
    if (N_BUCKETS > MAX_BUCKETS) N_BUCKETS = MAX_BUCKETS;
    if (N_BUCKETS <= 0) N_BUCKETS = 1;

    /* Aloca buckets */
    buckets = malloc(N_BUCKETS * sizeof(int *));
    bucketSizes = calloc(N_BUCKETS, sizeof(int));
    if (!buckets || !bucketSizes) {
        printf("Erro na alocação de buckets\n");
        exit(1);
    }

    /* Tamanho inicial de cada bucket (ajustável conforme necessidade) */
    for (i = 0; i < N_BUCKETS; i++) {
        buckets[i] = malloc(64 * sizeof(int));
        if (!buckets[i]) {
            printf("Erro ao alocar bucket %d\n", i);
            exit(1);
        }
    }

    /* Encontra o maior valor (evitando INT_MAX) */
    for (i = 0; i < n; i++) {
        if (array[i] > max) max = array[i];
    }
    if (max == INT_MAX) max--;

    /* Distribui os elementos nos buckets */
    for (i = 0; i < n; i++) {
        if (max == 0) idx = 0;
        else idx = (int)((double)array[i] / (max + 1) * N_BUCKETS);

        if (idx < 0) idx = 0;
        if (idx >= N_BUCKETS) idx = N_BUCKETS - 1;

        /* Redimensiona o bucket se necessário */
        if (bucketSizes[idx] % 64 == 0) {
            int newSize = bucketSizes[idx] + 64;
            int *temp = realloc(buckets[idx], newSize * sizeof(int));
            if (!temp) {
                printf("Erro ao realocar bucket %d\n", idx);
                exit(1);
            }
            buckets[idx] = temp;
        }
        buckets[idx][bucketSizes[idx]++] = array[i];
    }

    /* Ordena e copia de volta para o array */
    k = 0;
    for (i = 0; i < N_BUCKETS; i++) {
        if (bucketSizes[i] > 0) {
            insertionSort(buckets[i], bucketSizes[i]);
            for (j = 0; j < bucketSizes[i]; j++) {
                array[k++] = buckets[i][j];
            }
            free(buckets[i]);
        }
    }
    free(buckets);
    free(bucketSizes);
}

/* =================== Quick Sort (Hoare) =================== */

int partition(int *vet, int lo, int hi) {
    int pivo = vet[lo + (hi - lo) / 2];  /* Pivô no meio para evitar worst-case */
    int i = lo - 1;
    int j = hi + 1;
    while (1) {
        do { j--; } while (vet[j] > pivo);
        do { i++; } while (vet[i] < pivo);
        if (i < j) {
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        } else {
            return j;
        }
    }
}

void quickSort(int *vet, int lo, int hi) {
    if (lo < hi) {
        int p = partition(vet, lo, hi);
        quickSort(vet, lo, p);
        quickSort(vet, p + 1, hi);
    }
}

/* =================== MAIN =================== */

int main() {
    int i, tamVet, opcao;
    int *vet, *copia1, *copia2;
    clock_t t0, t1;

    printf("Escolha o tipo de array:\n");
    printf("1 - Aleatório\n2 - Parcialmente ordenado\nOpcao: ");
    scanf("%d", &opcao);

    printf("Tamanho do array (ex: 1000000): ");
    scanf("%d", &tamVet);

    /* Aloca memória */
    vet = malloc(tamVet * sizeof(int));
    copia1 = malloc(tamVet * sizeof(int));
    copia2 = malloc(tamVet * sizeof(int));
    if (!vet || !copia1 || !copia2) {
        printf("Erro na alocação\n");
        return 1;
    }

    /* Preenche o array */
    srand(time(NULL));
    if (opcao == 1) {
        for (i = 0; i < tamVet; i++) vet[i] = rand() % tamVet;
    } else {
        for (i = 0; i < tamVet; i++) vet[i] = i + (rand() % 10);
    }

    /* Copia para os arrays de teste */
    memcpy(copia1, vet, tamVet * sizeof(int));
    memcpy(copia2, vet, tamVet * sizeof(int));

    /* Teste QuickSort */
    t0 = clock();
    quickSort(copia1, 0, tamVet - 1);
    t1 = clock();
    printf("QuickSort: %.2fs\n", difTempo(t0, t1));

    /* Teste BucketSort */
    t0 = clock();
    bucketSort(copia2, tamVet);
    t1 = clock();
    printf("InsertionSort: %.2fs\n", difTempo(t0, t1));

    /* Libera memória */
    free(vet);
    free(copia1);
    free(copia2);

    return 0;
}
