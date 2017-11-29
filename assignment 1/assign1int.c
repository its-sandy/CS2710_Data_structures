#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/***********************************************************************************************
											--PROBLEM STATEMENT--

	Write a program that will search for a given query element among 'n' elements in an UNSORTED array:

		a)  Assume the elements are integers and fill up array with random integers.

		b)  Simulate tossing of an unbiased coin. If HEADS, the query is a random integer and if 
			TAILS, query is the integer stored in a
			random index.

		c)  Plot the graph for increasing values of n and time taken. For each n, execute 10000 queries 
			as in (b) and take average.

		d)  Repeat the first three steps for double.

***********************************************************************************************/

int main(int argc, char** argv)										//arguments are initial and final powers of 2 in the number of elemens
{
	if(argc != 3)													//check if the correct number of arguments have been provided
		printf("Error: incorrect number of parameters. Enter 2 parameters\n");
	else
	{
		int n = atoi(argv[1]),m = atoi(argv[2]),k,i,l,toss,a;		//creating variables to store
																	// n,m -- command line arguments
																	//k,i,l -- loop variables
																	//toss -- variable to store output of coin flip (heads= 1, tails = 0)
																	//a,b -- stores query input
		
		FILE *fout = fopen("intdata.dat","w");						//opening output file stream to intdata.dat (for integer data points)
																						
		printf("Case1: Integer Elements\n");

		for(k = n; k <= m; k++)										//looping over power of 2 in number of elements
		{	
			long long int num = pow(2,k);							//num -- number of elements in array
			int array[num];											//creating array of size num

			time_t t;
			srand((unsigned) time(&t));								//setting the seed for random function							

			clock_t start,stop;

			start = clock();										//storing the starting time 

			for(i=0; i<num; i++)									//assigning random integer values to the array
				array[i] = rand();

			for(i=0; i<10000; i++)									//looping over the 10000 queries
			{
				toss = rand()%2;									//performing the toss (heads= 1, tails = 0)

				if(toss)											//if it is HEAD, search for a random integer in the array
				{
					a = rand();
					for(l=0; l<num; l++)
					if(array[l] == a)
					break;
				}
				else 												//if it is a TAIL
				{
					a = array[rand()%num];							//set 'a' as a random element from the array													
					for(l=0; l<num; l++)							//and search for it
					if(array[l] == a)
					break;
				}
			}

			stop = clock();											//storing the ending time
			double time_taken = stop-start;							//finding time taken and 
			time_taken /= (CLOCKS_PER_SEC*10000);					//CLOCKS_PER_SEC and 10000 to get average time per query 
																	//in seconds

			printf("average time for num = %lld: %.10f \n", num,time_taken);
			fprintf(fout, "%lld %.10f\n",num,time_taken); 			//writing the time to file
		}
	fclose(fout);													//closing file pointer
	}

return 0;
}