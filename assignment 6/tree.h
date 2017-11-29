/* 
		This header file contains the definition of the structure
		"node" and also prototypes of certain functions that are
		used in the queue. The definitions of these functions
		are available in file "tree.c"
																		*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node 												// object for each node in tree
{
	int value;														// stores value of node
	int subtree_size;												// stores size of subtree headed by it
	bool available;													// tells if node has not been deleted

	struct node *left;												// pointers to children and parent
	struct node *right;
	struct node *parent;
} node;

node *newNode(int value, node* parent);								// function to initialize new node
void inorder(node *root, bool first);								// function to perform inorder traversal
node* insert(node* root, int key);									// function to insert given value in tree
void sortTreeForInsert(node* root);									// helper functions used for rebuilding the tree
void sortTreeForDelete(node* root);
void freeNodes(node* root);											// function to free all nodes under a given node
node* buildTree(node* parent, int lindex, int rindex);				// function to rebuild a tree
node* rebuild(node* root, bool ins);								// function to manage operations under rebuilding
node* insertion(node** root_ptr, int key);							// function to manage operations under insertion
node* findNode(node* root, int key);								// function to check if given node is available in the tree
node* deletion(node** root_ptr, int key);							// function to manage operations under deletion
void search(node* root, int key);
void printLevelOrder(node* root);									// function to print levelOrder of tree


/////////////////////

// A linked list (LL) node to store a queue entry
typedef struct QNode
{
    node* element;
    struct QNode *next;
} QNode;
 
// The queue, front stores the front node of LL and rear stores ths
// last node of LL
typedef struct Queue
{
    struct QNode *front, *rear;
} Queue;
 
QNode* QnewNode(node* key);
Queue *createQueue();
void enQueue(Queue *q, node* key);
QNode *deQueue(Queue *q);