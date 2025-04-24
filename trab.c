#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define MAX_BUCKETS 10000
#define INSERTION_THRESHOLD 32 

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

/* =================== Merge Sort Otimizado =================== */

void merge(int *vet, int *temp, int lo, int mid, int hi) {
    int i = lo, j = mid + 1, k = lo;

    while (i <= mid && j <= hi) {
        if (vet[i] <= vet[j]) {
            temp[k++] = vet[i++];
        } else {
            temp[k++] = vet[j++];
        }
    }

    while (i <= mid) temp[k++] = vet[i++];
    while (j <= hi) temp[k++] = vet[j++];

    memcpy(vet + lo, temp + lo, (hi - lo + 1) * sizeof(int));
}

void mergeSortRec(int *vet, int *temp, int lo, int hi) {
    int mid;
    if (hi - lo <= INSERTION_THRESHOLD) {
        insertionSort(vet + lo, hi - lo + 1);
        return;
    }

    mid = lo + (hi - lo) / 2;
    mergeSortRec(vet, temp, lo, mid);
    mergeSortRec(vet, temp, mid + 1, hi);
    merge(vet, temp, lo, mid, hi);
}

void mergeSort(int *vet, int n) {
    int *temp = malloc(n * sizeof(int));
    if (n <= 1) return;

    if (!temp) {
        printf("Erro: Falha na alocação de memória temporária\n");
        exit(1);
    }

    mergeSortRec(vet, temp, 0, n - 1);
    free(temp);
}

/* =================== Bucket Sort Otimizado =================== */

void bucketSort(int *array, int n) {
    int i, j, k, idx, max = 0;
    int **buckets, *bucketSizes;
    int N_BUCKETS;

    if (n <= 0) return;

    N_BUCKETS = (int)sqrt(n);
    if (N_BUCKETS > MAX_BUCKETS) N_BUCKETS = MAX_BUCKETS;
    if (N_BUCKETS <= 0) N_BUCKETS = 1;

    buckets = malloc(N_BUCKETS * sizeof(int *));
    bucketSizes = calloc(N_BUCKETS, sizeof(int));
    if (!buckets || !bucketSizes) {
        printf("Erro na alocação de buckets\n");
        exit(1);
    }

    for (i = 0; i < N_BUCKETS; i++) {
        buckets[i] = malloc(64 * sizeof(int));
        if (!buckets[i]) {
            printf("Erro ao alocar bucket %d\n", i);
            exit(1);
        }
    }

    for (i = 0; i < n; i++) {
        if (array[i] > max) max = array[i];
    }
    if (max == INT_MAX) max--;

    for (i = 0; i < n; i++) {
        if (max == 0) idx = 0;
        else idx = (int)((double)array[i] / (max + 1) * N_BUCKETS);

        if (idx < 0) idx = 0;
        if (idx >= N_BUCKETS) idx = N_BUCKETS - 1;

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
    int pivo = vet[lo + (hi - lo) / 2];
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
    int *vet, *copia1, *copia2, *copia3;
    clock_t t0, t1;

    printf("Escolha o tipo de array:\n");
    printf("1 - Aleatório\n2 - Parcialmente ordenado\nOpcao: ");
    scanf("%d", &opcao);

    printf("Tamanho do array (ex: 1000000): ");
    scanf("%d", &tamVet);

    vet = malloc(tamVet * sizeof(int));
    copia1 = malloc(tamVet * sizeof(int));
    copia2 = malloc(tamVet * sizeof(int));
    copia3 = malloc(tamVet * sizeof(int));
    if (!vet || !copia1 || !copia2 || !copia3) {
        printf("Erro na alocação\n");
        return 1;
    }

    srand(time(NULL));
    if (opcao == 1) {
        for (i = 0; i < tamVet; i++) vet[i] = rand() % tamVet;
    } else {
        for (i = 0; i < tamVet; i++) vet[i] = i + (rand() % 10);
    }

    memcpy(copia1, vet, tamVet * sizeof(int));
    memcpy(copia2, vet, tamVet * sizeof(int));
    memcpy(copia3, vet, tamVet * sizeof(int));

    /* Teste QuickSort */
    t0 = clock();
    quickSort(copia1, 0, tamVet - 1);
    t1 = clock();
    printf("QuickSort: %.2fs\n", difTempo(t0, t1));

    /* Teste MergeSort */
    t0 = clock();
    mergeSort(copia2, tamVet);
    t1 = clock();
    printf("MergeSort: %.2fs\n", difTempo(t0, t1));

    /* Teste BucketSort */
    t0 = clock();
    bucketSort(copia3, tamVet);
    t1 = clock();
    printf("BucketSort: %.2fs\n", difTempo(t0, t1));

    free(vet);
    free(copia1);
    free(copia2);
    free(copia3);

    return 0;
}
