#include <stdio.h>
#include <string.h>
#define Max_size 100
#define MAX_STRING_SIZE 30
typedef struct
{
    char nomes[Max_size][MAX_STRING_SIZE];
    char primeiro_nome[Max_size][MAX_STRING_SIZE];
    char sobrenome[Max_size][MAX_STRING_SIZE];
    char nomes_finais[Max_size][MAX_STRING_SIZE];
    char controle[9];
    int n;
}info;

info lista_homonimo(info *dados){
    int j = 0;
    for (int i = 0; i < dados->n; i++)
    {
        int t = 0;
        char *aux = dados->primeiro_nome[i];
        for (int k = i+1; k < dados->n; k++)
        {
            int p = 0;
            while (aux[p] != '\0' && dados->primeiro_nome[k][p] != '\0' && dados->primeiro_nome[i][p] == dados->primeiro_nome[k][p])
            {
                p++;
            }
            if (dados->primeiro_nome[i][p] == '\0' && dados->primeiro_nome[k][p] == '\0')
            {
                t = 1;
                strcpy(dados->nomes_finais[j], dados->nomes[k]);
                j++;
            }
            
        }
        if (t == 1)
        {
            strcpy(dados->nomes_finais[j], dados->nomes[i]);
            j++;
        }
        
    }

    return *dados;
}

info lista_parente(info *dados){
    int j = 0;
    for (int i = 0; i < dados->n; i++)
    {
        int t = 0;
        char *aux = dados->sobrenome[i];
        for (int k = i+1; k < dados->n; k++)
        {
            int p = 0;
            while (aux[p] != '\0' && dados->sobrenome[k][p] != '\0' && dados->sobrenome[i][p] == dados->sobrenome[k][p])
            {
                p++;
            }
            if (dados->sobrenome[i][p] == '\0' && dados->sobrenome[k][p] == '\0')
            {
                t = 1;
                strcpy(dados->nomes_finais[j], dados->nomes[k]);
                j++;
            }
            
        }
        if (t == 1)
        {
            strcpy(dados->nomes_finais[j], dados->nomes[i]);
            j++;
        }
    }
    
    return *dados;
}

int igualdade_caracter(char s1[9], char s2[9]){
    int i=0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
    {
        ++i;
    }
    if (s1[i] == '\0' && s2[i] == '\0')
    {
        return 1;
    }
    else{
        return 0;
    }
    
    
}

info dividir_str(info *dados){
    for (int i = 0; i < dados->n; i++)
    {
        int k = 0;
        while (dados->nomes[i][k] != '_')
        {
            dados->primeiro_nome[i][k] = dados->nomes[i][k];
            k++;
        }
        
        int p = 0;
        while (dados->nomes[i][k] != '\0')
        {
            if (dados->nomes[i][k] == '_')
            {
                k++;
            }
            
            dados->sobrenome[i][p] = dados->nomes[i][k];
            k++;
            p++;
        }
        
    }
    return *dados;
    
}

info ordenar(info *dados){
    char temp[MAX_STRING_SIZE];

    int k = sizeof(dados->nomes_finais)/sizeof(dados->nomes_finais[2]);
    k = k/25;

    for(int i = 0; i < k; i++){
        for(int j=0; j < k-1-i; j++){
            
            if(strcmp(dados->nomes_finais[j], dados->nomes_finais[j+1]) > 0){
                strcpy(temp, dados->nomes_finais[j]);
                strcpy(dados->nomes_finais[j], dados->nomes_finais[j+1]);
                strcpy(dados->nomes_finais[j+1], temp);
            }
        }
    }
    return *dados;
}

int main(){
    
    info dados;
    
    scanf("%d", &dados.n);

    char var[9];

    scanf("%s", var);

    for (int i = 0; i < Max_size; i++)
    {
        dados.nomes_finais[i][0] = 0;
    }

    for(int i=0; i < dados.n; i++)
    {
        scanf("%s", dados.nomes[i]);
    }

    strcpy(dados.controle, "homonimos");

    dividir_str(&dados);

    if (igualdade_caracter(var, dados.controle))
    {
        lista_homonimo(&dados);
    }
    else
    {
        lista_parente(&dados);
    }
    
    ordenar(&dados);
    
    for (int i = 0; i < 4; i++)
    {
        printf("%s\n", dados.nomes_finais[i]);
    }
    
    return 0;
}