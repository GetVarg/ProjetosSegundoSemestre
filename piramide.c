#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//-----------------------------------------
struct item
{
    double valor;
    int nivel;
    char nome[20];
};

typedef struct item Item;

typedef struct no
{
    Item item;
    struct no *esquerda, *direita, *recrutador;
}No;

typedef No * p_no;
//----------------------------------------- estrutura de fila
typedef struct elemento
{
    p_no reg;
    struct elemento* prox;
}Elemento;

typedef Elemento * p_elemento;

typedef struct fila
{
    p_elemento head;
}Fila;

typedef Fila * p_f;

//-----------------------------------------

Item creat_item(int valor, char nome[20]){
    Item aux;
    strcpy(aux.nome, nome);
    aux.valor = valor;
    return aux;
}

p_no inicializa_arv(Item x){
    p_no node = malloc(sizeof(No));
    node->item = x;
    node->esquerda = node->direita = node->recrutador = NULL;
    return node;
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

void taxa(p_no atual){
    double taxa_inc = atual->item.valor/10;
    atual->item.valor = atual->item.valor + taxa_inc;
    atual->recrutador->item.valor = atual->recrutador->item.valor - taxa_inc;



    if(atual->recrutador->direita != NULL && atual->recrutador->esquerda != NULL){
        double taxa_out_esq = (atual->recrutador->esquerda->item.valor*6)/100;
        double taxa_out_dir = (atual->recrutador->direita->item.valor*6)/100;
        
        atual->recrutador->esquerda->item.valor = atual->recrutador->esquerda->item.valor - taxa_out_esq;
        atual->recrutador->direita->item.valor = atual->recrutador->direita->item.valor - taxa_out_dir;
        atual->recrutador->item.valor = atual->recrutador->item.valor + taxa_out_dir + taxa_out_esq;
        
        int k = 5;
        atual = atual->recrutador;
        
        
        while (k > 0 && atual->recrutador != NULL)
        {
            double tax_nivel = (atual->item.valor*k)/100;
            atual->item.valor = atual->item.valor - tax_nivel;
            atual->recrutador->item.valor = atual->recrutador->item.valor + tax_nivel;
            atual = atual->recrutador;
            k--;
        }
    }
    
}

void insere_recrutado(p_no root, Item x){
    p_no node = inicializa_arv(x);
    node->item.nivel = root->item.nivel + 1;
    if(root->esquerda == NULL){
            root->esquerda = node;
            root->esquerda->recrutador = root;
            taxa(root->esquerda);
        }
    else{
        root->direita = node;
        root->direita->recrutador = root;
        taxa(root->direita);
    }
}


void busca_pre_ord(p_no root, Item x, char nome_ref[20]){
    if(strcmp(nome_ref, root->item.nome) == 0){
        insere_recrutado(root, x);
    }
    else{
        if(root->esquerda != NULL)
            busca_pre_ord(root->esquerda, x, nome_ref);
        if(root->direita != NULL)
            busca_pre_ord(root->direita, x, nome_ref);
    }
}

/*-----------------------------------------------------*/
p_f inicia_fila(){
    p_f f;
    f = malloc(sizeof(Fila));
    f->head = NULL;
    return f;
}

void insereFila(p_f f, p_no p){
    p_elemento novo = malloc(sizeof(Elemento));
    novo->reg = p;
    novo->prox = NULL;
    if(f->head==NULL){
        f->head = novo;
    }else{
        p_elemento pointer = f->head;
        p_elemento ant = NULL;
        while(pointer!=NULL){
            ant = pointer;
            pointer = pointer->prox;
        }
        ant->prox = novo;
        free(pointer);
    }
}

p_elemento removeFila(p_f f){
    if(f->head!=NULL){
        p_elemento pointer = f->head;
        f->head = pointer->prox;
        return pointer;
    }
    return 0;
}

void contar(int *cont, p_no root){
    if(root != NULL){
        if (root->item.nivel > *cont)
            *cont = root->item.nivel;
        contar(cont, root->direita);
        contar(cont, root->esquerda);
    }
}
int tamanhoFila(p_f f){
    p_elemento pointer = f->head;
    int tam;
    tam=0;
    while(pointer!=NULL){
        tam++;
        pointer = pointer->prox;
    }
    return tam;
}

void percurso(p_no root){
    p_f fila = inicia_fila();
    p_elemento prox;
    insereFila(fila, root);
    int nivel = root->item.nivel;
    printf("Nivel %d: ", nivel);

    while(tamanhoFila(fila)>0){
        prox = removeFila(fila);
        if(prox != NULL){
            if (nivel != prox->reg->item.nivel)
            {
                nivel++;
                printf("\nNivel %d: ", nivel);
            }
        
            printf("[%s %.2f] ", prox->reg->item.nome, prox->reg->item.valor);
            
            if(prox->reg->esquerda!=NULL)
                insereFila(fila, prox->reg->esquerda);
            if(prox->reg->direita!=NULL)
                insereFila(fila, prox->reg->direita);
        
        }
        free(prox);
    }
    printf("\n\n");
    free(fila);
}

int main(){
    char nome_1[20];
    char fdc[4];
    int valor;
    scanf("%s %s %d", fdc, nome_1, &valor);

    p_no root = inicializa_arv(creat_item(valor, nome_1));
    root->item.nivel = 1;

    while(1==1)
    {
        percurso(root);
        char nome_ref[20], nome_rec[20], tipo[7];
        scanf("%s %s %s %d", nome_ref, tipo, nome_rec, &valor);
        if (getchar() == EOF)
        {
            break;
        }
        
        busca_pre_ord(root, creat_item(valor, nome_rec), nome_ref);
    }
    arv_libera(root);
    return 0;
}