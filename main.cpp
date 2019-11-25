#include "header.h"

#include <chrono>
#define pb push_back
#define MAX 10000
#define IND_ID 1
#define IND_ANO_RANK 2
#define GRAUMINIMO 3

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
		else if(indice == IND_ANO_RANK)
		{
			if(k == stoi(to_string(regs[i].anoNascimento) + to_string(regs[i].rank)))
			{
				return i;
			}
		}
	}
	return -1;
}
void menu()
{
	cout << "============== ETAPA 2 ==============" << endl;
	cout << "1 - Insercao de registro" << endl;
	cout << "2 - Remocao de registro" << endl;
	cout << "3 - Limpeza do arquivo" << endl;
	cout << "============== ETAPA 3 ==============" << endl;
	cout << "4 - Busca por ID" << endl;
	cout << "5 - Busca por Ano e Ranking" << endl;
	cout << "0 - Sair " << endl;
}
int main()
{
	arquivos arquivo;
	//ETAPA 1 , GERACAO DO ARQUIVO BINARIO
	arquivo.gerarBinario(MAX);


	//Menu

	int opcao = -1;
	while(opcao != 0)
	{
		menu();
		cin >> opcao;
		if(opcao == 1)
		{
			Registro * novo = new Registro();
			cout << "Escreva o id:" << endl;
			cin >> novo->id;
			cout << "Digite o ano de nascimento:" << endl;
			cin >> novo->anoNascimento;
			cout << "Digite 1 para o sexo FEMININO e 2 para o sexo MASCULINO" << endl;
			int aux; cin >> aux;
			if(aux == 1) strcpy(novo->sexo, "FEMALE");
			else strcpy(novo->sexo, "MALE");
			cout << "Digite a etnia:" << endl;
			cin >> novo->etnia;
			cout << "Digite o nome:" << endl;
			cin >> novo->nome;
			cout << "Digite a quantidade de pessoas com este nome, neste ano:" << endl;
			cin >> novo->contador;
			cout << "Digite o ranking deste nome neste ano:" << endl;
			cin >> novo->rank;
			arquivo.inserirArquivoBinario(novo);
			//arquivo.lerArquivoBinario();
		}
		else if(opcao == 2)
		{
			int rrn = -1;
			cout << "Diga o rrn que deseja remover:" << endl;
			cin >> rrn;
			if(rrn >= sizeof(Cabecalho) && rrn <= (sizeof(Registro)*MAX+sizeof(Cabecalho)))
				arquivo.removerArquivoBinario(rrn);
		}
		else if(opcao == 3)
		{
			arquivo.limparArquivo();
		}
		else
		{
			arquivo.gerarBinarioIndiceId();
			arquivo.gerarBinarioIndiceAnoRank();
			regs.clear();

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

			if(opcao == 4)
			{
				fstream indice;
				indice.open("indice_id.dat", ios::in | ios::binary);
				if(indice.fail())
				{
					cout << "Erro ao abrir o arquivo de indice id";
					return 1;
				}
				BTree p1(GRAUMINIMO);
				indice.seekg(0, ios::beg);
				id * auxId = new id();
				while(1)
				{

					indice.read((char*)auxId, sizeof(id));
					if(indice.eof()) break;
					p1.insert(mp(auxId->id, auxId->rrn));
				}
				indice.close();
				int id;
				cout << "Digite o id que deseja buscar:"<<endl;
				cin >> id;


				auto start = high_resolution_clock::now();
				int resultado = p1.search(id);

				auto stop = high_resolution_clock::now();

				if(resultado != -1)
				{
					cout << "Encontrado na TreeB , RRN: "<< resultado << endl;
					arquivo.printarArquivoBinario(resultado);
				}
				else
					cout << "Nao encontrado na TreeB" << endl;

				auto duration = duration_cast<nanoseconds>(stop - start);
				// To get the value of duration use the count()
				// member function on the duration object
				cout << "Tempo de busca: "<< duration.count()<<" nanosegundos." << endl;
				start = high_resolution_clock::now();
				resultado = buscaSequencial(id, IND_ID);
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
					cout << "Nao encontrado na busca sequencial" << endl;

				duration = duration_cast<nanoseconds>(stop - start);
				cout << "Tempo de busca: "<< duration.count()<<" nanosegundos." << endl;

			}
			if(opcao == 5)
			{
				fstream indice;
				indice.open("indice_anoRank.dat", ios::in | ios::binary);
				if(indice.fail())
				{
					cout << "Erro ao abrir o arquivo de indice id";
					return 1;
				}
				BTree p1(GRAUMINIMO);
				indice.seekg(0, ios::beg);
				anoRank * auxAnoRank = new anoRank();
				while(1)
				{

					indice.read((char*)auxAnoRank, sizeof(anoRank));
					if(indice.eof()) break;
					p1.insert(mp(auxAnoRank->anoRank, auxAnoRank->rrn));
				}
				indice.close();

				int ano, ranking;
				cout << "Digite o ano que deseja buscar:"<<endl;
				cin >> ano;
				cout << "Digite o ranking que deseja buscar:" <<endl;
				cin >> ranking;
				string auxiliar;
				if(!WINDOWS)
				{
					auxiliar = to_string(ano) + to_string(ranking);
					int anoRanking = stoi(auxiliar);

					auto start = high_resolution_clock::now();
					int resultado = p1.search(anoRanking);

					auto stop = high_resolution_clock::now();

					if(resultado != -1)
					{
						cout << "Encontrado na TreeB" << endl;
						arquivo.printarArquivoBinario(resultado);
					}
					else
						cout << "Nao encontrado na TreeB" << endl;
					auto duration = duration_cast<nanoseconds>(stop - start);
					cout << "Tempo de busca: "<< duration.count()<<" nanosegundos." << endl;

					start = high_resolution_clock::now();
					resultado = buscaSequencial(anoRanking, IND_ANO_RANK);
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
						cout << "Nao encontrado na busca sequencial" << endl;

					duration = duration_cast<nanoseconds>(stop - start);
					cout << "Tempo de busca: "<< duration.count()<<" nanosegundos." << endl;
				}

			}
		}

	}







	return 0;
}
