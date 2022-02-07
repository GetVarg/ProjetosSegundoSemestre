#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float faixa_renda[5];
    int faixa_renda_anual[5];
    float taxa_imp[5];
    float **renda_mensal;
    float *renda_anual;
    float **imposto_mes;
    float *total_imposto_anual;
    float *abatimento;
    int n;
    float *ajuste;
}info;

void retido_na_fonte(info *dados){

    for (int i = 0; i<dados->n; i++){
        for (int j = 0; j < 12; j++){
            dados->imposto_mes[i][j] = 0;
        }
    }

    for (int n = 0; n < dados->n; n++){
        for (int k = 0; k < 12; k++)
        {
            for (int i = 0; i < 5; i++)
            {
            
                if (dados->renda_mensal[n][k] > dados->faixa_renda[i+1] && i < 4 && dados->renda_mensal[n][k] > dados->faixa_renda[i]){
                    dados->imposto_mes[n][k] += (dados->faixa_renda[i+1] - dados->faixa_renda[i])*dados->taxa_imp[i];
                }
            
                if (dados->renda_mensal[n][k] > dados->faixa_renda[i] && dados->renda_mensal[n][k] < dados->faixa_renda[i+1] && i < 4){
                    dados->imposto_mes[n][k] += (dados->renda_mensal[n][k]-dados->faixa_renda[i])*dados->taxa_imp[i];
                    break;
                }

                if(i == 4 && dados->faixa_renda[i] < dados->renda_mensal[n][k])
                {
                    dados->imposto_mes[n][k] += (dados->renda_mensal[n][k]-dados->faixa_renda[4])*dados->taxa_imp[4];
                }
            }
        }
    }
    
}

void imposto_anual(info *dados){

    for (int k = 0; dados->n > k; k++)
    {

        dados->total_imposto_anual[k] = 0;

        dados->renda_anual[k] = dados->renda_anual[k] - dados->abatimento[k];

        for (int i = 0; i < 5; i++){
        
            if (dados->renda_anual[k] > dados->faixa_renda_anual[i+1] && dados->renda_anual[k] > dados->faixa_renda_anual[i] && i < 4){
                dados->total_imposto_anual[k] += (dados->faixa_renda_anual[i+1] - dados->faixa_renda_anual[i])*dados->taxa_imp[i];
            }
        
            if (dados->renda_anual[k] > dados->faixa_renda_anual[i] && dados->renda_anual[k] < dados->faixa_renda_anual[i+1] && i < 4){
                dados->total_imposto_anual[k] += (dados->renda_anual[k]-dados->faixa_renda_anual[i])*dados->taxa_imp[i];
            }

            if (i == 4 && dados->faixa_renda_anual[i] < dados->renda_anual[k])
            {
                dados->total_imposto_anual[k] += (dados->renda_anual[k]-dados->faixa_renda_anual[4])*dados->taxa_imp[4];
            }
            
        }
    }
}

void impresso(info *dados){
    printf("Jan	Fev	Mar	Abr	Mai	Jun	Jul	Ago	Set	Out	Nov	Dez	Retido Devido Ajuste \n");
    for (int i = 0; i < dados->n; i++)
    {
        float devido = 0;
        for (int k = 0; k < 12; k++)
        {
            printf("%.2f\t", dados->imposto_mes[i][k]);
            devido += dados->imposto_mes[i][k];
        }
        
        printf("%.2f\t", devido);
        
        printf("%.2f\t", dados->total_imposto_anual[i]);

        printf("%.2f\n", dados->ajuste[i]);
    }
    
}

int main(){

    info dados;
    
    dados.faixa_renda[0] = 0;
    dados.faixa_renda[1] = 1499.15;
    dados.faixa_renda[2] = 2246.75;
    dados.faixa_renda[3] = 2995.70;
    dados.faixa_renda[4] = 3743.19;

    dados.taxa_imp[0] = 0;
    dados.taxa_imp[1] = 0.075;
    dados.taxa_imp[2] = 0.15;
    dados.taxa_imp[3] = 0.225;
    dados.taxa_imp[4] = 0.275;

    dados.faixa_renda_anual[0] = 0;
    dados.faixa_renda_anual[1] = 18000;
    dados.faixa_renda_anual[2] = 26400;
    dados.faixa_renda_anual[3] = 36000;
    dados.faixa_renda_anual[4] = 44400;

    scanf("%d", &dados.n);
    dados.imposto_mes = calloc(dados.n, sizeof(float *));
    for (int i = 0; i < dados.n; i++)
    {
        dados.imposto_mes[i] = calloc(12, sizeof(float));
    }

    dados.renda_mensal = calloc(dados.n, sizeof(float *));
    for (int i = 0; i < dados.n; i++)
    {
        dados.renda_mensal[i] = calloc(12, sizeof(float));
        for (int k = 0; k < 12; k++)
        {
            dados.renda_mensal[i][k] = 0;
        }
        
    }

    dados.abatimento = calloc(dados.n, sizeof(float));
    dados.ajuste = calloc(dados.n, sizeof(float));
    dados.total_imposto_anual = calloc(dados.n, sizeof(float));
    dados.renda_anual = calloc(dados.n, sizeof(float));

    for (int i = 0; i < dados.n; i++)
    {
        float soma = 0;
        dados.renda_anual[i] = 0;
        for (int k = 0; k < 12; k++)
        {
            scanf("%f", &dados.renda_mensal[i][k]);
            soma += dados.renda_mensal[i][k];
        }

        dados.renda_anual[i] += soma;

        retido_na_fonte(&dados);

    }
    
    for (int i = 0; i < dados.n; i++)
    {
        scanf("%f", &dados.abatimento[i]);
    }

    imposto_anual(&dados);

    for (int i = 0; i < dados.n; i++)
    {
        float total = 0;
        for (int k = 0; k < 12; k++)
        {
            total += dados.imposto_mes[i][k];
        }
        dados.ajuste[i] = dados.total_imposto_anual[i] - total;
    }        
    impresso(&dados);

    free(dados.abatimento);
    free (dados.imposto_mes);
    free(dados.renda_mensal);
    free(dados.ajuste);
    free(dados.total_imposto_anual);
    free(dados.renda_anual);
    return 0;
}