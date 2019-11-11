#include <bits/stdc++.h>

#define DEBUG 1

using namespace std;


struct registro{
    int id;
    int anoNascimento;
    char sexo[7];
    char etnia[100];
    char nome[100];
    int contador;
    int rank;
};
struct cabecalho{
    int topo;
};
struct removido{
    char caracter;
    int proximoPilha;
};
int posicaoReal(int rrn);
int main(){
    FILE *arq;
    int opcao=1;
    int rrn =0;
    int topo;
    struct registro r;
    arq = fopen("arquivo","rb");
    struct cabecalho cab;
    struct removido auxRemover;
    if(arq==NULL){
        arq = fopen("arquivo","ab");
        cab.topo=-1;
        fwrite(&cab, sizeof(struct cabecalho),1,arq);
        FILE * file = fopen("Popular_Baby_Names.csv", "r");
        //ifstream file ( "Popular_Baby_Names_Shufle.csv" ); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
        //Tive que apagar a primeira linha do arquivo
        struct registro aux;
        int i=0;
        while (i<10040)
        {
            fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%d,%d", &aux.id, &aux.anoNascimento, aux.sexo, aux.etnia, aux.nome, &aux.contador, &aux.rank);
            //string sexo, etnia, nome;
            //string value;


                // getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                // if(strcmp (value.c_str(),"") == 0) break;
                // aux.id = stoi(value);
                // getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                // aux.anoNascimento = stoi(value);
                // getline ( file, sexo , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                // getline ( file, etnia , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                // getline ( file, nome , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                // getline ( file, value , ',' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                // aux.contador = stoi(value);
                // getline ( file, value , '\n' ); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/
                // aux.rank = stoi(value);
                // strcpy(aux.sexo, sexo.c_str());
                // strcpy(aux.etnia, etnia.c_str());
                // strcpy(aux.nome, nome.c_str());
                fwrite(&aux, sizeof(struct registro), 1, arq);
                //cout << id << " - " << anoNascimento << " - " << sexo << " - " << etnia << " - " << nome << " - " << contador << " - " << rank << endl;
                i++;
        }
    }
    fclose(arq);

    while(opcao!=0){
        printf("(1) - Inserir pessoa\n");
        printf("(2) - Consultar todos\n");
        printf("(3) - Consultar nome por RRN\n");
        printf("(4) - Remover nome por RRN\n");
        printf("(5) - Limpeza do Arquivo\n");
        printf("(0) - Sair\n");
        scanf("%d", &opcao);
        /*if(opcao == 1){
            printf(">> Digite 0 em qualquer passo para sair\n");
            //fseek(arq, sizeof(struct cabecalho), SEEK_SET);
                while(1){
                    arq = fopen ("arquivo","rb");
                    fread(&cab, sizeof(struct cabecalho), 1, arq);
                    fclose(arq);
                    struct registro r;
                    int id;
                    int anoNascimento;
                    char sexo[6];
                    char etnia[100];
                    char nome[100];
                    int contador;
                    int rank;
                    printf("> Digite o nome:\n");
                    scanf("%s", r.nome);
                    if(strcmp(r.nome, "0") == 0) break;
                    printf("> Digite o Ano de Nascimento:\n");
                    scanf("%d", r.anoNascimento);
                    if(strcmp(r.anoNascimento, "0") == 0) break;
                    printf("> Digite o sexo:\n");
                    scanf("%s", r.sexo);
                    if(strcmp(r.sexo, "0") == 0) break;
                    printf("> Digite a valor do produto:\n");
                    scanf("%lf", &r.valor);
                    if(r.valor == 0) break;
                    if(cab.topo == -1){
                        arq = fopen ("arquivo","ab");
                        if(fwrite(&r, sizeof(struct registro), 1,arq) !=1)
                            printf("!! Erro ao escrever o arquivo\n");
                        else{
                            printf(">> Registro adicionado RRN [%d] \n",rrn);
                            rrn++;
                        }
                        fclose(arq);
                    }else{

                        arq = fopen ("arquivo","rb+");
                        fseek(arq, sizeof(struct cabecalho) + sizeof(struct registro) * cab.topo, SEEK_SET);
                        fread(&auxRemover, sizeof(struct removido),1 ,arq);
                        fseek(arq, (sizeof(struct cabecalho) + sizeof(struct registro) * cab.topo), SEEK_SET);
                        fwrite(&r, sizeof(struct registro), 1,arq);
                        cab.topo = auxRemover.proximoPilha;
                        rewind(arq);
                        fwrite(&cab, sizeof(struct cabecalho),1,arq);
                        fclose(arq);
                    }
            }
        }else */if(opcao == 2){
            arq = fopen ("arquivo","rb");
            if(!arq){
                printf("!! Erro ao abrir o arquivo\n");
                break;
            }
            int countItens = 0;
            int id = -1;
            fseek(arq, sizeof(struct cabecalho), SEEK_SET);
            while(fread(&auxRemover, sizeof(struct removido), 1, arq)){
                if(auxRemover.caracter != '*'){

                    id++;


                    fseek(arq, (sizeof(struct cabecalho) + sizeof(struct registro) * countItens), SEEK_SET);
                    fread(&r, sizeof(struct registro), 1, arq);
                    printf("------RRN - %d------\n", id);
                    printf("Id: %d\n", r.id);
                    printf("Ano de Nascimento: %d\n", r.anoNascimento);
                    printf("Sexo: %s\n", r.sexo);
                    printf("Etnia: %s\n", r.etnia);
                    printf("Nome %s\n", r.nome);
                    printf("Contador: %d\n", r.contador);
                    printf("Rank do Ano: %d\n", r.rank);
                //    cout<<r.id<<","<<r.anoNascimento<<","<<r.sexo<<","<<r.etnia<<","<<r.nome<<","<<r.contador<<","<<r.rank<<endl;
                }else{
                    fseek(arq, (sizeof(struct cabecalho) + sizeof(struct registro) * (countItens +1)), SEEK_SET);
                }
                countItens++;
            }
            if(id == -1)
                printf("Nao existe produtos na lista\n");
            else
                printf("----------------------\n");
            fclose(arq);
       }else if(opcao == 3){
            int rrnPesquisa;
            arq = fopen ("arquivo","rb");
            if(!arq){
                printf("!! Erro ao abrir o arquivo\n");
                break;
            }
            printf(">> Digite o RRN do produto:\n");
            scanf("%d",&rrnPesquisa);
            rrnPesquisa = posicaoReal(rrnPesquisa);
            if(rrnPesquisa == -1)
                printf("Nome nao existe\n");
            else{
                fseek(arq, rrnPesquisa*sizeof(struct registro)+sizeof(struct cabecalho), SEEK_SET);
                fread(&r, sizeof(struct registro), 1, arq);
                printf("----------------------\n");
                printf("Id: %d\n", r.id);
                printf("Ano de Nascimento: %d\n", r.anoNascimento);
                printf("Sexo: %s\n", r.sexo);
                printf("Etnia: %s\n", r.etnia);
                printf("Nome %s\n", r.nome);
                printf("Contador: %d\n", r.contador);
                printf("Rank do Ano: %d\n", r.rank);
                printf("----------------------\n");
            }
            fclose(arq);
        }else if(opcao == 4){

            int rrnPesquisa;
            arq = fopen ("arquivo","rb+");
            if(!arq){
                printf("!! Erro ao abrir o arquivo\n");
                break;
            }
            printf(">> Digite o RRN da pessoa:\n");
            scanf("%d",&rrnPesquisa);
            rrnPesquisa = posicaoReal(rrnPesquisa);
            printf("%d\n", rrnPesquisa);
            fread(&cab, sizeof(struct cabecalho), 1, arq);
            rewind(arq);
            auxRemover.proximoPilha = cab.topo;
            auxRemover.caracter = '*';
            cab.topo = rrnPesquisa;
            fwrite(&cab, sizeof(struct cabecalho),1,arq);
            fseek(arq, rrnPesquisa*sizeof(struct registro)+sizeof(struct cabecalho), SEEK_SET);
            fwrite(&auxRemover, sizeof(struct removido),1,arq);
            fclose(arq);

        }else if(opcao == 5){
            rename("arquivo","buffer");
            FILE *buffer;
            buffer = fopen("buffer","rb");
            arq = fopen("arquivo", "ab+");
            cab.topo=-1;
            fwrite(&cab, sizeof(struct cabecalho),1,arq);
            int countItens = 0;
            fseek(buffer, sizeof(struct cabecalho), SEEK_SET);
            while(fread(&auxRemover, sizeof(struct removido), 1, buffer)){
                if(auxRemover.caracter != '*'){
                    fseek(buffer, (sizeof(struct cabecalho) + sizeof(struct registro) * countItens), SEEK_SET);
                    fread(&r, sizeof(struct registro), 1, buffer);
                    fwrite(&r, sizeof(struct registro), 1, arq);
                }else{
                    fseek(buffer, (sizeof(struct cabecalho) + sizeof(struct registro) * (countItens +1)), SEEK_SET);
                }
                countItens++;
            }
            fclose(arq);
            fclose(buffer);
            remove("buffer");
            printf("Arquivo limpo\n");
        }
    }
    return 0;
}
int posicaoReal(int rrn){
    FILE *arq;
    int count = 0;
    int countItens = 0;
    struct removido auxRemover;
    arq = fopen ("arquivo","rb");
    fseek(arq, sizeof(struct cabecalho), SEEK_SET);
    while(fread(&auxRemover, sizeof(struct removido), 1, arq)){
        if(auxRemover.caracter != '*'){
            if(count==rrn)
                return countItens;
            count++;
        }
        countItens++;
        fseek(arq, (sizeof(struct cabecalho) + sizeof(struct registro) * (countItens)), SEEK_SET);
    }
    return -1;
}
