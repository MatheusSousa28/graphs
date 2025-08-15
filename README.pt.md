**Conteúdo Principal**  
Olá! este repositório contém a implementação de grafos direcionais e não direcionais em linguagem C, usando o método de lista de adjacências.

**O que são listas de adjacências ?**  
Um grafo é uma estrutura que representa relações entre objetos, no caso, vértices.
Esses vértices se conectam por “caminhos” (arestas) que ligam um ao outro.
A lista de adjacências armazena, para cada vértice, todos os vértices aos quais ele está conectado.
Isso nos permite implementar algoritmos de busca a partir do grafo e das relações entre os vértices.

**Vantagens e desvantagens da implementação por lista de adjacências**  
**Vantagens:**

- Uso de structs torna o código mais legível.

- Manutenção e compreensão mais fáceis.

- Implementação relativamente simples.

**Desvantagens:**

- Maior uso de memória comparado a matrizes de adjacência.

- Requer mais processamento em alguns casos.

*Alternativa:* Uma matriz de adjacência é mais leve e rápida em certos cenários, mas mais difícil de manter e implementar.

**Algoritmos de busca implementados**  
Os grafos podem utilizar diferentes algoritmos de busca para encontrar o caminho  mais curto entre dois vértices ou verificar alcance (quais vértices são acessiveis a partir de outro). Nesta implementação, o grafo direcional utiliza o algoritimo DFS (Depth-First Search), que consiste em ir o mais fundo possível em um caminho antes de voltar e explorar outros, ótimo para verificar conexões e detectar ciclos. Já o grafo não direcional utiliza o algoritmo BFS (Breadth-First Search) que funciona visitando todos os vizinhos de um vértice antes de aprofundar a busca, isso nos permite saber o caminho mais curto entre vértices. Os algoritmos DFS e BFS não são exclusivos de grafos direcionais ou não direcionais e funcionam em ambos os tipos, a escolha depende do objetivo da busca. 
