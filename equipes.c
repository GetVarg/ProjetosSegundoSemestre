#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int alt;
    struct no *proximo;
}No;

typedef No * p_no;

typedef struct
{
    p_no inicio;
    p_no fim;
    int tam;
}Lista;

typedef Lista * p_l;

p_l criar_lista(){
    p_l fila;
    fila = malloc(sizeof(Lista));
    fila->fim = NULL;
    fila->inicio = NULL;
    return fila;
}

void inserir_fim(p_l lista, int alt){

    p_no novo = malloc(sizeof(No));

    novo->alt = alt;
    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->fim = novo;
        lista->fim->proximo = lista->inicio;
    }
    else{
        lista->fim->proximo = novo;
        lista->fim = novo;
        novo->proximo = lista->inicio;
    }
    
}

void inserir_ini(p_l lista, int alt){

    p_no novo = malloc(sizeof(No));

    novo->alt = alt;
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    if (lista->fim == NULL)
    {
        lista->fim = novo;
    }
    lista->fim->proximo = lista->inicio;
    
}

void imprime(p_l lista){
    p_no aux = lista->inicio;
    while (aux != lista->fim)
    {
        printf("%d ", aux->alt);
        aux = aux->proximo;
    }
    printf("%d\n", aux->alt);
    
}

p_no trocar_comd(p_l lista){
    p_no remover = NULL;
    remover = lista->inicio;
    lista->fim->proximo = remover->proximo;
    lista->inicio = remover->proximo;
    lista->tam--;
    return remover;
}

p_no remover(p_l lista, int num){
    if (num < 0)
    {
        num = - num;
    }

    p_no aux, remover = NULL;
    
    if (lista->tam == 1)
    {
        trocar_comd(lista);
    }
    else{

        aux = lista->inicio;
        int i;
        for (i = 0; i < num; i++)
        {
            aux = aux->proximo;
            
        }
        
        if (aux->proximo == lista->fim)
        {
            remover = aux->proximo;
            aux->proximo = remover->proximo;
            lista->fim = aux;
        }
        else
        {
            remover = aux->proximo;
            aux->proximo = remover->proximo;
            
        }
    
    }
    lista->tam--;
    
    return remover;
}


void inserir_ord(p_l lista, int alt){
    p_no aux = malloc(sizeof(No));
    p_no novo = malloc(sizeof(No));

    novo->alt = alt;

    if (lista->inicio == NULL)
    {
        free(aux);
        free(novo);
        inserir_ini(lista, alt);;
    }
    else if (novo->alt < lista->inicio->alt)
    {
        free(aux);
        free(novo);
        inserir_ini(lista, alt);
    }
    else
    {
        aux = lista->inicio;
        while (aux->proximo != lista->inicio && novo->alt > aux->proximo->alt)
        {
            aux = aux->proximo;
        }
        if (aux->proximo == lista->inicio)
        {
            free(novo);
            inserir_fim(lista, alt);
        }
        else
        {
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
        
    }

}

void destruir(p_l l)
{
    if (l != NULL)
    {
        p_no aux = l->inicio;
        while (aux != l->fim)
        {
            l->inicio = l->inicio->proximo;
            free(aux);
            aux = l->inicio;
        }
        free(l);
    }
}

int main(){
    p_l lista, time_esq, time_dir;
    lista = criar_lista();
    time_esq = criar_lista();
    time_dir = criar_lista();


    int n;
    scanf("%d\n", &n);
    
    lista->tam = n;
    
    for (int i = 0; i < n; i++)
    {
        int alt;
        scanf("%d\n", &alt);
        inserir_fim(lista, alt);
    }

    p_no removido;
    removido = NULL;
    
    for (int i = 0; i < n; i++)
    {

        int sorte;
        if (i%2 != 1)
        {   
            scanf("%d", &sorte);
            int aux = sorte - 1;
            if (sorte == 1 || lista->tam == 1)
            {
                removido = trocar_comd(lista);
                
            }
            else if (aux%lista->tam == 0 && lista->tam < sorte)
            {
                removido = trocar_comd(lista);
            }
            else
            {
                removido = remover(lista, lista->tam - sorte);
            }
            inserir_ord(time_esq, removido->alt);
            //printf("--------------------------------\n");
        }
        else{
            scanf("%d", &sorte);
            int aux = sorte - 1;
            
            if (sorte == 1 || lista->tam == 1)
            {
                removido = trocar_comd(lista);
            }
            else if (aux%lista->tam == 0 && lista->tam < sorte)
            {
                removido = trocar_comd(lista);
            }
            
            else
            {
                removido = remover(lista, sorte - 2);
            }
            inserir_ord(time_dir, removido->alt);
        }
        free(removido);
    }

    imprime(time_esq);
    imprime(time_dir);

    destruir(time_esq);
    destruir(time_dir);
    destruir(lista);
    
    return 0;
}
