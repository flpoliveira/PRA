#include "header.h"


//using namespace N;

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
	arquivo.open("arquivo.dat", ios::out | ios::trunc |ios::binary);
	if(arquivo.fail())
	{
		cout << "Erro ao abrir o arquivo binario" << endl;
		return;
	}
	FILE * file = fopen("Popular_Baby_Names.csv", "r");

    //Declaração do cabeçalho para remoção lógica
    Cabecalho * cab = new Cabecalho();
    cab->topo = -1;
    arquivo.write((char *)cab, sizeof(Cabecalho));

    Registro* aux = new Registro();

    int i=0;
    while (i<tamanho)
    {
        fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%d,%d", &aux->id, &aux->anoNascimento, aux->sexo, aux->etnia, aux->nome, &aux->contador, &aux->rank);
		 
        if(DEBUG)
        {
            cout << "aux->id: " << aux->id << ", aux->anoNascimento: " << aux->anoNascimento << ", aux->sexo: " << aux->sexo;
            cout << ", aux->etnia: " << aux->etnia << ", aux->nome: " << aux->nome << ", aux->contador: " << aux->contador;
            cout << ", aux->rank: " << aux->rank << endl;
        }
        
		arquivo.write((char*)aux, sizeof(Registro));
        i++;
    }
    fclose(file);
    arquivo.close();
}

void arquivos::gerarBinarioIndiceId()
{
	streampos rrn;
	fstream arquivo;
	arquivo.open("arquivo.dat", ios::in | ios::binary);
	if(arquivo.fail() && DEBUG)
	{
		cout << "Erro ao abrir o arquivo binario" << endl;
		return;
	}
	fstream indice;
	indice.open("indice_id.dat", ios::out | ios::binary);
	if(indice.fail() && DEBUG)
	{
		cout << "Erro ao abrir o arquivo de indice id";
		return;
	}
	Registro* reg = new Registro();
	id* indice_id = new id();
	arquivo.seekg(sizeof(Cabecalho));
    
    Removido * r = new Removido();
	while(1)
    {
       rrn = arquivo.tellg();
       arquivo.read((char *) r, sizeof(Removido));
       if(arquivo.eof()) break;
       if(r->caracter != '*')
       {

            arquivo.seekg(rrn);
            arquivo.read((char*)reg, sizeof(Registro));    
            
            if(DEBUG )
            {
                cout << "reg->id: " << reg->id << ", reg->anoNascimento: " << reg->anoNascimento << ", reg->sexo: " << reg->sexo;
                cout << ", reg->etnia: " << reg->etnia << ", reg->nome: " << reg->nome << ", reg->contador: " << reg->contador;
                cout << ", reg->rank: " << reg->rank << endl;
            }
            
            indice_id->id = reg->id;
            indice_id->rrn = rrn;

            if(DEBUG)
              cout << "id -> " << indice_id->id << " , rrn -> " << indice_id->rrn << endl;

            indice.write((char*)indice_id, sizeof(id));
       }
       else
            arquivo.seekg(sizeof(Registro) + rrn);

	  
	} 
	arquivo.close();
	indice.close();
}
void arquivos::inserirIndiceId(int rrn)
{
    fstream arquivo, indice;
    arquivo.open("arquivo.dat", ios::in |  ios::app | ios::binary);
    indice.open("indice_id.dat", ios::app | ios::binary);
    if(arquivo.fail() || indice.fail())
    {
        cout << "Erro ao abrir o arquivo na atualizacao do indice" << endl; 
        return;
    }
    Registro * reg = new Registro();
    arquivo.seekg(rrn);
    arquivo.read((char *) reg, sizeof(Registro));
    id * indice_id = new id();
    indice_id->id = reg->id;
    indice_id->rrn = rrn;
    indice.write((char *) indice_id, sizeof(id));
    arquivo.close();
    indice.close();

}
int arquivos::inserirArquivoBinario(Registro * reg)
{
    streampos rrn;
    fstream arquivo;
    arquivo.open("arquivo.dat", ios::in |  ios::out | ios::binary);
    Cabecalho * cab = new Cabecalho();

    if(arquivo.fail() && DEBUG)
    {
        cout << "Erro ao abrir o arquivo na insercao do arquivo binario" << endl;
        return -1;
    }

    arquivo.seekg(0, ios::beg);
    arquivo.read((char *) cab, sizeof(Cabecalho));
    
    if(cab->topo == -1)
    {
        arquivo.seekg(0, ios_base::end);
        rrn = arquivo.tellg();
        arquivo.write((char *)reg, sizeof(Registro));

    }
    else
    {
        arquivo.seekg(cab->topo);
        Removido * r = new Removido();
        arquivo.read((char *) r, sizeof(Removido));
        arquivo.seekp(cab->topo);
        arquivo.write((char *) reg, sizeof(Registro));
        cab->topo = r->proximoPilha;
        arquivo.seekp(0, ios::beg);
        arquivo.write((char *) cab, sizeof(Cabecalho));

    }
    
    arquivo.close();
    return rrn;
}
void arquivos::removerArquivoBinario(int rrn)
{
    fstream arquivo;
    arquivo.open("arquivo.dat", ios::in | ios::out  | ios::binary);
    if(arquivo.fail())
    {
        cout << "Erro ao abrir o arquivo na remocao do arquivo binario" <<endl;
        return;
    }
    Cabecalho * cab = new Cabecalho();
    arquivo.seekg(0, ios::beg);
    arquivo.read((char *) cab, sizeof(Cabecalho));
    
    Removido * r = new Removido();
    r->proximoPilha = cab->topo;
    r->caracter = '*';
    cab->topo = rrn;
    
    arquivo.seekp(0, ios::beg);
    arquivo.write((char *) cab, sizeof(Cabecalho));

    arquivo.seekp(rrn);
    arquivo.write((char *) r, sizeof(Removido));

    arquivo.close();

}
void arquivos::printarArquivoBinario(int rrn)
{
    Registro * reg = new Registro();
    fstream arquivo;
    arquivo.open("arquivo.dat", ios::in | ios::binary);
    if(arquivo.fail() && DEBUG)
    {
        cout << "Falha ao abrir o arquivo durante  a execucao do print" << endl;
        return;
    }
    arquivo.seekg(rrn);
    arquivo.read((char *)reg, sizeof(Registro));
    cout << "\tID: " << reg->id << endl;
    cout << "\tNome: " << reg->nome << endl;
    cout << "\tAno de Nascimento: " << reg->anoNascimento << endl;
    cout << "\tSexo: " << reg->sexo << endl;
    cout << "\tEtnia: " << reg->etnia << endl;
    cout << "\tContador: " << reg->contador << endl;
    cout << "\tRank: " << reg->rank << endl;
    arquivo.close();
}

