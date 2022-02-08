#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    char nome[20];
    int obj;
    char tipo[20];
    int qtd;
    struct no *proximo;
}No;

typedef No * p_no;

typedef struct
{
    p_no inicio;
    p_no fim;
    int comp;
}Lista;

typedef Lista * p_l;

/*--------------------------------------------------------typedef's pilha----------------------------------------------------*/
typedef struct no_pilha
{
    char tipo[20];
    struct no_pilha *proximo;
}NO_pilha;

typedef NO_pilha * p_no_pilha;

typedef struct{
    p_no_pilha topo;
    int tam;
}Pilha;

typedef Pilha * p_pilha;
/*------------------------------------ funcoes pilha------------------------------------------------*/
p_pilha inicia(){
    p_pilha pilha = (p_pilha)malloc(sizeof(Pilha));
    pilha->tam = 0;
    pilha->topo = NULL;
    return pilha;
}

void push(p_pilha *p, p_no navio, int num, int capacidade){
    for (int i = 0; i < num; i++)
    {
        int des = 0;

        while (navio->qtd > 0 && p[i]->tam < capacidade)
        {
            p_no_pilha novo;
            novo = NULL;
            novo = malloc(sizeof(NO_pilha));
            strcpy(novo->tipo, navio->tipo);
            novo->proximo = p[i]->topo;
            p[i]->topo = novo;
            p[i]->tam++;
            navio->qtd--;
            des++;
        }
        if (des > 0)
        {
            printf("%s descarrega %s doca: %d conteineres: %d\n", navio->nome, navio->tipo, i, des);
            break;
        }
        
    }
}

void desempilha(p_pilha *pilha, p_no navio, int num){
        
    for (int i = 0; i < num; i++)
    {
        int des = 0;
        while (pilha[i]->tam > 0 && navio->qtd > 0 && strcmp(pilha[i]->topo->tipo, navio->tipo) == 0)
        {
            p_no_pilha aux = NULL;
            if (pilha[i]->topo)
            {
                aux = pilha[i]->topo;
                pilha[i]->topo = aux->proximo;
                navio->qtd--;
                pilha[i]->tam--;
                des++;
            }
            else
                break;
                        
        }
        if (des > 0)
        {
            printf("%s carrega %s doca: %d conteineres: %d\n", navio->nome, navio->tipo, i, des);
            break;
        }
    }
    
}

void destruir_pilha(p_pilha pilha){
    p_no_pilha aux = pilha->topo;
    while(aux != NULL){
        free(aux);
        aux = aux->proximo;
    }
    free(pilha);
}

/*------------------------------------ funcoes fila ------------------------------------------------*/
p_l criar_lista(){
    p_l fila;
    fila = malloc(sizeof(Lista));
    fila->fim = NULL;
    fila->inicio = NULL;
    return fila;
}


void inserir_fim(p_l lista, char nome[20], int obj, char tipo[20], int qtd){
    p_no novo = malloc(sizeof(No));

    strcpy(novo->nome, nome);
    novo->obj = obj;
    strcpy(novo->tipo, tipo);
    novo->qtd = qtd;
    novo->proximo = NULL;

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->fim = novo;
    }
    else{
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
}

void remover_prim(p_l lista){
    // p_no aux = malloc(sizeof(No));
    if (lista->inicio != NULL)
    {
        p_no aux = lista->inicio;
        lista->inicio = aux->proximo;

    }
    
    else
    {
        lista = NULL;
    }
}

void destruir(p_l l)
{
    if (l != NULL)
    {
        p_no aux = l->inicio;
        while (aux != NULL)
        {
            l->inicio = l->inicio->proximo;
            free(aux);
            aux = l->inicio;
        }
        free(l);
    }
}

int tipo(p_no elemento){
    int cond = 0;
    while (elemento != NULL)
    {
        if(elemento->obj == 1){
            if(cond == 2)
                return 3;
            cond = 1;
        }
        else{
            if(cond == 1)
                return 3;
            cond = 2;
        }
        elemento = elemento->proximo;
    }
    return cond;
}

int IsFull(p_pilha *pilha, int capacidade, int num_docas){
    for (int i = 0; i < num_docas; i++)
    {
        if(pilha[i]->tam < capacidade){
            return 0;
        }
    }
    return 1;
}

int No_top(p_pilha *pilha, p_no elemento, int num_docas){
    while(elemento != NULL){
        for (int i = 0; i < num_docas; i++)
        {
            if(pilha[i]->topo->tipo != NULL){
                if(strcmp(pilha[i]->topo->tipo, elemento->tipo) == 0)
                    return 0;
            }
        }
        elemento = elemento->proximo;
    }
    return 1;
    
}

int check(p_l lista, p_pilha *pilha, int num_docas, int capacidade){
    int cond = tipo(lista->inicio);
    if (cond == 1){
        if(No_top(pilha, lista->inicio, num_docas)){
            return 1;
        }
    }
    else if(cond == 2){
        if(IsFull(pilha, capacidade, num_docas))
            return 1;
    }
    else if(cond == 3){
        if(IsFull(pilha, capacidade, num_docas) && No_top(pilha, lista->inicio, num_docas))
            return 1;
    }
    return 0;
}


/*------------------------------------core----------------------------------------------------------------------------------------*/

int main(){
    int num_docas, capacidade;
    p_l lista;
    lista = criar_lista();


    scanf("%d", &num_docas);
    scanf("%d", &capacidade);

    p_pilha *pilha;
    pilha = malloc(sizeof(p_no_pilha)*num_docas);

    for (int i = 0; i < num_docas; i++)
    {
        pilha[i] = inicia();
    }
    
    scanf("%d", &lista->comp);

    for (int i = 0; i < lista->comp; i++)
    {
        char nome[20], obj_str[20], tipo[20];
        int qtd;
        
        scanf("%s %s %s %d", nome, obj_str, tipo, &qtd);
        int obj;
        if (strcmp(obj_str, "carrega") == 0){
            obj = 1;
        }
        else{
            obj = 2;
        }
        inserir_fim(lista, nome, obj, tipo, qtd);
    }

    p_no aux = lista->inicio;
    while (lista != NULL)
    {
        remover_prim(lista);
        lista->comp--;
        if (aux->obj == 2)
        {
            push(pilha, aux, num_docas, capacidade);
            if (aux->qtd != 0)
            {
                inserir_fim(lista, aux->nome, aux->obj, aux->tipo, aux->qtd);
                lista->comp++;
            }
                
        }
        else if(aux->obj == 1)
        {
            desempilha(pilha, aux, num_docas);
            if (aux->qtd != 0)
            {
                inserir_fim(lista, aux->nome, aux->obj, aux->tipo, aux->qtd);
                lista->comp++;
            }
                
        }
        if(check(lista, pilha, num_docas, capacidade)){
            printf("ALERTA: impossivel esvaziar fila, restam %d navios.\n", lista->comp);
            break;
        }
        else if(lista->inicio != NULL){
            aux = lista->inicio;
        }
        else
        {
            break;
        }
            
    }
    destruir(lista);
    free(aux);
    for (int i = 0; i < num_docas; i++)
    {
        destruir_pilha(pilha[i]);
    }
    free(pilha);
    return 0;
}