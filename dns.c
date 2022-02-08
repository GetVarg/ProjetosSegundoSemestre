#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ip{
    int ip_a, ip_b, ip_c, ip_d;
}Ip;

typedef struct no
{
    Ip ip;
    char nome_dominio[100];
    int qtd;
    struct no *esquerda, *direita;
    int altura;
}No;

typedef No * p_no;

/*
    função que cria um novo no
    x->valor a ser inserido
    retorna: endereço do no criado
*/
p_no novoNo(Ip x, char nome[100]){
    p_no novo = malloc(sizeof(No));
    if(novo){
        novo->ip = x;
        strcpy(novo->nome_dominio, nome);
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }
    return novo;
}

p_no novoNo_req(Ip x){
    p_no novo = malloc(sizeof(No));
    if(novo){
        novo->ip = x;
        novo->qtd = 0;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }
    return novo;
}

//cria a arvore vazia
p_no arv_criavazia(void){
    return NULL;
}

/*
    compara dois ips a, b e determina e retorna 1 se a>b e retorna 0 se a<b ou 2 se a = b
*/
int comparar_ips(Ip ip_1, Ip ip_2){
    if(ip_1.ip_a == ip_2.ip_a && ip_1.ip_b == ip_2.ip_b && ip_1.ip_c == ip_2.ip_c && ip_1.ip_d == ip_2.ip_d)
        return 2;
    else if (ip_1.ip_d > ip_2.ip_d)
        return 1;
    else if(ip_1.ip_d < ip_2.ip_d)
        return 0;
    else if (ip_1.ip_c > ip_2.ip_c)
        return 1;
    else if(ip_1.ip_c < ip_2.ip_c)
        return 0;    
    else if (ip_1.ip_b > ip_2.ip_b)
        return 1;
    else if(ip_1.ip_b < ip_2.ip_b)
        return 0;
    else if (ip_1.ip_a > ip_2.ip_a)
        return 1;
    return 0;
}

/*
    Retorna o aior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
int maior(int a, int b){
    return (a > b)? a: b;
}

// Retorna a altura de um nó ou -1 caso ele seja null
int alturaNo(p_no no){
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

// calcula e retorna o fator de balanceamento de um no
int fatorBalanceamento(p_no no){
    if (no)
        return (alturaNo(no->esquerda) - alturaNo(no->direita));
    else
        return 0;
}

// função para a rotação à esquerda
p_no rotacaoEsquerda(p_no r){
    p_no y, f;
    y = r->direita;
    f = y->esquerda;
    
    y->esquerda = r;
    r->direita = f;

    r->altura = maior(alturaNo(r->esquerda), alturaNo(r->direita)) + 1;
    y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

// função para a rotação à direita
p_no rotacaoDireita(p_no r){
    p_no y, f;
    y = r->esquerda;
    f = y->direita;

    y->direita = r;
    r->esquerda = f;

    r->altura = maior(alturaNo(r->esquerda), alturaNo(r->direita)) + 1;
    y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

// função para rotação dupla
p_no rotacaoDireitaEsquerda(p_no r){
    r->direita = rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

// função para rotação dupla
p_no rotacaoEsquerdaDireita(p_no r){
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);
}

/*
    função para realizar o balanceamento da árvore após uma inserção ou remoção
    recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
p_no balancear(p_no root){
    int fb = fatorBalanceamento(root);
    if (fb < -1 && fatorBalanceamento(root->direita) <= 0)
        root = rotacaoEsquerda(root);
    else if (fb > 1 && fatorBalanceamento(root->esquerda) >= 0)
        root = rotacaoDireita(root);
    else if (fb > 1 && fatorBalanceamento(root->esquerda) < 0)
        root = rotacaoEsquerdaDireita(root);
    else if (fb < -1 && fatorBalanceamento(root->direita) > 0)
        root = rotacaoDireitaEsquerda(root);
    return root;
}

/*
    busca um dominio no na árvore dos acessos
    root -> raiz da árvore
    retorno: 0 se não encontrar e root se encontrar
*/
int buscar_num(p_no root, char nome[100], Ip x, int max){
    if(root != NULL){
        if(comparar_ips(root->ip, x) == 2){
            return root->qtd;
        }
        else
        {
            int aux = comparar_ips(x, root->ip);
            if(aux)
                return buscar_num(root->esquerda, nome, x, max);
            else
                return buscar_num(root->direita, nome, x, max); 
        }
    }
    return -1;
}

