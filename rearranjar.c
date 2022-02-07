#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *lista;
    int a;
    int b;
    int n;
}meus_dados;


meus_dados comando1(meus_dados *dados){ //inverter a ordem dos participantes a ate b

    int k_a, k_b;
    for (int i=0; dados-> n>= i; i++){
        if (dados->a == dados->lista[i]){
            k_a = i;
        }
        if (dados->b == dados->lista[i]){
            k_b = i;
        }
    }
    for (int i = 0; k_a + 2*i <= k_b; i++)
    {
        int sub = dados->lista[k_a+i];
        dados->lista[k_a+i] = dados->lista[k_b-i];
        dados->lista[k_b-i] = sub;
    }
    

    return *dados;
}

meus_dados comando2(meus_dados *dados){
    int temp, k_a;
    for (int i = 0; i < dados->n; i++){
        if (dados->lista[i] == dados->a){
            k_a = i;
        }
    }
    int k = k_a;
    while (dados->lista[k] != dados->b)
    {
        temp = dados->lista[k+1];
        dados->lista[k] = temp;
        k++;
    }

    dados->lista[k] = dados->a;

    return *dados;
}


int main() {

    meus_dados dados;

    scanf("%i", &dados.n);    

    dados.lista = malloc(dados.n * sizeof(int));

    
    for(int i=0; i < dados.n; i++){
        dados.lista[i] = i+1;
    }

    int op, tipo; /*numero de operações e tipo de comando*/

    scanf("%i", &op);
    for (int i=0; i < op; i++){
        scanf("%i %i %i", &tipo, &dados.a, &dados.b);

        if (tipo == 1){
            comando1(&dados);
        }
        if (tipo == 2){
            comando2(&dados);
        }
    }
    for (int i = 0; i<dados.n; i++){
        printf("%i ", dados.lista[i]);
    }
    return 0;
}