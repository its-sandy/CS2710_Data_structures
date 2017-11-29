#include "disjoint_set.h"					//importing .h file with functions prototypes

#define MAX_SIZE 100000						//largest element that can belong to any set

void initialize(set* array[])
{// function to initialize the array of pointers with NULL (since no elements are present yet)

	int i;
	for(i=0; i<MAX_SIZE; i++)
		array[i] = NULL;
}

void makeSet(set* array[], int element)
{// function to create a new set with the given element, provided the element is not already present

	if(array[element] == NULL)				//checks if the element is present
	{
		set* temp = (set*)malloc(sizeof(set));
		temp->element = element;
		temp->parent = temp;				//the new set points to itself
		temp->rank = 0;
		array[element] = temp;				//we update the new node in the array of pointers
		printf("New set created\n");
	}
	else
		printf("Element already present\n");
}

set* find(set* x)					
{// function that returns the Leader of the given set

	if(x != x->parent)
		x->parent = find(x->parent);		//we keep rising up, while performing PATH COMPRESSION at the same time
	return x->parent;
}

void findSet(set* array[], int element)
{// function to print the Leader of the given element, if it is present
	if(array[element] == NULL)
		printf("Element not present\n");
	else
		printf("Leader of set of %d is %d\n", element, find(array[element])->element);
}

void link(set* x, set* y)
{// function to link 2 sets based on the ranks of their leaders

	if(x->rank > y->rank)					//if x has a higher rank, x remains the Leader
		y->parent = x;
	else
		x->parent = y;						//if y has a higher rank or the ranks are equal, then, y remains the Leader

	if(x->rank == y->rank)					//if original ranks are equal, the rank of y goes up by 1 after linking
		(y->rank)++;
}

void unionSet(set* array[], int x, int y)
{// function to perform Union operation on the sets that contain 2 given elements

	if(array[x] == NULL || array[y] == NULL) //Union cannot be performed if either of the elements are not present
		printf("Element(s) not present\n");
	else
	{
		if(find(array[x]) == find(array[y])) //Union cannot be performed if both elements already belong to the same set
			printf("The elements are already linked\n");
		else
		{
			link(find(array[x]), find(array[y]));  //we link the 2 sets
			printf("The sets were linked\n");	
		}
	}
}