/*
							 ALPHA BALANCED TREE

	Write a program that implements the alpha balanced tree data structure
	and verify that insert, delete and search operations require O(log n)
	amortized cost

	File containing function definitions for the tree and queue data structures

																			*/

// including necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"											// .h file having structure definitions and function prototypes

#define alpha 0.7											// parameter used for tree balancing condition 

int glob_array[100000], count, del_count=0;					// glob_array, glob_array_available -> global arrays used for rebuilding
bool glob_array_available[100000], already_there;			// del_count -> stores number of deleted nodes present in tree

node *newNode(int value, node* parent)						
{
	/* function used to initialize new nodes in the tree */
    node *temp =  (node *)malloc(sizeof(node));
    temp->value = value;
    temp->subtree_size = 1;
    temp->available = true;									// indicates whether the node has been deleted or not
    temp->left = temp->right = NULL;
    temp->parent = parent;
    return temp;											// returns the newly allocated node
}

void inorder(node *root, bool first)
{
	/* function used to perform inorder traversal (ascending order)
	of the tree. Prints only non-deleted elements */
	if(first == true)										// variable to indicate first level recursive call (for tidier printing)
	{
		if(root != NULL)
			printf("The inorder traversal of existing elements is:-\n");
		else
			printf("There are no elements\n");
	}
    if (root != NULL)
    {
        inorder(root->left, false);							// left subtree printed before current node
        if(root -> available == true)						// checks whether the element is not deleted
        	printf("%d ", root->value);
        inorder(root->right, false);						// right subtree printed after current node
    }
    if(first == true)
    	printf("\n");
}

node* insert(node* root, int key)
{
	/* A utility function to insert a new node with given key in BST 
	returns the location where the node was inserted*/
	if(root == NULL)										// if tree does not exist, the new node by itself is the root
		return newNode(key, NULL);							
	if(root->value == key)									// checks if a node with the given value is already present
	{
		if(root -> available == false)						// if it were deleted, we renew its availability
			del_count--;									// number of deleted nodes is decremented
		root->available = true;
		already_there = true;								// subtree sizes should not be updated if node is already there
		return root;
		
	}
    else if(key > root->value)								// if key is bigger than node, move to right subtree
	{
		if(root -> right == NULL)							// if subtree doesn't exist
		{
			root->right = newNode(key, root);
			return root->right;
		}
		else 												// if subtree exists, recursively call in it
			return insert(root->right, key);
	}
	else 													// if key is smaller than node, move to left subtree
	{
		if(root -> left == NULL)							// if subtree doesn't exist
		{
			root->left = newNode(key, root);
			return root->left;
		}
		else 												// if subtree exists, recursively call in it
			return insert(root->left, key);			
	}
}

void sortTreeForInsert(node* root)
{
	/* utility function used for rebuilding during insertion.
	All nodes in the tree are retained */
	if(root != NULL)
	{
		sortTreeForInsert(root -> left);					// performed similar to inorder traversal
		glob_array[count++] = root -> value;				// we copy the values to global array in ascending order		
		glob_array_available[count-1] = root -> available;	// we maintain the availablity status of each node in the new tree
		sortTreeForInsert(root -> right);
	}
}

void sortTreeForDelete(node* root)
{
	/* utility function used for rebuilding during deletion.
	Only non-deleted nodes in the tree are retained */
	if(root != NULL)
	{
		sortTreeForDelete(root -> left);					// performed similar to inorder traversal
		if(root -> available == true)						// checks if node not deleted
		{
			glob_array[count++] = root -> value;			// we copy the values to global array in ascending order
			glob_array_available[count-1] = root -> available; // we do this just so we can use the existing rebuild function
		}
		sortTreeForDelete(root -> right);					// performed similar to inorder traversal
	}
}

void freeNodes(node* root)
{
	/*utility function to delete all nodes in the subtree under root*/
	if(root != NULL)
	{
		freeNodes(root -> left);							// should be performed in post-order traversal form
		freeNodes(root -> right);
		free(root);
	}
}

node* buildTree(node* parent, int lindex, int rindex)
{
	/* utility function used to build a BST from the elements present
	in glob_array, within the given limits*/
	if(rindex < lindex)										//no node exists if left limit > right limit
		return NULL;
	else
	{
		int mid = (lindex + rindex)/2, lsize, rsize;
		node* temp = newNode(glob_array[mid], parent);		// we choose the middle element in each stage to get a balanced BST
		temp -> available = glob_array_available[mid];		// availability status is retained
		temp -> left = buildTree(temp, lindex, mid-1);		// we build the subtrees
		temp -> right = buildTree(temp, mid+1, rindex);

		if(temp -> left == NULL)
			lsize = 0;
		else
			lsize = (temp -> left)->subtree_size;

		if(temp -> right == NULL)
			rsize = 0;
		else
			rsize = (temp -> right)->subtree_size;
		
		temp -> subtree_size = lsize + rsize + 1;			// subtree sizes for all the nodes in the subtree have to be updated
		return temp;										// returns pointer to the root node of newly built subtree
	}
}


