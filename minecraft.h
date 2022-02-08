#include <stdio.h>
#include <stdlib.h>
#ifndef _MINECRAFT
#define _MINECRAFT 

typedef struct {
    int ***mundo;
    int M;
    int *qtdDiamante;
    int *qtdOuro;
    int *qtdFerro;
    int *qtdBlocos;
    // você é livre pra definir o bloco aqui
} Bloco;

/**
 * Calcula a altitude da posição (x,z) dada uma 
 * semente s
**/
int calcularAltitude(int s, int x, int z);

void tipo_bloco(int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos, Bloco ***info, int x, int y, int z);

/**
 * Calcula o bloco da posição (x,y,z) dada uma 
 * semente s e altitude h
**/
int calcularBloco(int s, int x, int y, int z, int h);

/**
 * Libera a memória de uma matriz de int com m linhas.
**/
void liberaMatriz(int m, int **matriz);


/**
 * Libera a memória de uma matriz 3d de Blocos com m linhas e n colunas.
**/
void liberaMundo(int m, Bloco ***matriz);

// é obrigatório implementar os protótipos seguintes

/**
 * Cria uma matriz de altitudes representando
 * o relevo de um mundo.
 **/
int **calcularAltitudes(int m, int n, int seed);

/**
 * Cria um novo mundo representado por uma matriz
 * de blocos alocada dinamicamente.
 **/
Bloco ***criarMundo(int m, int n, int **altitudes, int seed);

/**
 * Explora o mapa de um mundo e devolve o tempo
 * necessário para minerar todo ele. Além disso,
 * devolve a quantidade de alguns minérios de
 * interesse.
 **/
double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco,
    int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos);

// você pode adicionar e implementar outros protótipos
// que forem necessários

#endif