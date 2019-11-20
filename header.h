#ifndef HEADER_H // include guard
#define HEADER_H
#include <bits/stdc++.h>
using namespace std;
#define INDICE first
#define POSICAO second
#define mp make_pair

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
	long long id;
	long long rrn;
}id;



class arquivos
{
	public:
    	void gerarBinario(int tamanho);
		void gerarBinarioIndiceId(int tamanho);
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
	    BTreeNode *search(int k);   // returns NULL if k is not present.

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
	    BTreeNode* search(int k)
	    {  return (root == NULL)? NULL : root->search(k); }

	    // The main function that inserts a new key in this B-Tree
	    void insert(pair<int, int> k);
};

#endif /* MY_CLASS_H */
