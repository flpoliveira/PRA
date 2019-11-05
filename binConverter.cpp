#include <bits/stdc++.h>

using namespace std;

typedef struct{
  int id;
  int anoNascimento;
  string sexo;
  string etnia;
  string nome;
  int contador;
  int rank;
} Registro;

vector<Registro> registros;

int main()
{
	
	ifstream file ( "Popular_Baby_Names_Shufle.csv" ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	
	int pLinha = 0;
	int id, anoNascimento, contador, rank;
	string sexo, etnia, nome;
			
	string value;
	while ( file.good() )
	{
		if(pLinha == 0)
			pLinha++;
		else
		{
			

			getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			id = stoi(string( value, 1, value.length()-2 ));
			getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			anoNascimento = stoi(string( value, 1, value.length()-2 ));
			getline ( file, sexo , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			getline ( file, etnia , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			getline ( file, nome , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			contador = stoi(string( value, 1, value.length()-2 ));
			getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
			rank =stoi(string( value, 1, value.length()-2 ));

			cout << id << " - " << anoNascimento << " - " << sexo << " - " << etnia << " - " << nome << " - " << contador << " - " << rank << endl;
		}
	     
	}
	return 0;
}