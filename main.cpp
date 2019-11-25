#include "header.h"

#include <chrono> 
#define pb push_back
#define IND_ID 1

using namespace std::chrono; 

vector<Registro> regs;

int  buscaSequencial(int k, int indice)
{
	for(int i = 0; i < regs.size(); i++)
	{
		if(indice == IND_ID)
		{
			if(k == regs[i].id)
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
	int tamanho = 30, grauMinimo = 3;
	
	/*cout << "Digite o numero de regs que deseja trabalhar:" <<endl;
	cin >> tamanho;
	cout << "Digte o grau minimo da Arvore B:" << endl;
	cin >> grauMinimo;

	//Caso o numero de Registro seja superior a 10000 ou inferior a 0
	tamanho = tamanho > 10000 ? 10000 : tamanho;
	tamanho = tamanho < 0 ? 0 : tamanho; 
	
	//Caso o numero do grau minimo seja menor que 0
	grauMinimo = grauMinimo < 0 ? 0 : grauMinimo;

	
	
*/

	

	//Gerando os arquivos Binarios do CSV - ETAPA 1
	arquivo.gerarBinario(tamanho);
	arquivo.gerarBinarioIndiceId();
	arquivo.gerarBinarioIndiceAnoRank();




	//Gerando a arvore B em memória principal
	BTree p1(grauMinimo);
	BTree p2(grauMinimo);
	fstream indice, indice2;
	indice.open("indice_id.dat", ios::in | ios::binary);
	indice2.open("indice_anoRank.dat", ios::in | ios::binary);
	id * auxId = new id();
	anoRank * auxAnoRank = new anoRank();
	if(indice.fail())
	{
		cout << "Erro ao abrir o arquivo de indice id";
		return 1;
	}
	indice.seekg(0, ios::beg);
	
	while(1)
	{
		
		indice.read((char*)auxId, sizeof(id));
		if(indice.eof()) break;
		cout << auxId->id << " - " << auxId->rrn << endl;
		p1.insert(mp(auxId->id, auxId->rrn));
	}
	while(1)
	{
		indice2.read((char *)auxAnoRank, sizeof(anoRank));
		if(indice2.eof()) break;
		cout << auxAnoRank->anoRank << ", " << auxAnoRank->rrn << endl;
		p2.insert(mp(auxAnoRank->anoRank, auxAnoRank->rrn));
	}
	indice.close();
	indice2.close();
	fstream arq;
	arq.open("arquivo.dat", ios::in | ios::binary);
	if(arq.fail())
	{
		cout << "Erro ao abrir o arquivo.dat" << endl;
		return 1;
	}
	arq.seekg(sizeof(Cabecalho));
	while(!arq.eof())
	{
		Registro * reg = new Registro();
		arq.read((char*) reg, sizeof(Registro));
		regs.pb(*reg);
	}
	arq.close();
	
	
	
	auto start = high_resolution_clock::now(); 
	int resultado = p1.search(11000);
	
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
	resultado = buscaSequencial(11000, 1);
	stop = high_resolution_clock::now(); 

	if(resultado != -1)
	{
		cout << "Encontrado na busca sequencial:" << endl;
		cout << "\tID: " << regs[resultado].id << endl;
		cout << "\tNome: " << regs[resultado].nome << endl;
		cout << "\tAno de Nascimento: " << regs[resultado].anoNascimento << endl;
		cout << "\tSexo: " << regs[resultado].sexo << endl;
		cout << "\tEtnia: " << regs[resultado].etnia << endl;
		cout << "\tContador: " << regs[resultado].contador << endl;
		cout << "\tRank: " << regs[resultado].rank << endl;
		
	}
	else
		cout << "nao encontrado sequencial" << endl;

	duration = duration_cast<nanoseconds>(stop - start);
	cout << duration.count() << endl; 
	
	return 0;
}
