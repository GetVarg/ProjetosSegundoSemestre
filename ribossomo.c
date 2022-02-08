#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *dna_alien;
    char *rna_alien;
    int tamanho;
    char *segmento;
    char *segmento_rna;
    int *contagem;
    int *id;
}info;

int indicie(char *dna, char base){

    for (int i = 0; i < 13; i++)
    {
        if (dna[i] == base)
        {
            return i;
        }
        
    }
    return 0;
    
}

void ler_dados(info *dados){
    
    dados->dna_alien = malloc(sizeof(char) * 13);
    dados->rna_alien = malloc(sizeof(char) * 13);
        
    for (int i = 0; i < 13; i++)
    {
        scanf("%c", &dados->dna_alien[i]);   
    }

    getchar();

    for (int i = 0; i < 13; i++)
    {
        scanf("%c", &dados->rna_alien[i]); 
    }    

    scanf("%d", &dados->tamanho);

    dados->segmento = malloc(dados->tamanho * sizeof(char));
    dados->segmento_rna = malloc(dados->tamanho * sizeof(char));

    getchar();
    
    for (int i = 0; i < dados->tamanho; i++)
    {
        scanf("%c", &dados->segmento[i]);
    }

}

int main(){
    info dados;
    dados.dna_alien = NULL;
    dados.rna_alien = NULL;
    dados.segmento = NULL;
    dados.segmento_rna = NULL;
    dados.contagem = NULL;
    dados.tamanho = 0;

    ler_dados(&dados);

    dados.segmento_rna = malloc(sizeof(char) * dados.tamanho);
    dados.id = malloc(sizeof(int) * dados.tamanho);
    dados.contagem = malloc(sizeof(int) * 13);

    for (int k = 0; k < 13; k++)
    {
        dados.contagem[k] = 0;
    }

    for (int i = 0; i < dados.tamanho; i++)
    {
        int ind = indicie(dados.dna_alien, dados.segmento[i]);
        dados.segmento_rna[i] = dados.rna_alien[ind];
        dados.id[i] = dados.contagem[ind];
        dados.contagem[ind]++;
    }

    printf("ID: \t");
    for (int i = 0; i < dados.tamanho; i++)
    {
        printf("%d ", dados.id[i]);
    }
    printf("\n");

    printf("DNA: \t");
    for (int i = 0; i < dados.tamanho; i++)
    {
        printf("%c ", dados.segmento[i]);
    }
    printf("\n");

    printf("\t");
    for (int i = 0; i < dados.tamanho; i++)
    {
        printf("| ");
    }
    printf("\n");

    printf("RNA: \t");
    for (int i = 0; i < dados.tamanho; i++)
    {
        printf("%c ", dados.segmento_rna[i]);
    }

    free(dados.contagem);
    free(dados.dna_alien);
    free(dados.id);
    free(dados.rna_alien);
    free(dados.segmento);
    free(dados.segmento_rna);
    return 0;
}