node* rebuild(node* root, bool ins)
{
	/* function used to manage the different processes in tree rebuilding
	 ins -> indicates whether rebuild is for insertion or deletion */
	count = 0;
	if(ins == true)											// sorts the elements based on insertion/ deletion rebuild
		sortTreeForInsert(root);
	else
		sortTreeForDelete(root);
	freeNodes(root -> left);								// frees the existing nodes in the tree that is meant to be rebuilt
	freeNodes(root -> right);
	return buildTree(NULL, 0, count - 1);					// returns pointer to the root node of newly built subtree
}

node* insertion(node** root_ptr, int key) // takes address of root as input
{
	/* function used to manage the different processes in insertion 
	receives the address of root pointer so that root can itself be changed
	if required*/
	already_there = false;
	float lsize, rsize;
	node* add_node = insert(*root_ptr, key);				// pointer to location where key was inserted
	node* added_node = add_node -> parent;

	if(*root_ptr == NULL)									// if it were an empty tree, root has to be altered
		*root_ptr = add_node;

	if(already_there == false)								// further operations should be done only if node wasn't already there
	{
		while(added_node != NULL)							// we increment subtrees_size ofall ancestors of the inserted node
		{
			added_node -> subtree_size++;
			added_node = added_node -> parent;
		}

		while(add_node != NULL)								// we check if alpha-balanced condition is satisfied by all of 
		{													// the inserted node's parents
			if(add_node -> left == NULL)
				lsize = 0;
			else
				lsize = (add_node -> left)->subtree_size;

			if(add_node -> right == NULL)
				rsize = 0;
			else
				rsize = (add_node -> right)->subtree_size;

			if(lsize > alpha*(lsize+rsize+1) || rsize > alpha*(lsize+rsize+1))	// check if condition is broken
			{
				node* temp = rebuild(add_node, true);		// if yes, we rebuild the subtree headed at that node
				add_node -> available = temp -> available;	// we copy all values in returned node to existing node in the tree 
				add_node -> value = temp -> value;
				add_node -> left = temp -> left;
				add_node -> right = temp -> right;

				if(add_node -> left != NULL)				// we update the parent field  of the two children to the 
					(add_node -> left) -> parent = add_node;// existing address of node
				if(add_node -> right != NULL)
					(add_node -> right) -> parent = add_node;

				free(temp);									// we free the last node. All temporary nodes used are now freed
				break;										// there can be at most one rebuild per insert
			}
				add_node = add_node -> parent;
		}
	}
	printf("element is inserted\n");
	return *root_ptr;										// returns the root node
}

node* findNode(node* root, int key)
{
	/* utility function to find if element is present in
	tree and is not deleted */
	if(root == NULL)
		return NULL;										// NULL is returned if either root is not there
	if(root -> value == key)								// or node is present in tree but is deleted
	{
		if(root -> available == true)
			return root;									// if node is available, we return its address
		else
			return NULL;
	}
	if(key < root -> value)									// we move into the 2 subtress depending on node's value
		return findNode(root -> left, key);
	else
		return findNode(root -> right, key);
}

node* deletion(node** root_ptr, int key)
{
	/* function to delete the given node in tree, if it is available */
	node* temp = findNode(*root_ptr, key);					// we check if node is available
	if(temp == NULL)
		printf("the element is not present in the tree\n");
	else 													// if node is available
	{
		temp -> available = false;							// update its availability and no. of deleted nodes in tree
		del_count++;
		printf("the element was deleted from the tree\n");

		if(del_count > 0.5 * ((*root_ptr) -> subtree_size)) // if there are too many deleted nodes, (paramter = 0.5)
		{
			*root_ptr = rebuild(*root_ptr, false);			// we rebuild the tree with only available nodes
			del_count = 0;									// del_count is reset as tree is rebuilt
		}
	}
	return *root_ptr;										// we return the root (updated or otherwise)
}

void search(node* root, int key)
{
	/*function that simply prints output based on what findNode function returns */
	node* temp = findNode(root, key);
	if(temp == NULL)
	printf("the element is not present in the tree\n");
	else
	printf("the element is present in the tree\n");
}


void printLevelOrder(node* root)
{
	/* function that prints all nodes in the tree in 
	Level Order (even if they are not available)  */
	if(root == NULL)										// checks if tree is empty
		printf("the tree is empty\n");
	else
	{
		Queue *q = createQueue();							// we utilize a queue data structure to perform level order
		QNode *n;
		printf("the level order of tree is :-\n");
		enQueue(q, root);									// root becomes the first QNode in the queue

		while(q -> front != NULL)							// while queue is not empty
		{
			n = deQueue(q);									// front element is dequed
			if(n->element != NULL)							// if it is not NULL
			{
				printf("%d ", n->element->value);			// weprint its value and enque its children at the end
				enQueue(q, n->element->left);
				enQueue(q, n->element->right);
			}
		}
		printf("\n");
	}
}
