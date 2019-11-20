#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct registro
{
    int id;
    int anoNascimento;
    char sexo[7];
    char etnia[100];
    char nome[100];
    int contador;
    int rank;
}registro;

typedef struct id
{
	int id;
	long long rrn;
}id;

void gerarBinario(int tamanho);
void gerarBinarioIndiceId(int tamanho);

#endif