void arquivos::limpaArquivo()
{
   
    rename("arquivo.dat","buffer");
   
    fstream arq1, arq2;
    arq1.open("arquivo.dat", ios::out | ios::trunc | ios::binary);
    arq2.open("buffer", ios::in | ios::binary);
    Cabecalho * cab = new Cabecalho();
    cab->topo = -1;
    arq1.write((char *) cab, sizeof(Cabecalho));
    arq2.seekg(sizeof(Cabecalho));
    Registro * reg = new Registro();
    Removido * rem = new Removido();
    int rrn;
    while(1)
    {
        rrn = arq1.tellg();
        arq2.read((char *) rem, sizeof(Removido));
        if(arq2.eof()) break;
        if(rem->caracter != '*')
        {
            arq2.seekg(rrn);
            arq2.read((char *) reg, sizeof(Registro));
            arq1.write((char *) reg, sizeof(Registro));
        }
        else
            arq2.seekg(rrn + sizeof(Registro));
    }
    arq1.close();
    arq2.close();
}
/*
===================================
ARVORE B na Memoria Principal
==================================
* Construtores das classes da arvore B
* Busca e percorrer a arvore B de forma transversal
* Código retirado do https://www.geeksforgeeks.org/introduction-of-b-tree-2/


*/

// Constructor for BTreeNode class

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new pair<int,int>[2*t-1];
    C = new BTreeNode *[2*t];

    // Initialize the number of keys as 0
    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
        cout << " (" << keys[i].INDICE << "," << keys[i].POSICAO<< ")";
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
int BTreeNode::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i].INDICE)
        i++;

    // If the found key is equal to k, return this node
    if (keys[i].INDICE == k)
        return keys[i].POSICAO;

    // If key is not found here and this is a leaf node
    if (leaf == true)
        return -1;

    // Go to the appropriate child
    return C[i]->search(k);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(pair<int,int> k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0].INDICE = k.INDICE;
		root->keys[0].POSICAO = k.POSICAO;  // Insert key
        root->n = 1;  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2*t-1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0].INDICE < k.INDICE)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(pair<int, int> k)
{
    // Initialize index as index of rightmost element
    int i = n-1;

    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i].INDICE > k.INDICE)
        {
            keys[i+1].INDICE = keys[i].INDICE;
			keys[i+1].POSICAO = keys[i].POSICAO;
            i--;
        }

        // Insert the new key at found location
        keys[i+1].INDICE = k.INDICE;
		keys[i+1].POSICAO = k.POSICAO;
        n = n+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i].INDICE > k.INDICE)
            i--;

        // See if the found child is full
        if (C[i+1]->n == 2*t-1)
        {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i+1].INDICE < k.INDICE)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t-1; j++)
	{
		z->keys[j].INDICE = y->keys[j+t].INDICE;
		z->keys[j].POSICAO = y->keys[j+t].POSICAO;
	}


    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    // Link the new child to this node
    C[i+1] = z;

    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--)
	{
		keys[j+1].INDICE = keys[j].INDICE;
		keys[j+1].POSICAO = keys[j].POSICAO;
	}


    // Copy the middle key of y to this node
    keys[i].INDICE = y->keys[t-1].INDICE;
	keys[i].POSICAO = y->keys[t-1].POSICAO;


    // Increment count of keys in this node
    n = n + 1;
}


