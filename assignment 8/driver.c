/*								DISJOINT SET UNION
Implement disjoint set data structure with support for the following operations

1. Make_set ( x ) - To create a new set with element x

2. Find_set ( x ) - Find the set to which x belongs

3. Union (S1, S2) - Union of two sets S1 and S2

Also, provide an interactive interface through the terminal for the above operations. */


#include "disjoint_set.h"		//importing .h file with functions prototypes
#define MAX_SIZE 100000			//largest element that can belong to any set

int main()
{
	int c=1, val, val1;
	set* array[MAX_SIZE];		//array of pointers storing the address of each element's node
	initialize(array);			//initially all elements' addresses are NULL as there are no nodes

	while(c!=0)
	{
		printf("\n-----------------------------------------------\nEnter choice:- 1-Make_set; 2-Find_set; 3-Union; 0-Exit\n");
		scanf("%d",&c);

		switch(c)
		{
			case 0: break;
			case 1: printf("Enter element to make set\n");	//We create a new set (if not already present) with the given element 
					scanf("%d",&val);
					makeSet(array, val);
					break;
			case 2: printf("Enter element to find set\n");	//We find the leader of the set to which the element belongs (if it is present)
					scanf("%d",&val);
					findSet(array, val);
					break;
			case 3: printf("Enter elements to take union\n");// We perform union of the sets of the two elements (if they are present)
					scanf("%d",&val);
					scanf("%d",&val1);
					unionSet(array, val, val1);
					break;
			default: printf("Enter a correct option\n");
		}
	}
	return 0;
}