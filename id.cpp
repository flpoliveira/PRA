#include <bits/stdc++.h>

using namespace std;
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
	int rrn;
}id;
int main()
{
	streampos rrn;
	fstream arquivo;
	arquivo.open("arquivo", ios::in | ios::binary);
	if(arquivo.fail())
	{
		cout << "Erro ao abrir o arquivo binario" << endl;
		return 1;
	}
	fstream indice;
	indice.open("indice_id.bin", ios::out | ios::app | ios::binary);
	if(indice.fail())
	{
		cout << "Erro ao abrir o arquivo de indice id";
		return 1;
	}
	registro* reg = new registro();
	id* indice_id = new id();
	arquivo.ssekg(0, ios::beg);
	for(int i = 0; i < 10000;i++)
	{
		rrn = binario.tellg();
		binario.read((char*)reg, sizeof(registro));
		indice_id->id = reg->id;
		indice_id->rrn = rrn;
		indice.write((char*)indice_id, sizeof(id));
		arquivo.seekg(sizeof(registro)*(i+1));
	}
	arquivo.close();
	indice.close();

	return 0;
}