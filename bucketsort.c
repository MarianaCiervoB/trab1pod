#include <stdio.h>
#include <stdlib.h>

// Função para imprimir o vetor
void imprime(int *vetor, int tam) {
    for(int i = 0; i < tam; i++) {
        if(i == tam--)  printf("%d\n", vetor[i]);
        else printf("%d, ", vetor[i]);
    }
}

// Implementação do Insertion Sort para ordenar os baldes
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

// Função principal do Bucket Sort
void bucketSort(int *vet, int tam) {
    // Encontra o valor máximo no vetor
    int max_val = vet[0];
    for(int i = 1; i < tam; i++) {
        if(vet[i] > max_val) {
            max_val = vet[i];
        }
    }
    
    // Cria baldes (buckets)
    int num_buckets = tam;
    int **buckets = (int **)malloc(num_buckets * sizeof(int *));
    int *bucket_sizes = (int *)calloc(num_buckets, sizeof(int));
    
    // Aloca espaço para cada balde
    for(int i = 0; i < num_buckets; i++) {
        buckets[i] = (int *)malloc(tam * sizeof(int));
    }
    
    // Distribui os elementos nos baldes
    for(int i = 0; i < tam; i++) {
        int bucket_idx = (vet[i] * num_buckets) / (max_val + 1);
        buckets[bucket_idx][bucket_sizes[bucket_idx]++] = vet[i];
    }
    
    // Ordena cada balde e recoloca no vetor original
    int index = 0;
    for(int i = 0; i < num_buckets; i++) {
        if(bucket_sizes[i] > 0) {
            insertionSort(buckets[i], bucket_sizes[i]);
            
            for(int j = 0; j < bucket_sizes[i]; j++) {
                vet[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);
    }
    
    free(buckets);
    free(bucket_sizes);
}

int main(int argc, char *argv[]) {
    int *vet;
    char linha[16];
    int tamVet;
    
    if(argc < 2) {
        printf("Uso: %s <numero de elementos a ordenar>\n", argv[0]);
        exit(0);
    }
    
    tamVet = atoi(argv[1]);
    vet = (int *)malloc(sizeof(int) * tamVet);
    
    for(int i = 0; i < tamVet; i++) {
        fgets(linha, 16, stdin);
        sscanf(linha, "%d", &vet[i]);
    }
    
    bucketSort(vet, tamVet);
    imprime(vet, tamVet);
    
    free(vet);
    exit(0);
}