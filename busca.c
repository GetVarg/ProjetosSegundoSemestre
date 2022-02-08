#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct item
{
    char nome[25];
    float preco;
    int codigo;
};

typedef struct item Item;

typedef struct no
{
    Item item;
    struct no *esquerda, *direita;
}No;

typedef No * p_no;
  
//------------------------------------------
typedef struct elemento
{
    Item reg;
    struct elemento* prox;
}Elemento;

typedef Elemento * p_elemento;

typedef struct fila
{
    p_elemento head;
    p_elemento top;
}Fila;

typedef Fila * p_f;

//------------------------------------------

Item creat_item(int codigo, float preco, char nome[25]){
    Item aux;
    strcpy(aux.nome, nome);
    aux.codigo = codigo;
    aux.preco = preco;
    return aux;
}

p_no arv_criavazia(void){
    return NULL;
}

int arv_vazia(p_no a){
    return a==NULL;
}

p_no arv_libera(p_no root){
    if (!arv_vazia(root))
    {
        arv_libera(root->esquerda);
        arv_libera(root->direita);
        free(root);
    }
    return NULL;
}

p_no insere_produto_arv(p_no root, Item x){
    if (root == NULL){
        p_no node = malloc(sizeof(No));
        node->item = x;
        node->direita = node->esquerda = NULL;
        return node;
    }
    else{
        if (x.preco < root->item.preco)
            root->esquerda = insere_produto_arv(root->esquerda, x);
        else
            root->direita = insere_produto_arv(root->direita, x);
    }
    return root;
}

p_f inicia_fila(){
    p_f f;
    f = malloc(sizeof(Fila));
    f->head = NULL;
    return f;
}

void inserir_lista(Item x, p_f f){
    p_elemento novo = malloc(sizeof(Elemento));
    novo->reg = x;
    novo->prox = NULL;
    if(f->head == NULL){
        printf("%d %s %f\n", x.codigo, x.nome, x.preco)
        f->head = novo;
    }
    else if (strcmp(novo->reg.nome, f->head->reg.nome) == -1)
    {
        novo->prox = f->head;
        f->head = novo;
    }
    else{
        p_elemento aux, ant;
        ant = NULL;
        aux = f->head;
        while (aux != NULL && strcmp(aux->reg.nome, novo->reg.nome) != -1)
        {
            ant = aux;
            aux = aux->prox;
        }
        if (ant == NULL)
        {
            novo->prox = f->head->prox;
            f->head->prox = novo;
        }
        else
        {
            novo->prox = ant->prox;
            ant->prox = novo;        
        }
    
    }

}

void busca_itens(p_no root, float preco_max, int codigo_interesse, p_f f){
    if (root != NULL)
    {
        if (preco_max >= root->item.preco && codigo_interesse == root->item.codigo){
            inserir_lista(root->item, f);
        }
        if(root->item.preco >= preco_max){
            busca_itens(root->direita, preco_max, codigo_interesse, f);
        
            busca_itens(root->esquerda, preco_max, codigo_interesse, f);
        }
        else
        {
            busca_itens(root->esquerda, preco_max, codigo_interesse, f);
        
            busca_itens(root->direita, preco_max, codigo_interesse, f);
        }
        
    }
}

void imprimir(p_elemento top){
    if (top != NULL)
    {
        printf("%s %d %.2f\n", top->reg.nome, top->reg.codigo, top->reg.preco);
        imprimir(top->prox);
    }
}

void libera_lista(p_elemento head){
    if (head != NULL)
    {
        libera_lista(head->prox);
        free(head);
    }    
}

void imprime_arv(p_no root){
    if (root != NULL)
    {
        printf("%s\n", root->item.nome);
        imprime_arv(root->direita);
        imprime_arv(root->esquerda);
    }
    
}

int main(){
    int n;
    scanf("%d", &n);
    p_no root = arv_criavazia();
    
    for (int i = 0; i < n; i++)
    {
        char nome_loja[25];
        float preco;
        int codigo;
        scanf("%s %d %f", nome_loja, &codigo, &preco);
        root = insere_produto_arv(root, creat_item(codigo, preco, nome_loja));
    }
    int m;
    scanf("%d", &m);
    int codigo_interesse;
    float preco_procurado;
    float preco_max;

    for (int i = 0; i < m; i++)
    {
        p_f f = inicia_fila();
    
        scanf("%d %f", &codigo_interesse, &preco_procurado);
    
        preco_max = (11*preco_procurado)/10;
    
        busca_itens(root, preco_max, codigo_interesse, f);

    
        printf("OFERTAS para %d:\n", codigo_interesse);
        if (f->head == NULL)
            printf("nenhuma boa oferta foi encontrada\n\n");
        else
        {
            imprimir(f->head);
            printf("\n");
        }
        
    
        libera_lista(f->head);
        free(f);
    }
    arv_libera(root);
    
}