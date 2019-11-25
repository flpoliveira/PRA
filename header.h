#ifndef HEADER_H // include guard
#define HEADER_H
#include <bits/stdc++.h>
using namespace std;
#define INDICE first
#define POSICAO second
#define mp make_pair
#define DEBUG 1


typedef struct Registro
{
    int id;
    int anoNascimento;
    char sexo[7];
    char etnia[100];
    char nome[100];
    int contador;
    int rank;
}Registro;

typedef struct Cabecalho
{
	int topo;
}Cabecalho;

typedef struct Removido
{
	char caracter;
	int proximoPilha;
}Removido;

typedef struct id
{
	long long id;
	long long rrn;
}id;



class arquivos
{
	public:
    	void gerarBinario(int tamanho);
		void gerarBinarioIndiceId();
		int  inserirArquivoBinario(Registro * reg);
		void printarArquivoBinario(int rrn);
		void inserirIndiceId(int rrn);
		void removerArquivoBinario(int rrn);
		void limpaArquivo();
};


class BTreeNode
{
    pair <int, int> *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
	public:
	    BTreeNode(int _t, bool _leaf);   // Constructor

	    // A utility function to insert a new key in the subtree rooted with
	    // this node. The assumption is, the node must be non-full when this
	    // function is called
	    void insertNonFull(pair <int, int> k);

	    // A utility function to split the child y of this node. i is index of y in
	    // child array C[].  The Child y must be full when this function is called
	    void splitChild(int i, BTreeNode *y);

	    // A function to traverse all nodes in a subtree rooted with this node
	    void traverse();

	    // A function to search a key in the subtree rooted with this node.
	    int search(int k);   // returns NULL if k is not present.

	// Make BTree friend of this so that we can access private members of this
	// class in BTree functions
	friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
	public:
	    // Constructor (Initializes tree as empty)
	    BTree(int _t)
	    {  root = NULL;  t = _t; }

	    // function to traverse the tree
	    void traverse()
	    {  if (root != NULL) root->traverse(); }

	    // function to search a key in this tree
	    int search(int k)
	    {  return (root == NULL)? -1 : root->search(k); }

	    // The main function that inserts a new key in this B-Tree
	    void insert(pair<int, int> k);
};

/*
typedef struct SecondaryBTreeHeader{
	int rrnRoot;
	int t;
}SecondaryBTreeHeader;

typedef struct SecondaryBTreeNode{
	pair<int, int> keys[2*GRAUMINIMO-1];
	int n;
	bool leaf;
	int rrnFilhos[2*GRAUMINIMO];
}SecondaryBTreeNode;

//BTree for secondary memory
class SecondaryBTree
{
	
	SecondaryBTreeNode * node;
	public:
		SecondaryBTree()
		{
			fstream arquivo;
			arquivo.open("BTree.dat", ios::out | ios::app | ios::binary);
			SecondaryBTreeHeader * header = new SecondaryBTreeHeader();
			header->rrnRoot = -1;
			header->t = GRAUMINIMO;
			node = NULL;
			cout << header->rrnRoot << ", " << header->t << endl;
			arquivo.write((char *) header, sizeof(SecondaryBTreeHeader));
			arquivo.close();
		}
		int search(int k)
		{
			fstream arquivo;
			arquivo.open("BTree.dat", ios::out | ios::app | ios::binary);				
			if(arquivo.fail())
			{
				cout << "Erro ao abrir o arquivo da BTree" << endl;
				return -1;
			}
			SecondaryBTreeHeader * header = new SecondaryBTreeHeader();

			arquivo.seekg(0, ios::beg);
			arquivo.read((char*)header, sizeof(SecondaryBTreeHeader));
			if(header.rrnRoot == -1)
			{
				cout << "Arvore vazia" << endl;
				return -1;
			}
			else
			{
				
			}
			return 1;

		}
		void insert(pair<int, int> k)
		{
			// stream arquivo;
			// arquivo.open("BTree.dat", ios::out | ios::app | ios::binary);				
			// if(arquivo.fail())
			// {
			// 	cout << "Erro ao abrir o arquivo da BTree" << endl;
			// 	return -1;
			// }
			// SecondaryBTreeHeader * header = new SecondaryBTreeHeader();

			// arquivo.seekg(0, ios::beg);
			// arquivo.read((char*)header, sizeof(SecondaryBTreeHeader));
			// if(header.rrnRoot == -1)
			// {
				
			// }
		}
		streampos alocando(bool _leaf)
		{
			fstream arquivo;
			arquivo.open("BTree.dat", ios::out | ios::app | ios::binary);
			SecondaryBTreeNode * no = new SecondaryBTreeNode();
			for(int i = 0; i < 2*GRAUMINIMO-1; i++)
			{
				no->keys[i] = mp(-1, -1);

			}
			no->n = 0;
			no->leaf = _leaf;
			for(int i  = 0 ; i < 2*GRAUMINIMO;i++)
			{
				no->rrnFilhos[i] = -1;
			}
			arquivo.seekp(ios::end);
			streampos rrn = arquivo.tellg();
			cout << arquivo.tellp() << "dasdadsadasd" << endl; 
			arquivo.write((char*) no, sizeof(SecondaryBTreeNode));	
			arquivo.close();
			return rrn;
		}


};


*/
#endif /* MY_CLASS_H */

