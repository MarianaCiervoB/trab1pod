#include <stdio.h>
#include <stdlib.h>

/* Função que imprime um vetor de inteiros separados por vírgula,
   exceto o último elemento que é seguido por quebra de linha */
static void print(int *vetor, int tam) {
    int i;
    for(i = 0; i < tam; i++) {
        if(i == tam-1) printf("%d\n", vetor[i]);  /* Último elemento */ 
        else printf("%d, ", vetor[i]);            /* Demais elementos */ 
    }
}

/* Insertion Sort para ordenação individual dos baldes:
   - Percorre o vetor da esquerda para direita
   - Cada elemento é inserido na posição correta na parte já ordenada */
void insertionSort(int *vet, int tam) {
    int i, j, key;
    for(i = 1; i < tam; i++) {
        key = vet[i];  /* Elemento atual a ser posicionado */ 
        j = i - 1;
        
        /*  Move elementos maiores que 'key' para frente */
        while(j >= 0 && vet[j] > key) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = key;  /*  Insere o elemento na posição correta */
    }
}

/* Função principal do Bucket Sort:
   - Divide os elementos em vários "baldes"
   - Ordena cada balde individualmente
   - Concatena os baldes ordenados */
void bucketSort(int *vet, int tam) {
    /* Encontra o valor máximo para determinar os intervalos dos baldes */ 
    int max_val = vet[0];
    int i, j;
    int index = 0;

    /*  Criação dos baldes */
    int num_buckets = tam;  /* Número de baldes = tamanho do vetor */ 
    int **buckets = (int **)malloc(num_buckets * sizeof(int *));
    int *bucket_sizes = (int *)calloc(num_buckets, sizeof(int));
    
    /*  Aloca memória para cada balde */
    for(i = 0; i < num_buckets; i++) {
        buckets[i] = (int *)malloc(tam * sizeof(int));
    }

    for(i = 1; i < tam; i++) {
        if(vet[i] > max_val) max_val = vet[i];
    }
    
    /*  Distribui os elementos nos baldes apropriados */
    for(i = 0; i < tam; i++) {
        /*  Calcula em qual balde o elemento deve ficar */
        int bucket_idx = (vet[i] * num_buckets) / (max_val + 1);
        buckets[bucket_idx][bucket_sizes[bucket_idx]++] = vet[i];
    }
    
    /*  Ordena cada balde e concatena no vetor original */
    for(i = 0; i < num_buckets; i++) {
        if(bucket_sizes[i] > 0) {
            insertionSort(buckets[i], bucket_sizes[i]);  /* Ordena o balde  */
            
            /*  Copia os elementos ordenados de volta para o vetor principal */
            for(j = 0; j < bucket_sizes[i]; j++) {
                vet[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);  /* Libera memória do balde */ 
    }
    
    /* Libera memória das estruturas auxiliares */ 
    free(buckets);
    free(bucket_sizes);
}

/* Função principal:
   - Lê entrada do usuário
   - Chama o bucket sort
   - Imprime o resultado */
int main(int argc, char *argv[]) {
    int *vet;
    char linha[16];
    int tamVet;
    int i;
    
    /* Verifica argumentos de linha de comando */ 
    if(argc < 2) {
        printf("Uso: %s <numero de elementos a ordenar>\n", argv[0]);
        exit(0);
    }
    
    tamVet = atoi(argv[1]);  /*  Converte argumento para inteiro */
    vet = (int *)malloc(sizeof(int) * tamVet);  /*  Aloca vetor */
    
    /*  Lê os valores de entrada */
    for(i = 0; i < tamVet; i++) {
        fgets(linha, 16, stdin);
        sscanf(linha, "%d", &vet[i]);
    }
    
    bucketSort(vet, tamVet);  /*  Ordena o vetor */
    print(vet, tamVet);     /*  Imprime o resultado */
    free(vet);  /* Libera memória */
    exit(0);
}
