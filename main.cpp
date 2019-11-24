#include "header.h"

#include <chrono> 
#define pb push_back
#define IND_ID 1

using namespace std::chrono; 

vector<registro> registros;

int  buscaSequencial(int k, int indice)
{
	for(int i = 0; i < registros.size(); i++)
	{
		if(indice == IND_ID)
		{
			if(k == registros[i].id)
			{
				return i;
			}
		}
	}
	return -1;
}
void menu()
{
	cout << "============== MENU ==============" << endl;
	cout << "1 - Busca por ID" << endl;
	cout << "0 - Sair " << endl;
}
int main()
{
	arquivos arquivo;
	int tamanho = 10000, grauMinimo = 3;
	/*
	cout << "Digite o numero de registros que deseja trabalhar:" <<endl;
	cin >> tamanho;
	cout << "Digte o grau minimo da Arvore B:" << endl;
	cin >> grauMinimo;

	//Caso o numero de registro seja superior a 10000 ou inferior a 0
	tamanho = tamanho > 10000 ? 10000 : tamanho;
	tamanho = tamanho < 0 ? 0 : tamanho; 
	
	//Caso o numero do grau minimo seja menor que 0
	grauMinimo = grauMinimo < 0 ? 0 : grauMinimo;
	
	*/


	

	//Gerando os arquivos Binarios do CSV - ETAPA 1
	arquivo.gerarBinario(tamanho);
	arquivo.gerarBinarioIndiceId(tamanho);

	//Gerando a arvore B em memória principal
	BTree p1(grauMinimo);

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
		//cout << cn->id << " - " << cn->rrn << endl;
		p1.insert(mp(cn->id, cn->rrn));
		indice.seekg(sizeof(id)*(i+1));
	}
	indice.close();
	fstream arq;
	arq.open("arquivo.dat", ios::in | ios::binary);
	if(arq.fail())
	{
		cout << "Erro ao abrir o arquivo.dat" << endl;
		return 1;
	}
	arq.seekg(0, ios::beg);
	for(int i  = 0; i < tamanho; i++)
	{
		registro * reg = new registro();
		arq.read((char*) reg, sizeof(registro));
		registros.pb(*reg);
		arq.seekg(sizeof(registro)*(i+1));
	}
	arq.close();
	
	
	
	auto start = high_resolution_clock::now(); 
	int resultado = p1.search(7000);
	
	auto stop = high_resolution_clock::now(); 
	
	if(resultado != -1)
	{
		cout << "Encontrado na TreeB" << endl;
		arquivo.printarArquivoBinario(resultado);
	}
	else
		cout << "Não encontrado TreeB" << endl;
	auto duration = duration_cast<nanoseconds>(stop - start); 
	// To get the value of duration use the count() 
	// member function on the duration object 
	cout << duration.count() << endl; 
	start = high_resolution_clock::now(); 
	 resultado = buscaSequencial(7500, 1);
	stop = high_resolution_clock::now(); 

	if(resultado != -1)
	{
		cout << "Encontrado na busca sequencial:" << endl;
		cout << "\tID: " << registros[resultado].id << endl;
		cout << "\tNome: " << registros[resultado].nome << endl;
		cout << "\tAno de Nascimento: " << registros[resultado].anoNascimento << endl;
		cout << "\tSexo: " << registros[resultado].sexo << endl;
		cout << "\tEtnia: " << registros[resultado].etnia << endl;
		cout << "\tContador: " << registros[resultado].contador << endl;
		cout << "\tRank: " << registros[resultado].rank << endl;
		
	}
	else
		cout << "nao encontrado sequencial" << endl;

	duration = duration_cast<nanoseconds>(stop - start);
	cout << duration.count() << endl; 

	return 0;
}
