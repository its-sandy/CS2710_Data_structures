/*
							 ALPHA BALANCED TREE

	Write a program that implements the alpha balanced tree data structure
	and verify that insert, delete and search operations require O(log n)
	amortized cost

																			*/
// importing header files

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "rb_tree.h"								// importing .h files for queue and tree
#include "queue.h"

extern bool already_there;
#define MAX_SIZE 10							// maximum value of element used

int main()
{
	int val, c=1,j;
	node* root = NULL;									// initializing the tree's root
	long long int n,i;
	clock_t start,stop;

	if(already_there)
		printf("already_there true \n");
	else
		printf("already_there false \n");

	FILE *fout2 = fopen("averagetime.dat","w");			// write file pointer

	n=1000;

	time_t t;
	srand((unsigned) time(&t));						//setting the seed for random function							
	
	start = clock();

	for(i=0; i<n; i++)
	{
		val = rand() % MAX_SIZE;			
		c = rand();								//equal probability for each function
		if(c%3 == 1)
			root = insertion(&root, val);
		else if (c%3 == 2)
			root = deletion(&root, val);
		else
			search(root, val);	
	}
	freeNodes(root);
	root = NULL;
	
	stop = clock();

	double time_taken = (double)(stop - start)/CLOCKS_PER_SEC;	//dividing by clocks per second to get the time in seconds
	printf("No. of Queries = %lld --- Total Time Taken = %.10f --- Average Time Taken = %.20f\n",n,time_taken/10,(time_taken/n)/10);
	fprintf(fout2, "%lld %.10f\n",n,(time_taken/n)/10);	//writing average time to file


	return 0;
}