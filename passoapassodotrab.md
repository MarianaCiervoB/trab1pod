- **Entender o Bucket Sort Tradicional**
    1. Cria vários "baldes" (buckets)
    2. Distribui os números nos baldes de acordo com seu valor (números pequenos vão para baldes iniciais, grandes para finais)
    3. Ordena cada balde individualmente (geralmente com Insertion Sort)
    4. Junta todos os baldes ordenados para ter a lista completa ordenada
- **Criar Variações do Algoritmo**
    - Bucket Sort tradicional (com Insertion Sort nos baldes) - para comparação
    - Bucket Sort com Quick Sort para ordenar os baldes
    - Bucket Sort com Merge Sort
    - Bucket Sort com Heap Sort
- **Implementar em C**
    
    Escreva um programa em C que:
    
    - Gera arrays de números aleatórios (ou parcialmente ordenados)
    - Aplica as 4 versões do algoritmo
    - Mede o tempo que cada um leva para ordenar
- **Testar com Diferentes Tamanhos**
    - 100.000 números
    - 1.000.000 números
    - 100.000.000 números
- **Analisar o Resultado**
    - Qual versão foi mais rápida para cada tamanho?
    - Como o desempenho muda conforme o tamanho aumenta?
    - Por que alguns algoritmos funcionam melhor em certos casos?
- **Escrever Relatório**
    
    Explique os resultados das comparações, qual versão foi melhor e por quê
