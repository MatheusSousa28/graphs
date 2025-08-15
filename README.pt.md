**Conteúdo Principal**  
Olá! este repositório contém a implementação de grafos direcionais e não direcionais em linguagem C, usando o método de lista de adjacências.

**O que são listas de adjacências ?**  
Bom, um grafo nada mais é do que uma estrutura que representa relações entre objetos, no caso, vértices. Esses vértices se relacionam com outros vértices, podemos imaginar isso 
como um "caminho" de um vértice ao outro. Uma lista de adjacências armazena todas as relações que um determinado vértice possui, possibilitando-nos implementar algoritimos de busca a 
partir do grafo e as relações entre os vértices.

**Vantagens e desvantagens da implementação por lista de adjacências**  

A implementação de grafos por listas de adjacências faz uso de structs, o que torna o código mais fácil de ler, melhora sua manutenibilidade e é claro, torna mais simples a sua implementação. Porém, 
structs requerem mais espaço de armazenamento, além de mais poder de processamento para execução do código. É importante notar que existem implementações de grafos que utilizam 
matrizes em vez de structs, isso faz com que esse tipo de implementação seja mais leve e não demande tanto poder de processamento, mas sua implementação e manutenibilidade é difícil.  

**Algoritmos de busca em grafos**  
