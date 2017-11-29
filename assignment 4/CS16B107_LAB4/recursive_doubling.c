/*
							 RECURSIVE DOUBLING

	Write a program that implements recursive doubling in a linked list.
	Assume that the number of elements in the list is a power of 2.

																			*/

// Importing header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "linked_list.h"											// Header file containing definition of linked list data structure
																	// and prototypes of functions used by it

#define MAX_VAL 20													// maximum value taken by an input element (for convinience)

typedef long long int ll;

void print(node *ptrarray[], ll n, int j)							// Function to print value of nodes pointed by elements of 
{																	// array "ptrarray" of size "n"

	ll i;
	printf("%4d     ", j);											// printing the iteration number
	for(i=0; i<n; i++)
		printf("%4d\t", ptrarray[i] -> value);						// we loop through the array and print each value according to the format
	printf("\n");
}

int main(int argc, char** argv)
{
	if(argc != 2)													// check if the correct number of arguments have been provided
		printf("Error: incorrect number of parameters. Enter 1 parameter\n");
	else
	{
		time_t t;
		srand((unsigned) time(&t));										// setting the seed for random function	

		ll n = pow(2, atoi(argv[1])),i;								// the number of elements used for calculation is 2^(argument)
		node* head = (node*)malloc(sizeof(node));					// declaring, allocating memory and initialising the head of linked list
		head -> value = rand() % MAX_VAL;
		head -> next = NULL;

		node* temp = head;
		for(i=1; i<n; i++)
		{
			insertNode(temp,rand() % MAX_VAL);						// Adding remaining nodes using insertNode from linked_list.h
			temp = temp->next;
		}
		insertNode(temp,0);											// We add the element 0 at last for convinience during calculation 

		temp = head;
		node *ptrarray[n+1];										// Creating array of node pointers to maintain each chain	
		ptrarray[0] = temp;
		for(i=0; i<=n; i++)											// Updating the pointers to the nodes of linked list in the array
		{
			ptrarray[i] = temp;
			temp = temp->next;
		}

		printf("Iteration");										// Printing column heading according to format
		for(i=1; i<=n; i++)
			printf("%4lld\t", i);
		printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

		print(ptrarray, n, 0);
		int k = atoi(argv[1]),j;

		// Calculation begins
		for(j=1; j<=k; j++)											// The number of iterations is the log to the base 2 of number of elements
		{
			for(i=0; ptrarray[i] -> next != NULL; i++)				// In each iteration, we loop over each chain in the ptrarray array of pointers
			{
				(ptrarray[i] -> value) += ((ptrarray[i] -> next) -> value); 	// Adding value of next node to current node
				(ptrarray[i] -> next) = ((ptrarray[i] -> next) -> next);		// Shifting "next" of current node one step forward, to "next" of current next node
			}
			print(ptrarray, n, j);									// printing the contents of ptrarray after each iteration
		}
		freeNodes(head);											// Freeing the nodes in the linked list using freeNodes in "linked_list.h"
	}
	return 0;
}