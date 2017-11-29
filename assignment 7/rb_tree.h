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

node *newNode(int value, node* parent);								// function to initialize new node
void inorder(node *root, bool first);								// function to perform inorder traversal
void left_rotate(node** root_ptr, node* p);
void right_rotate(node** root_ptr, node* p);
node* uncle(node* x);
node* sibling(node* x);
node* grandparent(node* x);
bool colour(node* x);
node* substitute_node(node* x);
void insert_alterations(node** root_ptr, node* x);
node* insert(node* root, int key);									// function to insert given value in tree
node* insertion(node** root_ptr, int key);							// function to manage operations under insertion
void double_black(node** root_ptr, node* u);
node* findNode(node* root, int key);								// function to check if given node is available in the tree
node* deletion(node** root_ptr, int key);							// function to manage operations under deletion
void search(node* root, int key);
void printLevelOrder(node* root);
void freeNodes(node* root);