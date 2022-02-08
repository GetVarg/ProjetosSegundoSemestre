#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int lanterna;
    int tamanho;
}Data;


typedef struct No
{
    int num;
    char profissao[25];
    char vacina[12];
    struct No *prox;
}No;

typedef No * p_no;

typedef struct
{
    p_no ini, fim;
}Fila;

typedef Fila * p_fila;

/*-------------------------------------------------------
funcoes
*/

int comparar(char *profissao){
    char *ch1 = "youtuber-financas";
    char *ch2 = "coach"; 
    char *ch3 = "herdeiro";
    char *ch4 = "filho-politico";
    char *ch5 = "ex-bbb";

    if (strcmp(profissao, ch1) && strcmp(profissao, ch2) && strcmp(profissao, ch3) && strcmp(profissao, ch4) && strcmp(profissao, ch5))
    {
        return 0;
    }
    
    return 1;
}
p_no criar_lista(){
    return NULL;
}

p_fila criar_fila(){
    p_fila f;
    f = malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void add_elemento_comeco(p_fila fila, int num, char *profissao, char *vacina){
    
    p_no novo;
    novo = malloc(sizeof(No));
    novo->num = num;
    strcpy(novo->profissao, profissao);
    strcpy(novo->vacina, vacina);
    
    if (fila->ini == NULL)
    {
        novo->prox = NULL;
        fila->ini = novo;
        fila->fim = novo;
    }
    else
    {
        novo->prox = fila->ini;
        fila->ini = novo;
    }

}

void add_elemento_final(p_fila f, int num, char *profissao, char *vacina){
    p_no novo;
    novo = malloc(sizeof(No));

    novo->num = num;
    strcpy(novo->profissao, profissao);
    strcpy(novo->vacina, vacina);

    novo->prox = NULL;
    
    if (f->ini == NULL)
    {
        f->ini = novo;
        f->fim = novo;
    }
    else
    {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void add_elemento_pos(p_fila f, int num, char *profissao, char *vacina, int lanterna, int tamanho){
    p_no novo, atual, aux;
    atual = f->ini;
    novo = malloc(sizeof(No));

    novo->num = num;
    strcpy(novo->profissao, profissao);
    strcpy(novo->vacina, vacina);

    novo->prox = NULL;
    for (int i = 0; i < lanterna-1; i++)
    {
        atual = atual->prox;
    }
    aux = atual->prox;
    atual->prox = novo;
    novo->prox = aux;
}

void eliminar(p_fila f){
    p_no aux = f->ini->prox;
    while (aux != NULL && strcmp(aux->vacina, "nao-vacinado") == 0)
    {
        aux = aux->prox;
    }
    if(aux != NULL)
        f->ini->prox->prox = aux;
}

void org(p_fila fila, p_no no, int num, char *profissao, char *vacina, Data *controle){

    p_no novo;
    novo = malloc(sizeof(No));
    novo->num = num;
    strcpy(novo->profissao, profissao);
    strcpy(novo->vacina, vacina);
    
    if (comparar(profissao) == 1)
    {
        controle->lanterna = 1;
        add_elemento_comeco(fila, num, profissao, vacina);
        controle->lanterna = 1;
    }
    else if (strcmp(profissao, "funcionario") == 0)
    {
        add_elemento_final(fila, num, profissao, vacina);
        controle->lanterna = controle->tamanho;
    }
    
    else{
        if (controle->tamanho == 1 || controle->lanterna == controle->tamanho)
        {
            fila->fim.
            add_elemento_final(fila, num, profissao, vacina);
        }
        else
        {
            add_elemento_pos(fila, num, profissao, vacina, controle->lanterna, controle->tamanho);
        }
        if (strcmp(profissao, "fiscal") == 0)
            eliminar(fila);
        
    }
    
}

void destruir(p_fila l)
{
    if (l != NULL)
    {
        p_no aux = l->ini;
        while (aux != NULL)
        {
            l->ini = l->ini->prox;
            free(aux);
            aux = l->ini;
        }
        free(l);
    }
}

void imprime(p_fila fila){
    p_no inicio = fila->ini;
    while (inicio != NULL)
    {
        printf("%d %s %s\n", inicio->num, inicio->profissao, inicio->vacina);
        inicio = inicio->prox;
    }
    
}


/*-------------------------------------------------------
core*/

int main(){
    p_no lista;
    lista = criar_lista();

    p_fila fila;
    fila = criar_fila();

    Data controle;
    controle.lanterna = 1;
    controle.tamanho = 1;

    int ch;
    while(scanf("%d", &ch) != EOF)
    {
        char profissao[200];
        char vacina[96];
        scanf(" %s %s\n", profissao, vacina);
        org(fila, lista, ch, profissao, vacina, &controle);
        controle.lanterna++;
        controle.tamanho++;
    }
    
    
    imprime(fila);
    destruir(fila);
    
    return 0;
}