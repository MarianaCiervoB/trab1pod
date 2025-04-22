Função principal (main)
Pergunta pro usuário se quer um array aleatório ou parcialmente ordenado;

Lê o tamanho do array;

Cria 5 cópias do array (pra testar cada algoritmo com a mesma entrada);

Executa e mede o tempo de execução de cada algoritmo de ordenação;

Mostra os tempos no final.

🧩 Funções auxiliares
generateRandomArray
Gera um array com valores aleatórios entre 0 e max_value.

generatePartiallySortedArray
Cria um array aleatório e depois aplica uma ordenação parcial, pra simular dados "meio bagunçados".

partialSort
Ordena parcialmente o array usando uma técnica parecida com o Shell Sort, mas só até certo ponto (usando alguns gaps específicos).

swap
Troca dois valores de lugar — usada em vários algoritmos.

🔄 Algoritmos de ordenação
bubbleSort
Clássico e lerdinho: compara elementos vizinhos e troca se tiver fora de ordem. Vai repetindo até tudo ficar certo.

insertionSort
Usado no BucketSort. Insere cada elemento na posição correta comparando com os anteriores — tipo organizar cartas na mão.

quickSort
Implementado de forma iterativa com pilha (sem recursão). Escolhe um pivô, separa os menores à esquerda e os maiores à direita, e repete o processo.

heapSort
Transforma o array em um heap máximo e vai tirando o maior elemento (raiz) e jogando pro final do array.

Usa a função heapify pra manter a estrutura de heap.

bucketSort
Divide os elementos em baldes (buckets) com base no valor, ordena cada bucket com insertionSort e junta tudo no final.

💡 Resumo da ideia geral:
Gera um array (aleatório ou parcialmente ordenado);

Copia ele várias vezes pra manter o teste justo;

Aplica cada algoritmo de ordenação;

Cronometra e mostra quanto tempo cada um levou;




Relatório: Comparação de Diferentes Algoritmos de Ordenação com Diferentes Tipos de Arrays

Buscando avaliar o desempenho de diferentes algoritmos de ordenação em arrays de inteiros com tamanhos variáveis, consideramos dois cenários:

Array totalmente aleatório

Array parcialmente ordenado

Os algoritmos implementados e comparados foram:

- BubbleSort

- QuickSort

- HeapSort

- BucketSort Tradicional (com ordenação interna usando InsertionSort)

Detalhes dos Algoritmos
* BubbleSort
Funcionamento: compara elementos vizinhos e os troca se estiverem fora de ordem.

Complexidade: O(n²) no pior e médio caso.

Observações: Simples e extremamente ineficiente para arrays grandes.

* QuickSort (iterativo)
Funcionamento: divide o array em duas partições usando um pivô, recursivamente (aqui, feito com pilha).

Complexidade: O(n log n) no caso médio; O(n²) no pior (se for uma má escolha de pivô).

Observações: Muito rápido na média; algoritmo muito bom de uso geral.

* HeapSort
Funcionamento: transforma o array em um heap máximo e vai removendo o maior elemento.

Complexidade: O(n log n) sempre.

Observações: Desempenho estável, mas com mais overhead que o QuickSort.

* BucketSort
Funcionamento: Divide os elementos em "baldes" com base em um intervalo (range). Ordena cada balde individualmente com outro algoritmo e depois concatena todos os baldes no array final.

Escolha do Tamanho do Bucket(range):
Fórmula usada: bucket_range = (max_value + 1) / bucket_count + 1

bucket_count foi fixado em 10, por ser um número que divide bem os valores aleatórios sem criar buckets sobrecarregados ou vazios demais. Valores pequenos criariam buckets grandes e tornariam a ordenação interna mais lenta; valores altos criariam overhead com muitos buckets vazios.

* Algoritmo de ordenação usado nos buckets: InsertionSort

InsertionSort é muito eficiente em subarrays pequenos ou quase ordenados (o que é geralmente o caso dentro dos buckets);

Tem baixa complexidade de implementação e memória.

 Comparação entre os algoritmos

Algoritmo	Caso ideal	Caso ruim	Complexidade média	Observações principais
BubbleSort	Pequenos arrays quase ordenados	Arrays grandes ou totalmente bagunçados	O(n²)	Muito ineficiente em geral
QuickSort	Arrays grandes aleatórios	Dados já ordenados ou todos iguais	O(n log n)	Rápido, mas pode cair em O(n²)
HeapSort	Dados grandes e aleatórios	-	O(n log n)	Estável, mas levemente mais lento que o QuickSort
BucketSort	Dados uniformemente distribuídos	Dados concentrados em poucos valores	O(n + k)	Ótimo para inteiros com distribuição uniforme
💬 Conclusões
QuickSort geralmente é o mais rápido nos testes realizados, especialmente com arrays totalmente aleatórios;

HeapSort tem desempenho mais estável, sem cair em piores casos como o QuickSort pode sofrer;

BubbleSort só serve como referência didática; seu desempenho é inaceitável para arrays grandes;

BucketSort, com InsertionSort nos baldes, se sai muito bem quando os dados são bem distribuídos, mas pode perder eficiência se os dados se acumulam em poucos buckets;

Partially Sorted Arrays: algoritmos como InsertionSort e até BubbleSort têm performance relativamente melhor, mas ainda assim são superados por QuickSort e HeapSort.
