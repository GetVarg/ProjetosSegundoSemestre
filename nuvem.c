#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define WORD 50

typedef struct no
{
    char word[WORD];
    int dado;
    struct no * proximo;
}No;

typedef No * p_no;

typedef struct
{
    p_no vetor;
}Hash;

typedef Hash * p_hash;

No inserir_lista(No elemento, char *chave){
    if(elemento.word == NULL){
        strcpy(elemento.word, chave);
        elemento.dado = 1;
    }
    else
        elemento.dado++;
    return elemento;
}

int hash(char *chave, int num_palavras){
	int i, n = 0;
	for(i = 0; i < strlen(chave); i++)
		n = (256 * n + chave[i]) % num_palavras;
	return n;
}

void inserir(p_hash t, char *chave, int num_palavras){
	int n = hash(chave, num_palavras);
	t->vetor[n] = inserir_lista(t->vetor[n], chave);
}

p_hash creat_hash_stop(){
    p_hash t;
    t = malloc(sizeof(Hash));
    t->vetor = malloc(sizeof(char[WORD]) * 127);
    char stop_word[][WORD] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};
    for (int i = 0; i < 127; i++)
    {
        int n = hash(stop_word[i], 127);
        t->vetor[n] = inserir_lista(t->vetor[n], stop_word[i]);
    }
    return t;
}

int is_stop(char word[WORD], p_hash tabela_stop){
    int n = hash(word, 127);
    if(strcmp(tabela_stop->vetor[n].word, word))
        return 0;
    else
        return 1;
}

int main(){
    int num_word, num_stop;
    scanf("%d", &num_word);
    scanf("%d" , &num_stop);
    
    p_hash tabela;
    tabela = malloc(sizeof(Hash));
    tabela->vetor = malloc(sizeof(No) * num_word);

    p_hash tabela_stop = creat_hash_stop();
    int count = 0;
    while (getchar() != EOF)
    {
        char word[WORD];
        scanf("%s", word);
        if(!is_stop(word, tabela_stop)){
            count++;
            inserir(tabela, word, num_word);
        }
    }
    for (int i = 0; i < num_word; i++)
    {
        printf("%s  %d\n", tabela->vetor[i].word, tabela->vetor[i].dado);
    }
    


    return 0;
}