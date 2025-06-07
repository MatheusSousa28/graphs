#include <stdio.h>
#include <locale.h>//corrigir acentuacao
#include <string.h>//manipulacao de strings
#include <stdlib.h>//alocacao dinamica de memoria
#define BRANCO 1
#define CINZA 2
#define PRETO 3
typedef struct Vert{
    int data;
    struct Vert* next;
    struct Vert* dad;
    int d;
    int cor;
    struct Vert* fnext;
}Vert;
typedef struct Graph{
    int numVerts;
    Vert* *adjLists;
    Vert* *vertices;
}Graph;
Vert* createVert(int data);
Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
void BFS(Graph* graph, Vert* s);
void enfileirar(Vert* *Q, Vert* s);
Vert* desenfileirar(Vert* *Q);
void printTree(Graph* graph);
void printSubTree(Graph* graph, Vert* v, int nivel);
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    Graph* graph = createGraph(8);
    addEdge(graph, 0, 1);
    addEdge(graph, 0 , 4);
    addEdge(graph, 1, 5);
    addEdge(graph, 5 , 2);
    addEdge(graph, 5 , 6);
    addEdge(graph, 6 , 2);
    addEdge(graph, 6 , 3);
    addEdge(graph, 6 , 7);
    addEdge(graph, 7, 3);
    addEdge(graph, 2, 3);
    printGraph(graph);
    BFS(graph, graph->vertices[1]);
    printTree(graph);
    return 0;
}
Vert* createVert(int data){
    Vert* newVert = (Vert*)malloc(sizeof(Vert));
    newVert->data = data;
    newVert->next = NULL;
    newVert->dad = NULL;
    newVert->d = -1;
    newVert->cor = BRANCO;
    newVert->fnext = NULL;
    return newVert;
}
Graph* createGraph(int numVertices){
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVerts = numVertices;
    graph->adjLists = (Vert**)malloc(numVertices * sizeof(Vert*));
    graph->vertices = (Vert**)malloc(numVertices * sizeof(Vert*));
    for(int i = 0; i < numVertices; i++){
        graph->adjLists[i] = NULL;
        graph->vertices[i] = createVert(i);
    }
    return graph;
}
void addEdge(Graph* graph, int src, int dest){
    Vert* v1 = graph->vertices[src];
    Vert* v2 = graph->vertices[dest];

    Vert* new = createVert(v1->data);
    new->next = graph->adjLists[dest];
    graph->adjLists[dest] = new;

    new = createVert(v2->data);
    new->next = graph->adjLists[src];
    graph->adjLists[src] = new;
}
void printGraph(Graph* graph){
    for(int i = 0; i < graph->numVerts; i++){
        printf("[%d]",i);
        Vert* temp = graph->adjLists[i];
        while (temp){
            printf(" %d ->",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
void BFS(Graph* graph, Vert* s){
    for(int i = 0; i < graph->numVerts; i++){
        graph->vertices[i]->cor = BRANCO;
        graph->vertices[i]->d = -1;
        graph->vertices[i]->dad = NULL;
    }
    s->cor = CINZA;
    s->d = 0;
    s->dad = NULL;
    Vert* Q = NULL;
    enfileirar(&Q, s);
    while(Q != NULL){
        Vert* u = desenfileirar(&Q);
        Vert* adj = graph->adjLists[u->data];
        while(adj){
            Vert* v = graph->vertices[adj->data];
            if(v->cor == BRANCO){
                v->cor = CINZA;
                v->d = u->d + 1;
                v->dad = u;
                enfileirar(&Q, v);
            }
            adj = adj->next;
        }
        u->cor = PRETO;
    }
}
void enfileirar(Vert* *Q, Vert* s){
    if(*Q == NULL){
        *Q = s;
    }else{
        Vert* temp = *Q;
        while(temp->fnext != NULL)
            temp = temp->fnext;
        temp->fnext = s;
    }
}
Vert* desenfileirar(Vert* *Q){
    Vert* x = *Q;
    *Q = (*Q)->fnext;
    x->fnext = NULL;
    return x;
}
void printTree(Graph* graph) {
    for (int i = 0; i < graph->numVerts; i++) {
        Vert* v = graph->vertices[i];
        // Raiz de uma árvore (sem pai)
        if (v->dad == NULL && v->cor != BRANCO) {
            printf("\ninicio da arvore\n");
            printSubTree(graph, v, 0);
        }
    }
}
void printSubTree(Graph* graph, Vert* v, int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("    ");  // 4 espaços por nível
    }
    printf("%d\n", v->data);
    // Imprime os filhos de v
    for (int i = 0; i < graph->numVerts; i++) {
        Vert* filho = graph->vertices[i];
        if (filho->dad == v) {
            printSubTree(graph, filho, nivel + 1);
        }
    }
}