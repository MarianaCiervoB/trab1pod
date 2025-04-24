#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_LINE 16

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

/* =================== Bucket Sort =================== */

void bucketSort(int *array, int n) {
    int N_BUCKETS, max, stepSize, idx, k, i, j, m, chave;
    int **buckets, *bucketCount, *bucketCapacity;
    int *tmp;

    N_BUCKETS = (int)sqrt(n); /* número padrão de buckets */
    if (N_BUCKETS > 10000) N_BUCKETS = 10000;

    buckets = malloc(N_BUCKETS * sizeof(int*));
    bucketCount = calloc(N_BUCKETS, sizeof(int));
    bucketCapacity = malloc(N_BUCKETS * sizeof(int));

    stepSize = 64; /* tamanho inicial e fator de crescimento */

    for (i = 0; i < N_BUCKETS; i++) {
        bucketCapacity[i] = stepSize;
        buckets[i] = malloc(stepSize * sizeof(int));
    }

    /* encontra o maior valor pra normalizar */
    max = array[0];
    for (i = 1; i < n; i++) {
        if (array[i] > max) max = array[i];
    }

    /* distribui os valores nos buckets */
    for (i = 0; i < n; i++) {
        idx = (array[i] * N_BUCKETS) / (max + 1);
        if (bucketCount[idx] >= bucketCapacity[idx]) {
            bucketCapacity[idx] *= 2;
            tmp = realloc(buckets[idx], bucketCapacity[idx] * sizeof(int));
            if (!tmp) {
                printf("Erro de realocação no bucket %d\n", idx);
                exit(1);
            }
            buckets[idx] = tmp;
        }
        buckets[idx][bucketCount[idx]++] = array[i];
    }

    /* ordena e junta */
    k = 0;
    for (i = 0; i < N_BUCKETS; i++) {
        if (bucketCount[i] > 0) {
            /* insertionSort */
            for (j = 1; j < bucketCount[i]; j++) {
                chave = buckets[i][j];
                m = j - 1;
                while (m >= 0 && buckets[i][m] > chave) {
                    buckets[i][m + 1] = buckets[i][m];
                    m--;
                }
                buckets[i][m + 1] = chave;
            }

            /* copia pro array final */
            for (j = 0; j < bucketCount[i]; j++) {
                array[k++] = buckets[i][j];
            }
        }
    }

    for (i = 0; i < N_BUCKETS; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketCount);
    free(bucketCapacity);
}

/* =================== Quick Sort =================== */

int partition(int *vet, int lo, int hi) {
  int pivo = vet[lo];
  int i = lo - 1;
  int j = hi + 1;
  int aux;

  while (1) {
    do { j--; } while (vet[j] > pivo);
    do { i++; } while (vet[i] < pivo);

    if (i < j) {
      aux = vet[i];
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

/* =================== Heap Sort =================== */

void heapsort(int a[], int n) {
  int i = n / 2;
  int pai, filho, t;

  for (;;) {
    if (i > 0) {
      i--;
      t = a[i];
    } else {
      n--;
      if (n == 0) return;
      t = a[n];
      a[n] = a[0];
    }

    pai = i;
    filho = i * 2 + 1;

    while (filho < n) {
      if ((filho + 1 < n) && (a[filho + 1] > a[filho]))
        filho++;
      if (a[filho] > t) {
        a[pai] = a[filho];
        pai = filho;
        filho = pai * 2 + 1;
      } else {
        break;
      }
    }
    a[pai] = t;
  }
}

/* =================== Bubble Sort =================== */

void bubbleSort(int *vetor, int tam) {
  int cont, troca, aux;
  do {
    troca = 0;
    for (cont = 0; cont < (tam - 1); cont++) {
      if (vetor[cont] > vetor[cont + 1]) {
        aux = vetor[cont];
        vetor[cont] = vetor[cont + 1];
        vetor[cont + 1] = aux;
        troca = 1;
      }
    }
  } while (troca);
}

/* =================== MAIN =================== */

int main() {
  int i, tamVet, opcao;
  int *vet, *copia1, *copia2, *copia3;
  clock_t t0, t1;

  printf("Escolha o tipo de array:\n");
  printf("1 - Array completamente aleatorio\n");
  printf("2 - Array parcialmente ordenado\n");
  printf("Opcao: ");
  scanf("%d", &opcao);

  printf("Digite o tamanho do array (ex: 1000000): ");
  scanf("%d", &tamVet);

  vet = (int *)malloc(sizeof(int) * tamVet);
  copia1 = (int *)malloc(sizeof(int) * tamVet);
  copia2 = (int *)malloc(sizeof(int) * tamVet);
  copia3 = (int *)malloc(sizeof(int) * tamVet);

  if (!vet || !copia1 || !copia2 || !copia3) {
    printf("Erro ao alocar memoria\n");
    return 1;
  }

  srand(time(NULL));

  if (opcao == 1) {
    for (i = 0; i < tamVet; i++) {
      vet[i] = rand();
    }
  } else {
    for (i = 0; i < tamVet; i++) {
      vet[i] = i + (rand() % 10);
    }
  }

  memcpy(copia1, vet, sizeof(int) * tamVet);
  memcpy(copia2, vet, sizeof(int) * tamVet);
  memcpy(copia3, vet, sizeof(int) * tamVet);

  printf("\nResultados:\n");

 /* t0 = clock();
  bubbleSort(vet, tamVet);
  t1 = clock();
  printf("BubbleSort: %.2f segundos\n", difTempo(t0, t1));*/

  t0 = clock();
  quickSort(copia1, 0, tamVet - 1);
  t1 = clock();
  printf("QuickSort: %.2f segundos\n", difTempo(t0, t1));

  t0 = clock();
  heapsort(copia2, tamVet);
  t1 = clock();
  printf("HeapSort: %.2f segundos\n", difTempo(t0, t1));

  t0 = clock();
  bucketSort(copia3, tamVet);
  t1 = clock();
  printf("BucketSort: %.2f segundos\n", difTempo(t0, t1));

  free(vet);
  free(copia1);
  free(copia2);
  free(copia3);

  return 0;
}
