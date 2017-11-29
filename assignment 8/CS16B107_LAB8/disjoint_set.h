#include <stdio.h>
#include <stdlib.h>

typedef struct set
{
	int element;				//stores the value of the element
	struct set* parent;			//stores the immediate parent of the element
	int rank;					//stores the rank of the element
} set;

void initialize(set* array[]);
// function to initialize the array of pointers with NULL (since no elements are present yet)

void makeSet(set* array[], int element);
// function to create a new set with the given element, provided the element is not already present

set* find(set* x);
// function that returns the Leader of the given set

void findSet(set* array[], int element);
// function to print the Leader of the given element, if it is present

void link(set* x, set* y);
// function to link 2 sets based on the ranks of their leaders

void unionSet(set* array[], int x, int y);
// function to perform Union operation on the sets that contain 2 given elements