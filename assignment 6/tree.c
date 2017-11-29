#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

#define alpha 0.7

int glob_array[100000], count, del_count=0;
bool glob_array_available[100000], already_there;

node *newNode(int value, node* parent)
{
    node *temp =  (node *)malloc(sizeof(node));
    temp->value = value;
    temp->subtree_size = 1;
    temp->available = true;
    temp->left = temp->right = NULL;
    temp->parent = parent;
    return temp;
}

void inorder(node *root, bool first)
{
	if(first == true)
	{
		if(root != NULL)
			printf("The inorder traversal of existing elements is:-\n");
		else
			printf("There are no elements\n");
	}
    if (root != NULL)
    {
        inorder(root->left, false);
        if(root -> available == true)
        	printf("%d ", root->value);
        inorder(root->right, false);
    }
    if(first == true)
    	printf("\n");
}

/* A utility function to insert a new node with given key in BST */
node* insert(node* root, int key)
{
	if(root == NULL)
		return newNode(key, NULL);
	if(root->value == key)
	{
		if(root -> available == false)
			del_count--;
		root->available = true;
		already_there = true;
		return root;
		
	}
    else if(key > root->value)
	{
		if(root -> right == NULL)
		{
			// (root->subtree_size)++;
			root->right = newNode(key, root);
			return root->right;
		}
		else
		{
			// (root->subtree_size)++;
			return insert(root->right, key);
		}
	}
	else
	{
		if(root -> left == NULL)
		{
			// (root->subtree_size)++;
			root->left = newNode(key, root);
			return root->left;
		}
		else
		{
			// (root->subtree_size)++;
			return insert(root->left, key);
		}
	}
}

void sortTreeForInsert(node* root)
{
	if(root != NULL)
	{
		sortTreeForInsert(root -> left);
		glob_array[count++] = root -> value;
		glob_array_available[count-1] = root -> available;
		sortTreeForInsert(root -> right);
	}
}

void sortTreeForDelete(node* root)
{
	if(root != NULL)
	{
		sortTreeForDelete(root -> left);
		if(root -> available == true)
		{
			glob_array[count++] = root -> value;
			glob_array_available[count-1] = root -> available;
		}
		sortTreeForDelete(root -> right);
	}
}

void freeNodes(node* root)
{
	if(root != NULL)
	{
		freeNodes(root -> left);
		freeNodes(root -> right);
		free(root);
	}
}

node* buildTree(node* parent, int lindex, int rindex)
{
	if(rindex < lindex)
		return NULL;
	else
	{
		int mid = (lindex + rindex)/2, lsize, rsize;
		node* temp = newNode(glob_array[mid], parent);
		temp -> available = glob_array_available[mid];
		temp -> left = buildTree(temp, lindex, mid-1);
		temp -> right = buildTree(temp, mid+1, rindex);

		if(temp -> left == NULL)
			lsize = 0;
		else
			lsize = (temp -> left)->subtree_size;

		if(temp -> right == NULL)
			rsize = 0;
		else
			rsize = (temp -> right)->subtree_size;
		
		temp -> subtree_size = lsize + rsize + 1;
		return temp;
	}
}


node* rebuild(node* root, bool ins)
{
	count = 0;
	if(ins == true)
		sortTreeForInsert(root);
	else
		sortTreeForDelete(root);
	freeNodes(root -> left);
	freeNodes(root -> right);
	return buildTree(NULL, 0, count - 1);
}

node* insertion(node** root_ptr, int key) // takes address of root as input
{
	already_there = false;
	float lsize, rsize;
	node* add_node = insert(*root_ptr, key);
	node* added_node = add_node -> parent;

	if(*root_ptr == NULL)
		*root_ptr = add_node;

	if(already_there == false)
	{
		while(added_node != NULL)
		{
			added_node -> subtree_size++;
			added_node = added_node -> parent;
		}

		while(add_node != NULL)
		{
			if(add_node -> left == NULL)
				lsize = 0;
			else
				lsize = (add_node -> left)->subtree_size;

			if(add_node -> right == NULL)
				rsize = 0;
			else
				rsize = (add_node -> right)->subtree_size;

			if(lsize > alpha*(lsize+rsize+1) || rsize > alpha*(lsize+rsize+1))
			{
				node* temp = rebuild(add_node, true);
				add_node -> available = temp -> available;
				add_node -> value = temp -> value;
				add_node -> left = temp -> left;
				add_node -> right = temp -> right;

				if(add_node -> left != NULL)
					(add_node -> left) -> parent = add_node;
				if(add_node -> right != NULL)
					(add_node -> right) -> parent = add_node;

				free(temp);
				printf("Rebuilding over\n");
				break;
			}
				add_node = add_node -> parent;
			}
		}
		printf("element is inserted\n");
		return *root_ptr;		// root
	}

	////////////////////////// delete
	node* findNode(node* root, int key)
	{
		if(root == NULL)
			return NULL;
		if(root -> value == key)
		{
			if(root -> available == true)
				return root;
			else
				return NULL;
		}
		if(key < root -> value)
			return findNode(root -> left, key);
		else
			return findNode(root -> right, key);
	}

	node* deletion(node** root_ptr, int key)
	{
		node* temp = findNode(*root_ptr, key);
		if(temp == NULL)
			printf("the element is not present in the tree\n");
		else
		{
			temp -> available = false;
			del_count++;
			printf("the element was deleted from the tree\n");

			if(del_count > 0.5 * ((*root_ptr) -> subtree_size))
			{
				*root_ptr = rebuild(*root_ptr, false);	
				del_count = 0;
			}
		}
		return *root_ptr;
	}

	void search(node* root, int key)
	{
		node* temp = findNode(root, key);
		if(temp == NULL)
		printf("the element is not present in the tree\n");
	else
		printf("the element is present in the tree\n");																																									
}

//////////

void printLevelOrder(node* root)
{
	if(root == NULL || root -> subtree_size == del_count)
		printf("the tree is empty\n");
	else
	{
		Queue *q = createQueue();
		QNode *n;
		printf("the level order of tree is :-\n");
		enQueue(q, root);

		while(q -> front != NULL)
		{
			n = deQueue(q);
			if(n->element != NULL)
			{
				printf("%d ", n->element->value);
				enQueue(q, n->element->left);
				enQueue(q, n->element->right);
			}
		}
		printf("\n");
	}
}
