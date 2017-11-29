#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_VAL 20

typedef long long int ll;

struct node
{
	int value;
	struct node *next;
};

void print(struct node *ptrarray[], ll n, int j)
{
	ll i;
	printf("%4d     ", j);
	for(i=0; i<=n; i++)
		printf("%4d\t", ptrarray[i] -> value);
	printf("\n");
}

int main(int argc, char** argv)
{
	if(argc != 2)													//check if the correct number of arguments have been provided
		printf("Error: incorrect number of parameters. Enter 1 parameter\n");
	else
	{
		time_t t;
		srand((unsigned) time(&t));
		ll n = pow(2, atoi(argv[1])),i;
		struct node *ptrarray[n+1];

		ptrarray[0] = (struct node*)malloc(sizeof(struct node));
		ptrarray[0] -> value = rand() % MAX_VAL;

		for(i=1; i<n; i++)
		{
			ptrarray[i] = (struct node*)malloc(sizeof(struct node));
			ptrarray[i] -> value = rand() % MAX_VAL;
			ptrarray[i-1] -> next = ptrarray[i];
		}
		ptrarray[n] = (struct node*)malloc(sizeof(struct node));
		ptrarray[n] -> value = 0;
		ptrarray[n-1] -> next = ptrarray[n];

		printf("Iteration");
		for(i=1; i<=n; i++)
			printf("%4lld\t", i);
		printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

		print(ptrarray, n, 0);
		int k = atoi(argv[1]),j;

		for(j=1; j<=k; j++)
		{
			for(i=0; ptrarray[i] -> next != NULL; i++)
			{
				(ptrarray[i] -> value) += ((ptrarray[i] -> next) -> value); 
				(ptrarray[i] -> next) = ((ptrarray[i] -> next) -> next);
			}
			print(ptrarray, n, j);
		}
	}
	return 0;
}