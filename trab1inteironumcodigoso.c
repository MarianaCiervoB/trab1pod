
#include <stdio.h>
#include <stdlib.h>

/* Função que imprime um vetor de inteiros separados por vírgula, exceto o último elemento que é seguido por quebra de linha */
static void print(int *vetor, int tam) {
    int cont;
    for(cont = 0; cont < tam; cont++) {
        if(cont == tam-1) printf("%d\n", vetor[cont]);  /* Último elemento */ 
        else printf("%d, ", vetor[cont]);            /* Demais elementos */ 
    }
    return;
}

/*
* Função que gera N números inteiros positivos aleatórios.
* N deve ser dado pelo usuário na linha de comando.  
* Se houver um terceiro parâmetro de linha de comando, ele será o limite superior para os valores gerados. 
*/
int geraN(int argc, char *argv[]){
  unsigned int i, val, N;
  int *vet; 
  if(argc == 2){
    N = val = atoi(argv[1]);
  } else {
    if(argc == 3){
      N = atoi(argv[1]);
      val = atoi(argv[2]);
    } else {
      printf("Uso: geraN <numero de valores a serem gerados> <limite superior para os valores>\n");
      exit(0);
    }
  }
  vet = (int *) malloc(sizeof(int) * N);

  val++;
  for(i=0; i<N; i++){
    vet[i] = (unsigned int) rand()%val; /**/
    printf("%u\n", vet[i]);
  }
  print(vet, N);
  return vet;
}

/* Função que utiliza versão modificada de gaps no Shell sort para ordenar parcialmente dados da entrada.*/
int *parcOrd(int *vet, int tam){
  int i, j, k=0, temp;
  int gaps[8]={701,301,132,57,23,10,4,2}; /* quanto menor o gap final, mais próximos os valores de sua posição final */
  while (gaps[k] > ((tam/2)-1))
	k++;
  while( gaps[k] >= 1 ){
    for(i = gaps[k]; i<tam; i++){
	temp = vet[i];
        j = i - gaps[k];
	while( j >= 0 && temp < vet[j]){
		vet[j+gaps[k]] = vet[j];
		j -= gaps[k];
	}
	vet[j+gaps[k]] = temp;
    }
    k++;
  }
  return vet;
}

int parcOrdAsc(int argc, char *argv[]){
  int  i;
  int *vet = geraN(argc, *argv);
  char linha[16];
  int tamVet;
  int maior = -1;

  if(argc < 2){
    printf("Uso: %s <numero de elementos a ordenar parcialmente>\n", argv[0]);
    exit(0);
  }
  tamVet = atoi(argv[1]);

  for(i=0; i<tamVet; i++){
	fgets(linha, 16, stdin);
	sscanf(linha, "%d", &vet[i]);
	if(vet[i] > maior)
		maior = vet[i];
  }

  parcOrd(vet, tamVet);
  print(vet, tamVet);
  return vet;
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
    print(vet, tam);
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
    int opcao;
    
    /* Verifica argumentos de linha de comando */ 
    if(argc < 2) {
        printf("Uso: %s <numero de elementos a ordenar>\n", argv[0]);
        exit(0);
    }
    
    tamVet = atoi(argv[1]);  /*  Converte argumento para inteiro */
    vet = (int *)malloc(sizeof(int) * tamVet);  /*  Aloca vetor */

    printf("Escolha uma opção:\n");
    printf("1 - Ordenar valores não ordenados\n");
    printf("2 - Ordenar valores parcialmente ordenados\n");
    printf("Opção: ");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &opcao);
    
    printf("Quantidade de valores: ");
    fgets(linha, sizeof(linha), stdin);
    sscanf(linha, "%d", &tamVet);
    
    if (opcao == 1) {
        /* Gera números aleatórios e lê a saída */
        vet = geraN (vet, tamVet);
    } 
    else if (opcao == 2) {
        /* Gera números, ordena parcialmente e lê a saída */
        vet = parcOrdAsc (vet, tamVet);
    } else {
        printf("Opção inválida!\n");
        free(vet);
        return 1;
    }
    
    /* Aplica Bucket Sort e imprime o resultado */
    printf("\nValores antes do Bucket Sort:\n");
    print(vet, tamVet);
    
    bucketSort(vet, tamVet);
    
    printf("\nValores após Bucket Sort:\n");
    print(vet, tamVet);
    
    free(vet);
    return 0;
}
