/*****************************************DYNAMIC ARRAY*****************************************
									
									  --PROBLEM STATEMENT--

	Write a program to create an abstract dynamic array structure that can support two
	operations, addition and deletion. These operations should dynamically expand and contract 
	the size of array as and when needed.:-
		1) double the size of array if number of elements exceeds size of array
		2) halve the size of array if number of elements is less than one quarter
		   of the size of array

************************************************************************************************/

// importing header files 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int num_of_elements = 0; 									//global varibale to store number of elements currently in the array
int size = 1;												//global varibale to store current total size of the array

int *insert(int *ptr, int num)								//function to add an element to the array
{															//takes the first pointer of the array and element to be added as input
	if(num_of_elements < size)								//if number of elements in array is less than it's size, 
	{														//simply add the element
		ptr[num_of_elements++] = num;
		return ptr;											//return the same pointer
	}
	else 													//if array is already full
	{
		int *temp = (int *)malloc(size*2*sizeof(int));		//we create a new array of twice the size
		int i;

		for(i=0; i<size; i++)								//copy the contents of existing array into the new array
			temp[i] = ptr[i];

		temp[num_of_elements++] = num;						//add the new element
		size *= 2;
		free(ptr);											//free the old memory locations

		return temp;										//return a pointer to first element of new array
	}
}

int *delete(int *ptr)										//function to delete the top element of the array
{
	if(num_of_elements == 0)								//if array is empty, simply return the same pointer
	{
		return ptr;
	}
	else
	{
		num_of_elements--;									//deleting the element just amounts to decreasing no. of elements by 1

		if(size > 1 && num_of_elements < (size/4))			//if number of elements becomes less than one quarter of the size of array
		{
			int *temp = (int *)malloc((size/2)*sizeof(int));	//we create a new array of half the size
			int i;

			for(i=0; i<num_of_elements; i++)				//copy the contents of existing array into the new array
				temp[i] = ptr[i];	

			size /= 2;
			free(ptr);										//free the old memory locations
			return temp;									//return a pointer to first element of new array
		}	
		return ptr;											//return the same pointer
	}
}

int main(int argc, char** argv)								//arguments are initial and final powers of 2 in the number of elements
{
	if(argc != 3)											//check if the correct number of arguments have been provided
		printf("Error: incorrect number of parameters. Enter 2 parameters\n");
	else
	{
		FILE *fout1 = fopen("totaltime.dat","w");			//opening output file stream to store total time and average time per query
		FILE *fout2 = fopen("averagetime.dat","w");
		long long int n = atoi(argv[1]),m = atoi(argv[2]);
		long long int i,j;									//loop variables

		n = pow(2,n);										//n and m store the initial and final number of queries
		m = pow(2,m);

		for(j=n; j<=m; j*=2)
		{
			int *ptr = (int *)malloc(sizeof(int));			//initializing the array with just capacity of 1 element
			time_t t;
			srand((unsigned) time(&t));						//setting the seed for random function							
			clock_t start,stop;
			num_of_elements = 0;
			size = 1;

			start = clock();								//storing the starting time 
			for(i=0; i<j; i++)
			{
				if(rand() % 10 < 6)							//we give a 60% chance for addition and 40% chance for deletion
					ptr = insert(ptr, rand());
				else
					ptr = delete(ptr);	
			}

			stop = clock();									//storing the ending time 

			double time_taken = (double)(stop - start)/CLOCKS_PER_SEC;	//dividing by clocks per second to get the time in seconds
			printf("No. of Queries = %lld --- Total Time Taken = %.10f --- Average Time Taken = %.20f\n",j,time_taken,time_taken/j);
			fprintf(fout1, "%lld %.20f\n",j,time_taken);	//writing total time to file 
			fprintf(fout2, "%lld %.10f\n",j,time_taken/j);	//writing average time to file

			free(ptr);										//freeing the memory locations allocated for array
		}
		fclose(fout1);										//closing the two file pointers
		fclose(fout2);
	}
	return 0;
}