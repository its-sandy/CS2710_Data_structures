/***************************************GARBAGE COLLECTOR***************************************
									
									  --PROBLEM STATEMENT--

	Write a program to create an abstract dynamic data structure that can :-
		1) allocate a specified amount of memory and return an index associated to it
		2) delete the memory allocated by taking the associated index as input
		3) execute garbage collection whenever required memory is not directly available

************************************************************************************************/

// importing header files 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000												// total memory available for storage
#define slot_size(a) (a.end - a.start + 1)							// macro to give the size of slot from starting and ending locations

int array[MAX_SIZE];												// array used to implement the data structure
int alength, flength, available_memory;								// alength - number of allotted slots; flength - number of free/available slots;
int key = 0; 														// available_memory - currently available memory; key - used to assign index to slots;

struct slot 														// structure used to represent each memory slot/section
{ 																	// contains starting location, ending location and index of slot
	int start,end,index;							

}allotted[MAX_SIZE], available[MAX_SIZE];							// two helper arrays to store allotted and available slots in order 
																	// of increasing start locations

void initialize()													// function to initialize the abstract data structure
{
	int i;
	for(i=0; i<MAX_SIZE; i++)										// clearing the contents of available and allotted arrays
	{
		allotted[i].start = allotted[i].end = allotted[i].index = -1;
		available[i].start = available[i].end = available[i].index = -1;
	}
	available[0].start = 0;											// in the beginning, there is just one available slot that spans 
	available[0].end = MAX_SIZE-1;									// the whole length of array (MAX_LENGTH)

	alength = 0;													// in the beginning, there are no allotted slots
	flength = 1;
	available_memory = MAX_SIZE;
}

void collect_garbage()												// function for garbage collection
{
	int i,j,k=0,temp;												// All allotted data is pushed to the front of array to create more space
	for(i=0; i<alength; i++)										// loop to cover each allotted slots
	{
		temp = k;
		for(j=allotted[i].start; j<= allotted[i].end; j++)			// Data of each allotted slot is shifted to the front
		array[k++] = array[j];

		allotted[i].start = temp;									// The start and end locations of each allotted slot are updated
		allotted[i].end = k-1;										// to their new locations
	}

	available[0].start = k;											// At the end of garbage collection, there is only one available slot
	available[0].end = MAX_SIZE-1;									// that extends from the first free location, to the end of array
	flength = 1;
}

void delete(int index)												// Delete function to delete an available slot based on index
{
	int i,j,k;
	for(i=0; i<alength; i++)										// Searches the allotted array to check if given index exists
	if(allotted[i].index == index)
	break;

	if(i == alength)												// If index does not exist
	printf("Index not available / already deleted\n\n");
	else															// If the index is present
	{
		int l = allotted[i].start, u = allotted[i].end;				// variables to store start and ed of deleted slot
		alength--;													// number of allotted slots reduces by 1
		available_memory += slot_size(allotted[i]);					// currently available memory increases by the deleted slot's size

		for(j=0; j<flength; j++)									// Find the free slot just after slot to be deleted
		if(available[j].start > l)
		break;

		if(j>0 && j<flength && available[j-1].end == l-1 && available[j].start == u+1)	// If the deleted slot can be combined with 
		{																				// free slots at both ends to create one free slot
			available[j-1].end = available[j].end;
			flength--;												// Number of free slots reduces by 1
			for(; j<flength; j++)								
			available[j] = available[j+1];							// shift back the available slots
		}
		else if(j>0 && available[j-1].end == l-1)					// If deleted slot can be combined with one free slot at start location
		available[j-1].end = u;										// extend the free slot
		else if(j<flength && available[j].start == u+1)				// If deleted slot can be combined with one free slot at end location
		available[j].start = l;										// extend the free slot
		else														// If deleted slot cannot be combined with any free slot
		{
			for(k=flength; k>j; k++)
			available[k] = available[k-1];
			available[j] = allotted[i];								// a new free slot is created. It has same start and end location as 
			flength++;												// the deleted slot 
		}

		for(; i<alength; i++)										// shift the allotteed slot to maintain order
		allotted[i] = allotted[i+1];
	}
}

