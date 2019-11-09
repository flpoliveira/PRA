#include <bits/stdc++.h>

using namespace std;

typedef struct{
  int id;
  int anoNascimento;
  char sexo[6];
  char etnia[100];
  char nome[100];
  int contador;
  int rank;
} Registro;

vector<Registro> registros;

int main()
{

	ifstream file ( "Popular_Baby_Names_Shufle.csv" ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/

	int id, anoNascimento, contador, rank;
	string sexo, etnia, nome;
	string value;
    //Tive que apagar a primeira linha do arquivo
	while ( file.good() )
	{

            Registro aux;
			getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
            if(strcmp (value.c_str(),"") == 0) break;
            id = stoi(value);
			getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			anoNascimento = stoi(value);
			getline ( file, sexo , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			getline ( file, etnia , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			getline ( file, nome , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			contador = stoi(value);
			getline ( file, value , '\n' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			rank = stoi(value);
            aux.id = id;
            aux.anoNascimento = anoNascimento;
            strcpy(aux.sexo, sexo.c_str());
            strcpy(aux.etnia, etnia.c_str());
            strcpy(aux.nome, nome.c_str()); 
            aux.contador = contador;
            aux.rank = rank;
            registros.push_back(aux);
			//cout << id << " - " << anoNascimento << " - " << sexo << " - " << etnia << " - " << nome << " - " << contador << " - " << rank << endl;

	}
    FILE *arq;
    arq = fopen ("Popular_Baby_Names_Shuffle.bin","ab");
    for(auto c : registros)
    {
        //cout << c.id << " - " << c.anoNascimento << " - " << c.sexo << " - " << c.etnia << " - " << c.nome << " - " << c.contador << " - " << c.rank << endl;
        if(fwrite(&c, sizeof(Registro),1,arq) !=1)
            cout << "Erro ao escrever o arquivo!!" << endl;
    }
    fclose(arq);

    arq = fopen ("Popular_Baby_Names_Shuffle.bin","rb");
    if(!arq) cout << "Erro ao abrir o arquivo" << endl;
    else cout << "Arquivo abriu perfeitamente" << endl;
    Registro r;
    while(fread(&r, sizeof(Registro), 1, arq))
    {
        cout << r.id << " - " << r.anoNascimento << " - " << r.sexo << " - " << r.etnia << " - " << r.nome << " - " << r.contador << " - " << r.rank << endl;
    }

    fclose(arq);
	return 0;
}
