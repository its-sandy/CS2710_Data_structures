#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node 												// object for each node in tree
{
	int value;														// stores value of node												// stores size of subtree headed by it
	bool colour;													// true -- red, false -- black

	struct node *left;												// pointers to children and parent
	struct node *right;
	struct node *parent;
} node;

typedef struct rbtree												// object for storing root and nil pointer of tree
{
	node* root;
	node* nil;
} rbtree;

rbtree* createTree();												// function to initialize tree with root and nil

node* tree_minimum(rbtree* T, node* x);								//function to find leftmost child of given node

void left_rotate(rbtree* T, node* x);								//function to perform left rotation about given node

void right_rotate(rbtree* T, node* x);								//function to perform right rotation about given node

void rb_insert_fixup(rbtree* T, node* z);							// function to maintain rb property after insertion

void rb_insert(rbtree* T, int key);									// function to insert given value into tree

void rb_transplant(rbtree* T, node* u, node* v);				 	// function to transplant node v in place of node u

void rb_delete_fixup(rbtree* T, node* x);							// function to maintain rb property after deletion

void rb_delete(rbtree* T, int key);									// function to delete given value from tree

node* findNode(rbtree* T, node* root, int key);						// function to check if given node is available in the tree

void search(rbtree* T, int key);									// function to print found node's details

void printLevelOrder(rbtree* T);									//function to print level order of tree

void freeNodes(node* root, node* sentinel);							// function to deallocate memory used by nodes

void freeTree(rbtree* T);											//function to deallocate memory used by tree