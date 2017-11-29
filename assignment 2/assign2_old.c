#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10000
#define slot_size(a) (a.end - a.start + 1)

int array[MAX_SIZE];
int alength, flength, available_memory;
int key = 0; 

struct slot
{ 
	int start,end,index;

}allotted[MAX_SIZE], available[MAX_SIZE];


void initialize()
{
	int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		allotted[i].start = allotted[i].end = allotted[i].index = -1;
		available[i].start = available[i].end = available[i].index = -1;
	}
	available[0].start = 0;
	available[0].end = MAX_SIZE-1;

	alength = 0;
	flength = 1;
	available_memory = MAX_SIZE;
}

void collect_garbage()
{
	int i,j,k=0,temp;
	for(i=0; i<alength; i++)
	{
		temp = k;
		for(j=allotted[i].start; j<= allotted[i].end; j++)
		array[k++] = array[j];

		allotted[i].start = temp;
		allotted[i].end = k-1;
	}

	available[0].start = k;
	available[0].end = MAX_SIZE-1;
	flength = 1;
}

void delete(int index)
{
	int i,j,k;
	for(i=0; i<alength; i++)
	if(allotted[i].index == index)
	break;

	if(i == alength)
	printf("Index not available / already deleted\n");
	else
	{
		int l = allotted[i].start, u = allotted[i].end;
		alength--;
		available_memory += slot_size(allotted[i]);

		for(j=0; j<flength; j++)
		if(available[j].start > l)
		break;

		if(j>0 && j<flength && available[j-1].end == l-1 && available[j].start == u+1)
		{
			available[j-1].end = available[j].end;
			flength--;
			for(; j<flength; j++)
			available[j] = available[j+1];	
		}
		else if(j>0 && available[j-1].end == l-1)
		available[j-1].end = u;
		else if(j<flength && available[j].start == u+1)
		available[j].start = l;
		else
		{
			for(k=flength; k>j; k++)
			available[k] = available[k-1];
			available[j] = allotted[i];
		}

		for(; i<alength; i++)
		allotted[i] = allotted[i+1];
	}
}

int request(int required)
{
	if(required > available_memory)
		return -1;
	else
	{
		// receive input
		int i,min_possible = MAX_SIZE + 1,index = -1,k=-1;
		int input[required];

		printf("Enter the input:- \n");

		for(i=0; i<required; i++)
		scanf("%d", &input[i]);

		// check if you can add directly
		for(i = 0; i < flength; i++)
		{
			if(slot_size(available[i]) >= required && slot_size(available[i]) < min_possible)
			{
				min_possible = slot_size(available[i]);
				index = available[i].start;
				k = i;

				if(min_possible == required)
				break;
			}		
		}

		if(index != -1)
		{
			int j;
			for(j = index, i=0; i<required; j++,i++)
			array[j] = input[i];

			for(i = alength - 1; index < allotted[i].start; i--)
			allotted[i+1] = allotted[i];

			i++; 
			allotted[i].start = index; 
			allotted[i].end = index + required - 1;
			allotted[i].index = key++;

			alength++;
			available_memory -= required;

			if(min_possible != required)
				available[k].start += required;
			else
			{
				for(i=k; i<flength-1; i++)
				available[i] = available[i+1];
				flength--;
			}

		}
		else
		{
			collect_garbage();
			int j; 
			allotted[alength].start = available[0].start; 
			allotted[alength].end = allotted[alength].start + required - 1;
			allotted[alength].index = key++;
			alength++;

			for(i = available[0].start,j=0; j<required; i++, j++)
			array[i] = input[j];

			available[0].start = i;
			available_memory -= required;

			if(available_memory == 0)
				flength = 0;
		}
		return key;
	}	
}

void print()
{
	int i;
	if(alength == 0)
		printf("No allotted memory\n\n");
	else
	{
		printf("ALLOTTED MEMORY\nINDEX ----------- START ----------- END\n");
		for(i=0; i<alength; i++)
			printf("%d --------- %d --------- %d\n",allotted[i].index,allotted[i].start,allotted[i].end);
		printf("\n");
	}

	if(flength == 0)
		printf("No available memory\n\n");
	else
	{
		printf("AVAILABLE MEMORY\nSTART ----------- END\n");
		for(i=0; i<flength; i++)
			printf("%d --------- %d\n",available[i].start,available[i].end);
		printf("\n");
	}

	printf("Total available Memory = %d --- Alength = %d --- Flength = %d\n--------------------------\n\n",available_memory,alength,flength);
}

int main()
{
	initialize();
	int n,qtype,query;
	printf("Enter number of queries :- \n");
	scanf("%d",&n);
	print();
	while(n--)
	{
		printf("Enter Query Type and value :- \n");
		scanf("%d %d", &qtype, &query);
		if(qtype == 1)
			request(query);
		else
			delete(query);
		print();
	}

	return 0;
}
