#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)

typedef struct{
	int chave, id, incremento;;
}Item;

//fila de prioridade
typedef struct{
	Item *v;
	int n, tamanho;
}FP;

typedef FP * p_fp;

//função que retorna um item com os parametros passados
Item creatItem(int id, int chave, int incremento){
    Item item;
    item.id = id;
    item.chave = chave;
    item.incremento = incremento;
    return item;
}

//função que troca o valor de duas variáveis
void troca(Item *a , Item *b){
	Item t = *a;
	*a = *b;
	*b = t;
}

//função que cria a fila de prioridades vazia com tamanho tam
p_fp criar_fila(int tam){
	p_fp fprio = malloc(sizeof(FP));
	fprio->v = malloc(tam * sizeof(Item));
	fprio->n = 0;
	fprio->tamanho = tam;
	return fprio;
}

void sobe_no_heap(p_fp fprio, int k){
	if(k>0 && fprio->v[PAI(k)].chave < fprio->v[k].chave){
		troca(&fprio->v[k], &fprio->v[PAI(k)]);
		sobe_no_heap(fprio, PAI(k));
	}
}

//função que insere ordenadamente pela prioridade
void insere(p_fp fprio, Item item){
    if(item.id != EOF){
        fprio->v[fprio->n] = item;
        fprio->n++;
        sobe_no_heap(fprio, fprio->n-1);
    }
}

void desce_no_heap(p_fp fprio, int k){
	int maior_filho;
	if (F_ESQ(k) < fprio->n){
		maior_filho = F_ESQ(k);
		if(F_DIR(k) < fprio->n && fprio->v[F_ESQ(k)].chave < fprio->v[F_DIR(k)].chave)
			maior_filho = F_DIR(k);
		if (fprio->v[k].chave < fprio->v[maior_filho].chave){
			troca(&fprio->v[k], &fprio->v[maior_filho]);
			desce_no_heap(fprio, maior_filho);
		}
	}
}

Item extrai_maximo(p_fp fprio){
	Item item = fprio->v[0];
	troca(&fprio->v[0], &fprio->v[fprio->n-1]);
	fprio->n--;
	desce_no_heap(fprio, 0);
	return item;
}

void aumentar_prioridade(p_fp fprio, int i){
    fprio->v[i].chave = fprio->v[i].chave + fprio->v[i].incremento;
    sobe_no_heap(fprio, i);
}

int main(){
    int k, m;
    int count = 1;
    scanf("%d %d", &k, &m);
    p_fp fprio = criar_fila(m);
    int id = 0, prio = 0, incremento = 0;
    while (getchar() != EOF)
    {
        scanf("%d %d %d", &id, &prio, &incremento);

        if(id == 0 && prio == 0 && incremento == 0 && getchar() != EOF){
            printf("\nTICK %d\n", count);
            count++;
            for (int i = 0; i < k && fprio->n > 0; i++)
            {
                Item aux = extrai_maximo(fprio);
                printf("%d  %d  %d\n", aux.id, aux.chave, aux.incremento);
            }
            if(fprio != NULL){
                for (int i = 0; i < fprio->n; i++)
                {
                    aumentar_prioridade(fprio, i);
                }
                
            }
        }
        
        else if(fprio->n < fprio->tamanho)
            insere(fprio, creatItem(id, prio, incremento));
    }
    
}