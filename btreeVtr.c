#include <stdio.h>
#include <locale.h>//corrigir acentuacao
#include <string.h>//manipulacao de strings
#include <stdlib.h>//alocacao dinamica de memoria
int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int* *btree = NULL;
int tam = 0;
void destroy();
int valid(int last, int i);
int invalid(int last, int i);
int reallocation(int qnt, int opr);
int initialAllocation();
void generatetree(int first, int last, int i);
void printTree(int last,int i);
int minimum(int last, int i);
int maximum(int last, int i);
int search(int vlr, int last, int i);
int sucessor(int last, int i, int first);
int predecessor(int last, int i, int first);
void insert(int last, int vlr);
char buffer[50];
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    if(initialAllocation() == -1){
        printf("\nprograma finalizado");
        return -1;
    }
    generatetree(0,sizeof(arr)/sizeof(int) - 1,0);
    int resposta = -1;
    while(resposta != 0){
        printf("\n       MENU\n1 - exibir arvore\n2 - exibir valor minimo\n3 - exibir valor maximo\n4 - procurar valor\n5 - sucessor ou predecessor\n6 - inserir\n7 - remover\n0 - sair\n");
        fgets(buffer,50,stdin);
        resposta = atoi(buffer);
        memset(buffer,0,50);
        switch (resposta)
        {
            case 1:
            if(tam == 0){
                printf("\na arvore está vazia");
            }
                printTree(tam - 1,0);
            break;
            case 2:{
                if(tam == 0){
                    printf("\na arvore está vazia");
                }
                int minimo = minimum(tam - 1,0);
                printf("\nmenor valor da arvore: %d",*btree[minimo]);
            }
            break;
            case 3:{
                if(tam == 0){
                    printf("\na arvore está vazia");
                }
                int maximo = maximum(tam - 1,0);
                printf("\nmaior valor da arvore: %d",*btree[maximo]);
            }
            break;
            case 4:{
                int vlr = 0;
                printf("\ndigite o valor que voce quer pesquisar na arvore: ");
                fgets(buffer,50,stdin);
                vlr = atoi(buffer);
                memset(buffer,0,50);
                vlr = search(vlr,tam - 1,0);
                if(vlr == -1){
                    printf("esse valor não existe na arvore");
                }else{
                    printf("%d",*btree[vlr]);
                }
            }
            break;
            case 5:{
                int vlr = 0;
                printf("\nvoce quer achar o sucessor ou antecessor de qual valor ?\n");
                fgets(buffer,50,stdin);
                vlr = atoi(buffer);
                memset(buffer,0,50);
                vlr = search(vlr,tam - 1,0);
                if(vlr == -1){
                    printf("esse valor não existe na arvore");
                }else{
                    int escolha = 0;
                    printf("escolha:\n1 - sucessor\n2 - predecessor\n");
                    fgets(buffer,50,stdin);
                    escolha = atoi(buffer);
                    memset(buffer,0,50);
                    if(escolha == 1){
                        int maximo = maximum(tam - 1,0);
                        if(vlr == maximo){
                            printf("esse valor não tem sucessor, pois é o maior valor da arvore");
                        }else{
                            int suce = sucessor(tam - 1,vlr,0);
                            printf("o sucessor é: %d",*btree[suce]);
                        }
                    }else if(escolha == 2){
                        int minimo = minimum(tam - 1,0);
                        if(vlr == minimo){
                            printf("esse valor não tem predecessor, pois é o menor valor da arvore");
                        }else{
                            int prede = predecessor(tam - 1,vlr,0);
                            printf("o predecessor é: %d",*btree[prede]);
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
                if(vlr == -1){
                    printf("\nvalor inválido");
                }else{
                    insert(tam - 1,vlr);
                }
            }
            break;
            case 7:{
                int vlr = 0;
                printf("\ndigite o valor que voce quer remover da arvore: ");
                fgets(buffer,50,stdin);
                vlr = atoi(buffer);
                memset(buffer,0,50);
                vlr = search(vlr,tam - 1,0);
                if(vlr == -1){
                    printf("esse valor não existe na arvore");
                }else{
                    delete(tam-1,vlr);
                    printf("\nvalor deletado com sucesso");
                    int invalids = 0;
                    for(int i = tam-1; i >= 0 && *btree[i] == -1; i--){
                        invalids++;
                    }
                    if(invalids > 0){
                        if(reallocation(tam-invalids,0) != -1){
                            tam = tam - invalids;
                        }
                    }
                }
            }
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
int valid(int last, int i){
    return (i <= last && *btree[i] != -1);
}
int invalid(int last, int i){
    return (i > last || *btree[i] == -1);
}
int initialAllocation(){
    int n = sizeof(arr)/sizeof(int);
    btree = (int**)malloc(n * sizeof(int*));
    if(btree == NULL){
        printf("\nerro de alocação de memória");
        return -1;
    }
    for(int i = 0;i < n; i++){
        btree[i] = (int*)malloc(sizeof(int));
        if(btree[i] == NULL){
            printf("\nerro de alocação de memória");
            return -1;
        }
        tam++;
    }
    return 0;
}
void generatetree(int first, int last, int i){
    if(first > last){
        return;
    }
    int mid = (first + last) / 2;
    *btree[i] = arr[mid];
    generatetree(first,mid - 1,2*i + 1);
    generatetree(mid + 1,last,2*i + 2);
}
void printTree(int last, int i){
    if(i >  last){
        return;
    }
    if(*btree[i] != -1){
        printTree(last,2*i + 1);
        printf("%d ",*btree[i]);
        printTree(last,2*i + 2);
    }
}
int minimum(int last,int i){
    while(valid(last,2*i+1)){
        i = 2*i + 1;
    }
    return i;
}
int maximum(int last,int i){
    while(valid(last,2*i+2)){
        i = 2*i + 2;
    }
    return i;
}
int search(int vlr, int last, int i){
    if(invalid(last,i)){
        return -1;
    }
    if(vlr < *btree[i]){
        return search(vlr,last,2*i + 1);
    }else if(vlr > *btree[i]){
        return search(vlr, last, 2*i + 2);
    }else{
        return i;
    }
}
int sucessor(int last, int i, int first){
    if(valid(last,2*i + 2))
        return minimum(last,2*i + 2);
    int y = (i - 1) / 2;
    while(y > first && i == 2*y + 2){
        i = y;
        y = (y - 1) / 2;
    }
    return y;
}
int predecessor(int last, int i, int first){
    if(valid(last,2*i + 1))
        return maximum(last,2*i + 1);
    int y = (i - 1) / 2;
    while(y > first && i == 2*y + 1){
        i = y;
        y = (y - 1) / 2;
    }
    return y;
}
void insert(int last,int vlr){
    if(last == -1){
        *btree[0] = vlr;
        return;
    }
    int y = -1;
    int x = 0;
    while(valid(last,x)){
        y = x;
        if(vlr < *btree[x])
            x = 2*x + 1;
        else
            x = 2*x + 2;
    }
    if(vlr < *btree[y]){
        if(2*y + 1 <= last){
            *btree[2*y + 1] = vlr;
            printf("\nvalor inserido com sucesso");
        }else{
            if(reallocation((2*y + 1),1) != -1){
                *btree[2*y + 1] = vlr;
                printf("\nvalor inserido com sucesso");
            }
        }
    }else{
        if(2*y + 2 <= last){
            *btree[2*y + 2] = vlr;
            printf("\nvalor inserido com sucesso");
        }else{
            if(reallocation((2*y + 2),1) != -1){
                *btree[2*y + 2] = vlr;
                printf("\nvalor inserido com sucesso");
            }
        }
    }
}
int reallocation(int qnt, int opr){
    if(opr == 1){
        btree = (int**)realloc(btree,(qnt + 1) * sizeof(int*));
        if(btree == NULL){
            printf("\nerro. não foi possivel alocar memória");
            return -1;
        }
        for(int i = tam; i <= qnt; i++){
            btree[i] = (int*)malloc(sizeof(int));
            if(btree[i] == NULL){
                printf("erro ao alocar memória");
                reallocation(0,2);
                return -1;
            }
            *btree[i] = -1;
            tam++;
        }
    }else{
        btree = (int**)realloc(btree,tam * sizeof(int*));
        if(btree == NULL){
            printf("\nerro ao realocar memória");
            return -1;
        }
    }
    return 0;
}
void delete(int last, int i){
    if(invalid(last,2*i+1)){
        if(invalid(last,2*i+2)){
            *btree[i] = -1;
        }else{
            *btree[i] = *btree[2*i + 2];
            delete(last,2*i+2);
        }
    }else if(invalid(last,2*i + 2)){
        *btree[i] = *btree[2*i+1];
        delete(last,2*i+1);
    }else{
        int suce =  minimum(last,2*i+2);
        *btree[i] = *btree[suce];
        delete(last,suce);
    }
}
void destroy(){
    for(int i = 0; i < tam;i++){
        free(btree[i]);
    }
    free(btree);
}