void request(int required)											// Function to allocate requested amount of memory
{
	if(required > available_memory)									// checks if required memory is available
		printf("Required memory not available\n\n");
	else
	{
		int i,min_possible = MAX_SIZE + 1,index = -1,k=-1;
		int input[required];

		for(i=0; i<required; i++)									// Generates random integers to store in the newly allotted slot
		input[i] = rand();

		for(i = 0; i < flength; i++)								// Loops over the available free slots to check if they are large
		{															// enough to store required memory
			if(slot_size(available[i]) >= required && slot_size(available[i]) < min_possible)
			{
				min_possible = slot_size(available[i]);				// Among the possible free slots, the one with smallest size is 
				index = available[i].start;							// selected. This is done to minimize number of Garbage Collection steps
				k = i;												// Stores index of chosen free slot	

				if(min_possible == required)						// breaks if slot size is exactly as required (best case)
				break;
			}		
		}

		if(index != -1)												// If garbage collection is not required
		{
			int j;
			for(j = index, i=0; i<required; j++,i++)				// Stores input into the array
			array[j] = input[i];

			for(i = alength - 1; i>=0 && index < allotted[i].start; i--)	// makes update to allotted list, ensuring order is maintained
			allotted[i+1] = allotted[i];

			i++; 
			allotted[i].start = index; 								// Adds the new slot to allotted array
			allotted[i].end = index + required - 1;
			allotted[i].index = ++key;								// index is assigned based on the global counter "key"

			alength++;												// update number of allotted slots and currently available memory
			available_memory -= required;

			if(min_possible != required)							// checks if the free slot that was used is completely filled
				available[k].start += required;						// updates start position of free slot
			else
			{
				for(i=k; i<flength-1; i++)							// if the free slot is completely used, it is removed from available array
				available[i] = available[i+1];
				flength--;
			}
		}
		else														// If garbage collection is required
		{
			collect_garbage();										// executes garbage collection
			int j; 
			allotted[alength].start = available[0].start; 			// adds the new slot at the last and only free slot
			allotted[alength].end = allotted[alength].start + required - 1;
			allotted[alength].index = ++key;						
			alength++;

			for(i = available[0].start,j=0; j<required; i++, j++)	// stores input into the array
			array[i] = input[j];

			available[0].start = i;									// updates the only free slot existing
			available_memory -= required;

			if(available_memory == 0)								// If no memory is available, change flength to 0
				flength = 0;
		}
		printf("Index allotted = %d\n\n",key);						// Outputs the index assigned to the new slot
	}	
}

void print()
{
	int i;
	if(alength == 0)												// Printing the Allotted Slots array
		printf("NO ALLOTTED MEMORY\n\n");
	else
	{
		printf("ALLOTTED MEMORY\nINDEX ----------- START ----------- END\n");
		for(i=0; i<alength; i++)
			printf("%5d ----------- %5d ----------- %5d\n",allotted[i].index,allotted[i].start,allotted[i].end);
		printf("\n");
	}

	if(flength == 0)												// Printing the Available Slots array
		printf("NO AVAILABLE MEMORY\n\n");
	else
	{
		printf("AVAILABLE MEMORY\nSTART ----------- END\n");
		for(i=0; i<flength; i++)
			printf("%5d ----------- %5d\n",available[i].start,available[i].end);
		printf("\n");
	}

	printf("Total available Memory = %d --- Alength = %d --- Flength = %d\n\n",available_memory,alength,flength);
	printf("********************************************************************\n\n");
}

int main()
{
	time_t t;
	srand((unsigned) time(&t));										// setting the seed for random function							
	initialize();													// initializing the absract data structure
	int n,qtype,query;
	printf("Enter number of queries :- \n");						// getting number of queries
	scanf("%d",&n);
	print();														// printing initial state of data structure
	while(n--)														// looping over each query	
	{
		printf("Enter Query Type and value :- \n");				
		scanf("%d %d", &qtype, &query);
		if(qtype == 1)												// query type 1 corresponds to request 
			request(query);
		else														// query type 2 corresponds to delete 
			delete(query);
		print();													// printing the current state of data structure after every query
	}

	return 0;
}
