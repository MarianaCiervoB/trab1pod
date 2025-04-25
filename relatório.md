📄 Relatório Técnico - Análise e Implementação de Algoritmos de Ordenação
✨ Introdução
Neste projeto, foi desenvolvido um comparativo entre quatro algoritmos de ordenação: QuickSort, MergeSort, HeapSort e uma versão otimizada de BucketSort. Os testes foram feitos com arrays contendo 10 milhões de elementos, tanto com dados aleatórios quanto parcialmente ordenados.

🪣 Bucket Sort Otimizado
🧠 Lógica e Estrutura
O BucketSort funciona distribuindo os elementos em “baldes” (buckets), e depois ordenando cada bucket individualmente. A última etapa é juntar todos os buckets em um único array ordenado.

📏 Escolha do Tamanho dos Buckets
A quantidade de buckets foi definida como a raiz quadrada do tamanho do array:

c
Copiar
Editar
N_BUCKETS = (int)sqrt(n);
Essa escolha é uma heurística comum porque equilibra bem o número de buckets e a quantidade de elementos por bucket. Evita tanto:

buckets lotados demais (ficam lentos),

quanto muitos buckets vazios (ineficiente e gasta memória à toa).

Para evitar exageros, foi colocado um limite superior com MAX_BUCKETS = 10000.

🧹 Ordenação Interna dos Buckets
Dentro de cada bucket foi usado Insertion Sort. Por quê?

Insertion é bem rápido pra conjuntos pequenos e quase ordenados.

Como os buckets têm poucos elementos, o overhead do Quick ou Merge não compensa.

⚙️ Algoritmos de Ordenação Utilizados

Algoritmo	Características Principais
QuickSort	Muito rápido, mas sensível à ordem dos dados. Divide e conquista.
MergeSort	Estável, eficiente e com desempenho previsível. Divide e conquista com uso de memória auxiliar.
InsertionSort	Simples e rápido para pequenos vetores. Usado só nos buckets e em pequenos merges.
HeapSort	Uso constante de memória e bom desempenho no pior caso, mas não tão rápido quanto os outros.
⏱️ Desempenho Observado
🔀 Com dados aleatórios (10 milhões):

Algoritmo	Tempo (segundos)
QuickSort	1.34s
MergeSort	1.27s
InsertionSort	15.38s 🐢
HeapSort	3.43s
📈 Com dados parcialmente ordenados:

Algoritmo	Tempo (segundos)
QuickSort	0.62s
MergeSort	0.48s
InsertionSort	0.27s ⚡
HeapSort	2.06s
🧪 Análise e Comparação
QuickSort se dá muito bem com dados aleatórios, mas tem desempenho instável se a entrada já estiver ordenada ou com muitos elementos iguais.

MergeSort foi o mais consistente: rápido tanto com dados bagunçados quanto organizados.

InsertionSort, sozinho, só presta com dados quase ordenados. Foi muito lento com vetores aleatórios.

HeapSort fica no meio do caminho: confiável, mas com tempo maior do que Merge e Quick.

O BucketSort brilha quando os dados estão razoavelmente uniformes e a distribuição permite buckets balanceados.

✅ Conclusão
A estratégia usada de aplicar BucketSort com InsertionSort dentro se mostrou vantajosa pela simplicidade e boa performance com dados bem distribuídos. O uso de sqrt(n) como número de buckets foi acertado pra balancear tempo e memória. Já o uso de Insertion para os buckets pequenos deu aquele boost de desempenho em casos com dados parcialmente ordenados.

![image](https://github.com/user-attachments/assets/46e6bf7a-3da3-4d82-8139-e2edb19fd313)

Com dados aleatórios, o MergeSort e o QuickSort mandaram bem, enquanto o InsertionSort ficou pra trás (muito lento).

Já com dados parcialmente ordenados, o InsertionSort surpreende e dá show — isso porque ele se aproveita bem da ordenação parcial, enquanto o HeapSort continua mais pesadão.

Pra conjuntos grandes e diversos, MergeSort leva a melhor geral. Mas, se o padrão dos dados ajudar, BucketSort pode ser o rei da performance. 👑
