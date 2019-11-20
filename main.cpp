#include "header.h"

int main()
{
	arquivos arquivo;
	int tamanho = 10000;
	arquivo.gerarBinario(tamanho);
	arquivo.gerarBinarioIndiceId(tamanho);
	BTree p1(3);
	fstream indice;
	indice.open("indice_id.dat", ios::in | ios::binary);
	id * cn = new id();
	if(indice.fail())
	{
		cout << "Erro ao abrir o arquivo de indice id";
		return 1;
	}
	indice.seekg(0, ios::beg);
	for(int i = 0; i < tamanho ;i++)
	{
		indice.read((char*)cn, sizeof(id));
		cout << cn->id << " - " << cn->rrn << endl;
		p1.insert(mp(cn->id, cn->rrn));
		indice.seekg(sizeof(id)*(i+1));
	}
	indice.close();
	p1.traverse();
	cout << endl;
	return 0;
}
