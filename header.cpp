#include "header.h"
#include <bits/stdc++.h>

//using namespace N;
using namespace std;
/*
===================================
ARQUIVOS
==================================
* Gerando o arquivo binario dado o CSV.
* Gerando o arquivo binario do indice de Id, dado o arquivo binario acima.


*/
void arquivos::gerarBinario(int tamanho)
{
	fstream arquivo;
	arquivo.open("arquivo.dat", ios::out | ios::app | ios::binary);
	if(arquivo.fail())
	{
		cout << "Erro ao abrir o arquivo binario" << endl;
		return;
	}
	FILE * file = fopen("Popular_Baby_Names.csv", "r");
    registro aux;
    registro* aux2 = new registro();
    int i=0;
    while (i<tamanho)
    {
        fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%d,%d", &aux.id, &aux.anoNascimento, aux2->sexo, aux2->etnia, aux2->nome, &aux.contador, &aux.rank);
		aux2->id = aux.id;
		aux2->anoNascimento = aux.anoNascimento;
		//aux2->sexo = aux.sexo;
		//aux2->etnia = aux.etnia;
		//aux2->nome = aux.nome;
		aux2->contador = aux.contador;      
		aux2->rank = aux.rank;
		cout << "aux2->id: " << aux2->id << ", aux2->anoNascimento: " << aux2->anoNascimento << ", aux2->sexo: " << aux2->sexo;
		cout << ", aux2->etnia: " << aux2->etnia << ", aux2->nome: " << aux2->nome << ", aux2->contador: " << aux2->contador;
		cout << ", aux2->rank: " << aux2->rank << endl; 
		arquivo.write((char*)aux2, sizeof(registro));  
        i++;
    }
    fclose(file);
    arquivo.close();
}

void arquivos::gerarBinarioIndiceId(int tamanho)
{
	streampos rrn;
	fstream arquivo;
	arquivo.open("arquivo.dat", ios::in | ios::binary);
	if(arquivo.fail())
	{
		cout << "Erro ao abrir o arquivo binario" << endl;
		return;
	}
	fstream indice;
	indice.open("indice_id.dat", ios::out | ios::app | ios::binary);
	if(indice.fail())
	{
		cout << "Erro ao abrir o arquivo de indice id";
		return;
	}
	registro* reg = new registro();
	id* indice_id = new id();
	arquivo.seekg(0, ios::beg);
	for(int i = 0; i < tamanho ;i++)
	{
		rrn = arquivo.tellg();
		arquivo.read((char*)reg, sizeof(registro));
		cout << "reg->id: " << reg->id << ", reg->anoNascimento: " << reg->anoNascimento << ", reg->sexo: " << reg->sexo;
		cout << ", reg->etnia: " << reg->etnia << ", reg->nome: " << reg->nome << ", reg->contador: " << reg->contador;
		cout << ", reg->rank: " << reg->rank << endl; 
		indice_id->id = reg->id;
		indice_id->rrn = rrn;
		cout << "id -> " << indice_id->id << " , rrn -> " << indice_id->rrn << endl;
		indice.write((char*)indice_id, sizeof(id));
		arquivo.seekg(sizeof(registro)*(i+1));
	}
	arquivo.close();
	indice.close();
}