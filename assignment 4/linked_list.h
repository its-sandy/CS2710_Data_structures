/* 
		This header file contains the definition of the structure
		"node" and also prototypes of certain functions that are
		used in the linked list. The definitions of these functions
		are available in file "linked_list.c"
																		*/

typedef struct node
{
	int value;
	struct node *next;
} node;

void insertNode(node* end, int val);			//	Function to insert a new node of value "val" at the end of linked list
void printNodes(node* head);					//	Function to print the values of nodes in the linked list
void freeNodes(node* head);						//	Function to free the memory allocated to the linked list