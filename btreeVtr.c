#include <stdio.h>
#include <locale.h>//corrigir acentuacao
#include <string.h>//manipulacao de strings
#include <stdlib.h>//alocacao dinamica de memoria
int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int **btree = NULL;
int tam = sizeof(arr)/sizeof(int);
void destroy();
void deleteNode();
int reallocation(int newTam, int opc);
void insert(int vlr,int last);
int predecessor(int i, int first);
int sucessor(int i, int first);
int search(int vlr, int i);
int maximum(int i);
int minimum(int i);
void printTree(int i);
void generateTree(int first, int last, int i);
int invalid(int last, int i);
int valid(int last, int i);
int initialAllocation();
char buffer[30];
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    if(initialAllocation() == -1){
        return 1;
    }
    generateTree(0,tam - 1, 0);
    int resposta = -1;
    while(resposta != 0){
        printf("\n");
        for (int i = 0; i < tam; i++)
        {
            printf("%d ",*btree[i]);
        }
        
        printf("\n       MENU\n1 - exibir arvore\n2 - exibir valor minimo\n3 - exibir valor maximo\n4 - procurar valor\n5 - sucessor ou predecessor\n6 - inserir\n7 - remover\n8 - tam\n0 - sair\n");
        fgets(buffer,50,stdin);
        resposta = atoi(buffer);
        memset(buffer,0,50);
        switch (resposta)
        {
            case 1:{
                if(tam == 1){
                    printf("\na arvore está vazia");
                    break;
                }
                printTree(0);
            }
            break;
            case 2:{
                if(tam == 1){
                    printf("\na arvore está vazia");
                    break;
                }
                int min = minimum(0);
                printf("\nmenor valor da arvore: %d",*btree[min]);
            }
            break;
            case 3:{
                if(tam == 1){
                    printf("\na arvore está vazia");
                    break;
                }
                int max = maximum(0);
                printf("\nmaior valor da arvore: %d",*btree[max]);
            }
            break;
            case 4:{
                int vlr = 0;
                printf("\nqual valor voce quer pesquisar na arvore: ");
                fgets(buffer,30,stdin);
                vlr = atoi(buffer);
                memset(buffer,0,30);
                int i = search(vlr, 0);
                if(i == -1){
                    printf("\nesse valor não existe na arvore");
                }else{
                    printf("\nvalor encontrado: %d", *btree[i]);
                }
            }
            break;
            case 5:{
                int vlr = 0;
                printf("\nvoce quer achar o sucessor ou predecessor de qual valor da arvore: ");
                fgets(buffer,30,stdin);
                vlr = atoi(buffer);
                memset(buffer,0,30);
                int i = search(vlr, 0);
                if(i == -1){
                    printf("\nesse valor não existe na arvore");
                }else{
                    int opcao = 0;
                    printf("\nescolha\n 1 - sucessor\n2 - predecessor\n");
                    fgets(buffer,30,stdin);
                    opcao = atoi(buffer);
                    memset(buffer,0,30);
                    if(opcao == 1){
                        if(i == maximum(0)){
                            printf("\nesse valor não tem sucessor, pois é o maior da arvore");
                        }else{
                            int suce = sucessor(i,0);
                            printf("\no sucessor é: %d",*btree[suce]);
                        }
                    }else if(opcao == 2){
                        if(i == minimum(0)){
                            printf("\nesse valor não tem predecessor, pois é o menor da arvore");
                        }else{
                            int prede = predecessor(i,0);
                            printf("\no predecessor é: %d",*btree[prede]);
                        }
                    }else{
                        printf("\nresposta inválida");
                    }
                }
            }
            break;
            case 6:{
                int vlr = 0;
                printf("\nqual valor voce quer inserir na arvore: ");
                fgets(buffer,30,stdin);
                vlr = atoi(buffer);
                memset(buffer,0,30);
                if(vlr != -1){
                    insert(vlr, tam - 1);
                    printf("\nvalor inserido com sucesso");
                }else{
                    printf("\nvalor inválido");
                }
            }
            break;
            case 7:{
                int vlr = 0;
                printf("\nqual valor voce quer deletar da arvore: ");
                fgets(buffer,30,stdin);
                vlr = atoi(buffer);
                memset(buffer,0,30);
                int i = search(vlr, 0);
                if(i == -1){
                    printf("\nesse valor não existe na arvore");
                }else{
                    deleteNode(i);
                    printf("\nvalor deletado com  sucesso");
                    int invalids = 0;
                    for (int i = tam - 1; i > 0; i--)
                    {
                        if(*btree[i] == -1){
                            invalids++;
                        }else{
                            break;
                        }
                    }
                    if(invalids > 0){
                        if(reallocation(tam - invalids, 0) != -1){
                            tam = tam - invalids;
                        }
                    }
                }
            }
            break;
            case 8:
            printf("%d",tam);
            break;
            case 0:
                printf("\nprograma finalizado");
                destroy();
            break;
            default:
                printf("\nresposta inválida");
            break;
        }
    }
}
int initialAllocation(){
    btree = (int**)malloc(tam * sizeof(int*));
    if(btree){
        for(int i = 0; i < tam; i++){
            btree[i] = (int*)malloc(sizeof(int));
            if(btree[i] == NULL){
                printf("\nerro ao alocar memória");
                return -1;
            }
        }
    }else{
        printf("\nerro ao alocar memória");
        return -1;
    }
    return 0;
}
int valid(int last, int i){
    return (i <= last && *btree[i] != -1);
}
int invalid(int last, int i){
    return (i > last || *btree[i] == -1);
}
void generateTree(int first, int last, int i){
    if(first > last){
        return;
    }
    int mid = (first + last) / 2;
    *btree[i] = arr[mid];
    generateTree(first, mid - 1, 2*i + 1);
    generateTree(mid + 1, last, 2*i + 2);
}
void printTree(int i){
    if(invalid(tam - 1,i)){
        return;
    }
    printTree(2*i + 1);
    printf("%d ",*btree[i]);
    printTree(2*i + 2);
}
int minimum(int i){
    while(valid(tam - 1, 2*i + 1)){
        i = 2*i + 1;
    }
    return i;
}
int maximum(int i){
    while(valid(tam - 1, 2*i + 2)){
        i = 2*i + 2;
    }
    return i;
}
int search(int vlr, int i){
    if(invalid(tam - 1, i)){
        return -1;
    }
    if(vlr < *btree[i]){
        return search(vlr, 2*i + 1);
    }else if(vlr > *btree[i]){
        return search(vlr, 2*i + 2);
    }else{
        return i;
    }
}
int sucessor(int i, int first){
    if(valid(tam - 1, 2*i + 2)){
        return minimum(2*i + 2);
    }
    int y = (i - 1) / 2;
    while(y >= first && 2*y + 2 == i){
        i = y;
        y = (y - 1) / 2;
    }
    return y;
}
int predecessor(int i, int first){
    if(valid(tam - 1, 2*i + 1)){
        return maximum(2*i + 1);
    }
    int y = (i - 1) / 2;
    while(y >= first && 2*y + 1 == i){
        i = y;
        y = (y - 1) / 2;
    }
    return y;
}
void insert(int vlr,int last){
    if(tam == 1){
        if(reallocation(2, 1) != -1){
            *btree[0] = vlr;
        }
        return;    
    }
    int y = -1;
    int x = 0;
    while(valid(tam - 1, x)){
        y = x;
        if(vlr < *btree[x]){
            x = 2*x + 1;
        }else{
            x = 2*x + 2;
        }
    }
    if(vlr < *btree[y]){
        if(2*y + 1 <= last){
            *btree[2*y + 1] =  vlr;
        }else{
            if(reallocation((2*y + 1) + 1,1) != -1){
                *btree[2*y + 1] =  vlr;
            }else{
                printf("\nnão foi possivel inserir");
            }
        }
    }else{
        if(2*y + 2 <= last){
            *btree[2*y + 2] =  vlr;
        }else{
            if(reallocation((2*y + 2) + 1,1) != -1){
                *btree[2*y + 2] =  vlr;
            }else{
                printf("\nnão foi possivel inserir");
            }
        }
    }
}
int reallocation(int newTam, int opc){
    if(opc == 1){
        btree = realloc(btree,newTam * sizeof(int*));
        if(btree){
            for(int i = tam; i < newTam; i++){
                btree[i] = malloc(sizeof(int));
                if(btree[i]){
                    *btree[i] = -1;
                    tam++;
                }else{
                    reallocation(newTam - tam,0);
                    return -1;
                }
            }
        }else{
            return -1;
        }
    }else{
        btree = realloc(btree,newTam * sizeof(int*));
    }
    return 0;
}
void deleteNode(int i){
    if(invalid(tam - 1, 2*i + 1)){
        if(invalid(tam - 1, 2*i + 2)){
            *btree[i] = -1;
        }else{
            *btree[i] = *btree[2*i + 2];
            deleteNode(2*i + 2);
        }
    }else if(invalid(tam - 1, 2*i + 2)){
        *btree[i] = *btree[2*i + 1];
        deleteNode(2*i + 1); 
    }else{
        int suce = minimum(2*i + 2);
        *btree[i] = *btree[suce];
        deleteNode(suce);
    }
}
void destroy(){
    for (int i = 0; i < tam; i++)
    {
        free(btree[i]);
    }
    free(btree);
}