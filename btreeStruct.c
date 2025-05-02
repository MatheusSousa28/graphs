#include <stdio.h>
#include <locale.h>//corrigir acentuacao
#include <string.h>//manipulacao de strings
#include <stdlib.h>//alocacao dinamica de memoria
int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
typedef struct Node{
    int vlr;
    struct Node* dad;
    struct Node* left;
    struct Node* right;
}Node;
char buffer[30];
void destroy(Node* root);
void transplant(Node* *root, Node* u, Node* v);
void delete(Node* *root, Node* z);
Node* predecessor(Node* n);
Node* sucessor(Node* n);
void generatetree(Node* *n, int first, int last, Node* dad);
void printTree(Node* root);
Node* minimum(Node* root);
Node* maximum(Node* root);
Node* search(int vlr, Node* root);
void insert(Node* *root, Node* new);
Node* getdata();
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    Node* root = NULL;
    generatetree(&root,0,sizeof(arr)/sizeof(int) - 1,NULL);
    int resposta = -1;
    while(resposta != 0){
        printf("\n       MENU\n1 - exibir arvore\n2 - exibir valor minimo\n3 - exibir valor maximo\n4 - procurar valor\n5 - sucessor ou predecessor\n6 - inserir\n7 - remover\n0 - sair\n");
        fgets(buffer,30,stdin);
        resposta = atoi(buffer);
        memset(buffer,0,30);
        switch (resposta)
        {
        case 1:
            if(root == NULL){
                printf("\na arvore está vazia");
                break;
            }
            printTree(root);
            break;
        case 2:{
            if(root == NULL){
                printf("\na arvore está vazia");
                break;
            }
            Node* n = minimum(root);
            printf("\nmenor valor da arvore: %d",n->vlr);
        }
            break;
        case 3:{
            if(root == NULL){
                printf("\na arvore está vazia");
                break;
            }
            Node* n = maximum(root);
            printf("\nmaior valor da arvore: %d",n->vlr);
        }
            break;
        case 4:{
            int vlr = 0;
            printf("\ndigite o valor que voce quer pesquisar na arvore: ");
            fgets(buffer,30,stdin);
            vlr = atoi(buffer);
            memset(buffer,0,30);
            Node* n = search(vlr,root);
            if(n == NULL){
                printf("esse valor não existe na arvore");
            }else{
                printf("%d",n->vlr);
            }
        }
        break;
        case 5:{
            int vlr = 0;
            printf("\nvoce quer achar o sucessor ou predecessor de qual valor: ");
            fgets(buffer,30,stdin);
            vlr = atoi(buffer);
            memset(buffer,0,30);
            Node* n = search(vlr,root);
            if(n == NULL){
                printf("esse valor não existe na arvore");
            }else{
                printf("escolha:\n1 - sucessor\n2 - predecessor\n");
                fgets(buffer,50,stdin);
                vlr = atoi(buffer);//reaproveitamento de variavel
                memset(buffer,0,50);
                if(vlr == 1){
                    Node* suce = sucessor(n);
                    if(suce){
                        printf("\no sucessor é: %d",suce->vlr);
                    }else{
                        printf("\nesse valor não tem sucessor na arvore");
                    }
                }else if(vlr == 2){
                    Node* prede = predecessor(n);
                    if(prede){
                        printf("\no predecessor é: %d",prede->vlr);
                    }else{
                        printf("\nesse valor não tem predecessor na arvore");
                    }
                }else{
                    printf("\nresposta inválida");
                }
            }
        }
        break;
        case 6:{
            Node* new = getdata();
            if(new){
                insert(&root,new);
                printf("\nvalor inserido na arvore com sucesso");
            }
        }
        break;
        case 7:{
            int vlr = 0;
            printf("\nvoce quer remover qual valor da arvore: ");
            fgets(buffer,30,stdin);
            vlr = atoi(buffer);
            memset(buffer,0,30);
            Node* n = search(vlr,root);
            if(n == NULL){
                printf("\nesse valor não existe na arvore");
            }else{
                delete(&root,n);
                printf("\nvalor removido com sucesso");
            }
        }
        break;
        case 0:
            printf("programa finalizado");
            destroy(root);
        break;
        default:
            printf("\nresposta inválida");
            break;
        }
    }
}
void generatetree(Node* *n, int first, int last, Node* dad){
    if(first > last){
        return;
    }
    int mid = (first + last) / 2;
    *n = malloc(sizeof(**n));
    (*n)->vlr = arr[mid];
    (*n)->dad = dad;
    (*n)->left = NULL;          
    (*n)->right = NULL;
    generatetree(&(*n)->left,first,mid - 1,(*n));
    generatetree(&(*n)->right,mid + 1,last,(*n));
}
void printTree(Node* root){
    if(root == NULL){
        return;
    }
    printTree(root->left);
    printf("%d ",root->vlr);
    printTree(root->right);
}
Node* minimum(Node* root){
    while(root->left){
        root = root->left;
    }
    return root;
}
Node* maximum(Node* root){
    while(root->right){
        root = root->right;
    }
    return root;
}
Node* search(int vlr, Node* root){
    if(root == NULL || vlr == root->vlr){
        return root;
    }
    if(vlr < root->vlr){
        return search(vlr,root->left);
    }else{
        return search(vlr, root->right);
    }
}
Node* sucessor(Node* n){
    if(n->right){
        return minimum(n->right);
    }else{
        Node* y = n->dad;
        while(y != NULL && n == y->right){
            n = y;
            y = y->dad;
        }
        return y;
    }
}
Node* predecessor(Node* n){
    if(n->left){
        return maximum(n->left);
    }else{
        Node* y = n->dad;
        while(y != NULL && n == y->left){
            n = y;
            y = y->dad;
        }
        return y;
    }
}
void insert(Node* *root, Node* new){
    if(*root == NULL){
        *root = new;
        return;
    }
    Node* y = NULL;
    Node* x = *root;
    while(x != NULL){
        y = x;
        if(new->vlr < x->vlr)
            x = x->left;
        else
            x = x->right;
    }
    new->dad = y;
    if(new->vlr < y->vlr)
        y->left = new;
    else
        y->right = new;
}
Node* getdata(){
    Node* new = (Node*)malloc(sizeof(Node));
    if(new){
        new->dad = NULL;
        new->left = NULL;
        new->right = NULL;
        int vlr = 0;
        printf("\nque valor voce quer inserir na arvore: ");
        fgets(buffer,30,stdin);
        vlr = atoi(buffer);
        memset(buffer,0,30);
        new->vlr = vlr;
        return new;
    }else{
        printf("\nnão foi possivel alocar memória");
        return NULL;
    }
}
void delete(Node* *root, Node* z){
    if(z->left == NULL){
        transplant(root,z,z->right);
    }else if(z->right == NULL){
        transplant(root,z,z->left);
    }else{
        Node* y = minimum(z->right);
        if(y != z->right){
            transplant(root,y,y->right);
            y->right = z->right;
            y->right->dad = y;
        }
        transplant(root,z,y);
        y->left = z->left;
        y->left->dad = y;
    }
    free(z);
}
void transplant(Node* *root, Node* u, Node* v){
    if(u->dad == NULL){
        *root = v;
    }else if(u == u->dad->left){
        u->dad->left = v;
    }else{
        u->dad->right = v;
    }
    if(v != NULL){
        v->dad = u->dad;
    }
}
void destroy(Node* root){
    if(root){
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}