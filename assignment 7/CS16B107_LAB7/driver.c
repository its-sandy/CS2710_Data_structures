/*                     RED BLACK TREES

 write a program to implement a red black tree with insert, delete and search features

 E.Santhosh Kumar (CS16B107)
                                                                            */
// importing header files

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "rb_tree.h"								// importing .h files for queue and tree
#include "queue.h"

#define MAX_SIZE 1000000									// maximum value of element used

int main()
{
	int val, c=1,j;
	long long int n,i;
	clock_t start,stop;
	double time_taken;

	FILE *fout2 = fopen("averagetime.dat","w");			// write file pointer

	time_t t;
	srand((unsigned) time(&t));							//setting the seed for random function			

	n = 1024;											//number of operations
	while(n <= 4194304)
	{
		rbtree* T = createTree();						//we initialize the tree
		start = clock();

		for(i=0; i<n; i++)
		{
			val = rand() % MAX_SIZE;			
			c = rand()%10;								
			if(c < 5)									// 50% probability for insertion
				rb_insert(T, val);
			else if (c < 8)
				rb_delete(T, val);						// 30% probability for insertion
			else
				search(T, val);							// 20% probability for insertion
		}
		stop = clock();
		freeTree(T);	

		time_taken = (double)(stop - start)/CLOCKS_PER_SEC;	//dividing by clocks per second to get the time in seconds
		printf("No. of Queries = %lld --- Total Time Taken = %.10f --- Average Time Taken = %.20f\n",n,time_taken,time_taken/n);
		fprintf(fout2, "%lld %.10f\n",n,time_taken/n);	//writing average time to file
		n*=2;
	}				
	return 0;
}
