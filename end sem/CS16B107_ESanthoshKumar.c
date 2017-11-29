#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

typedef struct heapElement
{
	int value;
	int llimit;
	int rlimit;
} heapElement;

void initializeHeap(int array[], heapElement heap[], int n)
{
	int i;

	for(i=n/2; i<n; i++)
	{
		heap[i].value = array[2*i - n] + array[2*i - n + 1];
		heap[i].llimit = 2*i - n;
		heap[i].rlimit = 2*i - n + 1;
	}

	for(i=n/2 - 1; i>0; i--)
	{
		heap[i].value = heap[2*i].value + heap[2*i + 1].value;
		heap[i].llimit = heap[2*i].llimit;
		heap[i].rlimit = heap[2*i+1].rlimit;
	}
}

int preSum(int array[], heapElement heap[], int n, int k, int node)
{
	if(node < n/2)
	{
		if(heap[node].rlimit <= k)
			return heap[node].value;
		else if(heap[node].llimit > k)
			return 0;
		else
			return preSum(array, heap, n, k, 2*node) + preSum(array, heap, n, k, 2*node+1);
	}
	else if(node < n)
	{
		if(heap[node].rlimit <= k)
			return heap[node].value;
		else if(heap[node].llimit > k)
			return 0;
		else
			return array[2*node - n];	
	}
}

void addValue(int array[], heapElement heap[], int n, int p, int k)
{
	array[k] += p;
	int i = (n+k)/2;

	while(i > 0)
	{
		heap[i].value += p;
		i/=2;
	}
}

void printHeap(int array[], heapElement heap[], int n)
{
	int i;
	printf("Array:-\n");
	for(i=0; i<n; i++)
		printf("%d  ",array[i]);
	printf("\nHeap:-\n");
	for(i=1; i<n; i++)
		printf("%d(%d,%d) ",heap[i].value, heap[i].llimit, heap[i].rlimit);
	printf("\n");
}
//comment
int main()
{
	int n = 32;
	clock_t start,stop;
	double time_taken;
	FILE *fout2 = fopen("averagetime.dat","w");

	while(n <= 1024*256)
	{
		int array[n], i, c;
		heapElement heap[n];

		time_t t;
		srand((unsigned) time(&t));

		for(i=0; i<n; i++)
			array[i] = rand()%MAX_SIZE;

		initializeHeap(array, heap, n);

		start = clock();
		for(i=0; i<n; i++)
		{
			if(rand()%2 == 0)
				addValue(array, heap, n, rand()%MAX_SIZE, rand()%n);
			else
				preSum(array, heap, n, rand()%n, 1);
		}
		stop = clock();

		time_taken = (double)(stop - start)/CLOCKS_PER_SEC;
		printf("Insert No. = %d --- Total Time Taken = %.10f --- Average Time Taken = %.10f\n",n,time_taken,time_taken/n);
		fprintf(fout2, "%d %.10f\n",n,time_taken/n);
		n*=2;

	}
	//fout2.close();

	return 0;
}
