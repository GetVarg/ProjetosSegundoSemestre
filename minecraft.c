#include "minecraft.h"
//m = x, y = y, n = z
//relevo[x][z]
//mundo[]

int calcularaltitude(int s, int x, int z){

    int h_1 = (s*(202 + x + z) + 12345 + x + z);
    return h_1%256;
}

void liberaMatriz(int m, int **matriz){
    for (int i = 0; i < m; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
    
}

void liberaMundo(int m, Bloco ***matriz){
    for (int i = 0; i < m; i++)
    {
        for (int k = 0; k < 256; k++)
        {
            free(matriz[i][k]);
        }
        free(matriz[i]);
    }
    free(matriz);
}

int calcularBloco(int s, int x, int y, int z, int h){
    Bloco bloco;
    if (y > h)
    {
        bloco.M = 21;
    }
    else
    {
        int j = (s*(202 + x + y + z) + x + y + z);
        bloco.M = j%33;
    }
    return bloco.M;
}

int **calcularAltitudes(int m, int n, int seed){

    int **relevo;
    
    relevo = (int **)malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
    {
        relevo[i] = (int *)malloc(sizeof(int)*n);
    }
    
    for (int j = 0; j < m; j++)
    {
        for (int k = 0; k < n; k++)
        {
            relevo[j][k] = calcularaltitude(seed, j, k);
        }
        
    }
    return relevo;
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed){
    Bloco ***mundo;
    mundo = malloc(sizeof(Bloco **)*m);
    for (int i = 0; i < m; i++)
    {
        mundo[i] = malloc(sizeof(Bloco *)*256);
        for (int k = 0; k < 256; k++)
        {
            mundo[i][k] = malloc(sizeof(Bloco)*n);
        }
    }

    for (int x = 0; x < m; x++)
    {
        for (int z = 0; z < n; z++)
        {
            for (int y = 0; y <= altitudes[x][z]; y++)
            {
                mundo[x][y][z].M = calcularBloco(seed, x, y, z, altitudes[x][z]);
            }
            
        }

    }
    return mundo;
}

void tipo_bloco(int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos, Bloco ***info, int x, int y, int z){
    if (info[x][y][z].M == 0)
    {
        *qtdDiamante = *qtdDiamante + 1;
        *qtdBlocos = *qtdBlocos + 1;
    }
    
    if (info[x][y][z].M == 1 || info[x][y][z].M == 2)
    {
        *qtdOuro = *qtdOuro + 1;
        *qtdBlocos = *qtdBlocos + 1;
    }
    if (info[x][y][z].M >= 3 && info[x][y][z].M <= 5)
    {
        *qtdFerro = *qtdFerro + 1;
        *qtdBlocos = *qtdBlocos + 1;
    }
    if (info[x][y][z].M >= 6 && info[x][y][z].M <= 20)
    {
        *qtdBlocos = *qtdBlocos + 1;
    }
}

double explorarMundo (Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, 
int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos){

    for (int x = 0; x < m; x++)
    {
        for (int z=0; z<n; z++)
        {
            for (int y = 0; y <= altitudes[x][z]; y++)
            {
                if (y > altitudes[x][z])
                {
                    break;
                }
                else
                {
                    tipo_bloco(qtdDiamante, qtdOuro, qtdFerro, qtdBlocos, mundo, x, y, z);
                }
                
            }
            
        }
    }

    return tempoPorBloco*(*qtdBlocos);
}

int main(){
    Bloco ***mundo;
    mundo = NULL;

    int m, n, s;
    int qtdDiamante = 0;
    int qtdOuro = 0;
    int qtdFerro = 0;
    int qtdBlocos = 0;
    float temp;
    
    scanf("%d %d", &m, &n);
    scanf("%d", &s);
    scanf("%f", &temp);

    int **altitudes;
    altitudes = calcularAltitudes(m, n, s);
    mundo = criarMundo(m, n, altitudes, s);
    double res = explorarMundo(mundo, m, n, altitudes, temp, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);
    printf("Total de Blocos: %d\n", qtdBlocos);
    printf("Tempo total: %.2fs\n", res);
    printf("Diamantes: %d\n", qtdDiamante);
    printf("Ouros: %d\n", qtdOuro);
    printf("Ferros: %d\n", qtdFerro);
    liberaMatriz(m, altitudes);
    liberaMundo(m, mundo);
    return 0;
}