/*
    busca um dominio no na árvore dos acessos
    root -> raiz da árvore
    printa a mensagem de aceitação e torna cond = 1 se encontrar o dominio
*/
void buscar_no(p_no root, char nome[100], int *cond,Ip novo){
    if (root != NULL){
        if(strcmp(nome, root->nome_dominio) == 0){
            *cond = 1;
            printf("ACCEPTED %s FROM %d.%d.%d.%d ", nome, novo.ip_a, novo.ip_b, novo.ip_c, novo.ip_d);
            printf("RESPOND %d.%d.%d.%d\n", root->ip.ip_a, root->ip.ip_b, root->ip.ip_c, root->ip.ip_d);
        }
        buscar_no(root->esquerda, nome, cond, novo);
        buscar_no(root->direita, nome, cond, novo);
    }
}

/*
    insere um novo no na árvore
    root -> raiz da árvore
    x-> valor a ser inserido
    retorno: endereço do novo no ou nova raiz apos o balanceamento
*/
p_no inserir_dominios(p_no root, Ip x, char nome[100], int request){
    if (root == NULL){
        root = novoNo(x,nome);
        return root;
    }
    else
    {
        int aux = comparar_ips(x, root->ip);
        if (aux)
            root->esquerda = inserir_dominios(root->esquerda, x, nome, request);
        if (aux == 0)
            root->direita = inserir_dominios(root->direita, x, nome, request);
    }
    root->altura = maior(alturaNo(root->esquerda), alturaNo(root->direita)) + 1;
    root = balancear(root);
    return root;
}

/*
    insere um novo no na árvore
    root -> raiz da árvore
    x-> valor a ser inserido
    retorno: endereço do novo no ou nova raiz apos o balanceamento
*/
p_no inserir_req(p_no root, Ip x, char nome[100], int request){
    if (root == NULL){
        root = novoNo_req(x);
        return root;
    }
    else if(comparar_ips(x, root->ip) == 2){
        root->qtd++;
        return root;
    }
    else
    {
        int aux = comparar_ips(x, root->ip);
        if (aux == 1)
            root->esquerda = inserir_req(root->esquerda, x, nome, request);
        else if (aux == 0)
            root->direita = inserir_req(root->direita, x, nome, request);
        else if (aux == 2)
        {
            root->qtd++;
        }
        
    }
    root->altura = maior(alturaNo(root->esquerda), alturaNo(root->direita)) + 1;
    root = balancear(root);
    return root;
}

int main(){
    int max_request, num_dns;
    scanf("%d", &max_request);
    scanf("%d", &num_dns);

    p_no root_dominios = arv_criavazia();
    for (int i = 0; i < num_dns; i++)
    {
        char nome_dominio[100];
        Ip novo;
        scanf("%s %d.%d.%d.%d", nome_dominio, &novo.ip_a, &novo.ip_b, &novo.ip_c, &novo.ip_d);
        root_dominios = inserir_dominios(root_dominios, novo, nome_dominio, 1);
    }

    int acesso;
    scanf("%d", &acesso);
    p_no root_request = arv_criavazia();
    for (int i = 0; i < acesso; i++)
    {
        char nome_dominio[100];
        Ip novo;
        for (int k = 0; k < 4; k++)
        {
            getchar();
        }
        
        scanf("%s", nome_dominio);

        for (int j = 0; j < 6; j++)
        {
            getchar();
        }
        scanf("%d.%d.%d.%d", &novo.ip_a, &novo.ip_b, &novo.ip_c, &novo.ip_d);
        
        root_request = inserir_req(root_request, novo, nome_dominio, max_request);
        
        int aux_req = buscar_num(root_request, nome_dominio, novo, max_request);        
        
        if(aux_req < max_request){
            int cond = 0;
            buscar_no(root_dominios, nome_dominio, &cond, novo);
            if(cond == 0)
                printf("NOTFOUND %s FROM %d.%d.%d.%d\n", nome_dominio, novo.ip_a, novo.ip_b, novo.ip_c, novo.ip_d);
        }
        else
            printf("FORBIDDEN %s FROM %d.%d.%d.%d\n", nome_dominio, novo.ip_a, novo.ip_b, novo.ip_c, novo.ip_d);
        
    }
}