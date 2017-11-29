#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "tree.h"

#define MAX_SIZE 100000

int main()
{
	int val, c=1;
	node* root = NULL;
	long long int n,i;
	clock_t start,stop;
	FILE *fout2 = fopen("periterationtime.dat","w");
	double time_taken;

	n=655356;
	// while(n <= 524288)
	// {
		time_t t;
		srand((unsigned) time(&t));						//setting the seed for random function							
		
		start = clock();
		for(i=0; i<n; i++)
		{
			val = rand() % MAX_SIZE;
			// c = rand();
			// if(c%4 < 4)
				root = insertion(&root, val);
			// else if (c%10 < 3)
			// 	root = deletion(&root, val);
			// else
			// 	search(root, val);
			stop = clock();
			time_taken = (double)(stop - start)/CLOCKS_PER_SEC;
			printf("Insert No. = %lld --- Total Time Taken = %.10f --- Average Time Taken = %.10f\n",i,time_taken,time_taken/i);
			if(i%1000 == 0)
				fprintf(fout2, "%lld %.10f\n",i,time_taken/i);
		}
		

		//time_taken = (double)(stop - start)/CLOCKS_PER_SEC;	//dividing by clocks per second to get the time in seconds
		//printf("No. of Queries = %lld --- Total Time Taken = %.10f --- Average Time Taken = %.20f\n",n,time_taken,time_taken/n);
		// fprintf(fout1, "%lld %.20f\n",n,time_taken);	//writing total time to file 
		//fprintf(fout2, "%lld %.10f\n",n,time_taken/n);	//writing average time to file

		freeNodes(root);
		root = NULL;
		//n*=2;
	// }


	// while(c!=0)
	// {
	// 	printf("\nEnter option:- 0-quit, 1-insert, 2-delete, 3-level_order, 4-in_order, 5-search\n");
	// 	scanf("%d",&c);
	// 	switch(c)
	// 	{
	// 		case 0: return 0; break;
	// 		case 1:
	// 			printf("Enter value to insert\n");
	// 			scanf("%d",&val);
	// 			root = insertion(&root, val);
	// 			break;
	// 		case 2:
	// 			printf("Enter value to delete\n");
	// 			scanf("%d",&val);
	// 			root = deletion(&root, val);
	// 			break;
	// 		case 3:
	// 			printLevelOrder(root);
	// 			break;
	// 		case 4:
	// 			inorder(root, true);
	// 			break;
	// 		case 5:
	// 			printf("Enter value to search\n");
	// 			scanf("%d",&val);
	// 			search(root, val);
	// 			break;
	// 		default:
	// 			printf("Enter correct query\n");
	// 	}
	// }
	return 0;
}