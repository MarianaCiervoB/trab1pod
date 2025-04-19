#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Função que imprime um vetor de inteiros separados por vírgula */
static void print(int *vetor, int tam) {
    int cont;
    for(cont = 0; cont < tam; cont++) {
        if(cont == tam - 1) printf("%d\n", vetor[cont]);
        else printf("%d, ", vetor[cont]);
    }
}

/* Gera N números aleatórios entre 0 e limite (ou tam) */
void geraN(int *vet, int tam, int limite) {
    int i;
    for(i = 0; i < tam; i++) {
        vet[i] = rand() % (limite + 1);
    }
}

/* Ordenação parcial com Shell Sort (parcial) */
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

/* Insertion Sort */
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

/* Bucket Sort */
void bucketSort(int *vet, int tam) {
    int max_val = vet[0];
    int i, j, index = 0;

    int num_buckets = tam;
    int **buckets = (int **)malloc(num_buckets * sizeof(int *));
    int *bucket_sizes = (int *)calloc(num_buckets, sizeof(int));

    for(i = 0; i < num_buckets; i++) {
        buckets[i] = (int *)malloc(tam * sizeof(int));
    }

    for(i = 1; i < tam; i++) {
        if(vet[i] > max_val) max_val = vet[i];
    }

    for(i = 0; i < tam; i++) {
        int bucket_idx = (vet[i] * num_buckets) / (max_val + 1);
        buckets[bucket_idx][bucket_sizes[bucket_idx]++] = vet[i];
    }

    for(i = 0; i < num_buckets; i++) {
        if(bucket_sizes[i] > 0) {
            insertionSort(buckets[i], bucket_sizes[i]);
            for(j = 0; j < bucket_sizes[i]; j++) {
                vet[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucket_sizes);
}

/* Função principal */
int main() {
    int *vet;
    int tamVet, opcao, limite;
    char linha[32];

    srand(time(NULL));

    printf("Escolha uma opção:\n");
    printf("1 - Ordenar valores aleatórios\n");
    printf("2 - Ordenar valores parcialmente ordenados\n");
    printf("Opção: ");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &opcao);

    printf("Quantidade de valores: ");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &tamVet);

    vet = (int *)malloc(sizeof(int) * tamVet);
    if (vet == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    if (opcao == 1) {
        printf("Limite superior dos valores (ex: 100): ");
        fgets(linha, sizeof(linha), stdin);
        sscanf(linha, "%d", &limite);
        geraN(vet, tamVet, limite);
    } else if (opcao == 2) {
        printf("Limite superior dos valores (ex: 100): ");
        fgets(linha, sizeof(linha), stdin);
        sscanf(linha, "%d", &limite);
        geraN(vet, tamVet, limite);
        parcOrdAsc(vet, tamVet);
    } else {
        printf("Opção inválida.\n");
        free(vet);
        return 1;
    }

    printf("\nValores antes do Bucket Sort:\n");
    print(vet, tamVet);

    bucketSort(vet, tamVet);

    printf("\nValores após o Bucket Sort:\n");
    print(vet, tamVet);

    free(vet);
    return 0;
}
