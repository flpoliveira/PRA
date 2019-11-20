// my_class.h
#ifndef HEADER_H // include guard
#define HEADER_H

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



class arquivos
{
	public:
    	void gerarBinario(int tamanho);
		void gerarBinarioIndiceId(int tamanho);
};

#endif /* MY_CLASS_H */