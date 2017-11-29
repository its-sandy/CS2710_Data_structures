/******************************************* SORTING  ******************************************
									
									  --PROBLEM STATEMENT--

	Write a program to implement mergesort and quicksort based on the user's preference

************************************************************************************************/

// importing header files 
#include <stdio.h>
#include <stdlib.h>

void quicksort(int array[], int low, int high)
{
	/* Function to implement quicksort
			array 	  -> array to be sorted
			low, high -> range of elements which have to be sorted */

	if(low < high)										// If low == high, it is the single element base case (already sorted) 
	{
		int pivot = rand()%(high - low + 1) + low;		// pivot index is a random index in the given range
		int i = low, j = high-1, temp;					// i,j mark the partitioned part of the array

		temp = array[high];								// swap the pivot element with the last element in range
		array[high] = array[pivot];
		array[pivot] = temp;

		while(i <= j)									// while left index is not more than right index
		{
			while(array[i] < array[high])				// we move i to the right till we get an element >= pivot element
				i++;
			while(array[j] > array[high])				// we move j to the left till we get an element <= pivot element
				j--;

			if(i>j)										// if i gets to the left of j, we break
			break;

			temp = array[i];							// swap the ith and jth elements to maintain the partition
			array[i] = array[j];
			array[j] = temp;
			i++;										// i and j are moved to the next elements
			j--;
		}

		j++;											// j is moved to indicate the left most element partition of elements >= pivot element
		temp = array[j];								// swap element at j with pivot element
		array[j] = array[high];
		array[high] = temp;								// pivot element is now in it's sorted location

		quicksort(array,low,j-1);						// recursively sort the elements <= pivot element
		quicksort(array,j+1,high);						// recursively sort the elements >= pivot element
	}
}

void mergesort(int array[], int low, int high, int c)
{
	/* Function to implement mergesort
			array 	  -> array to be sorted
			low, high -> range of elements which have to be sorted
			c         -> merging technique to be used           */

	if(low < high)										// If low == high, it is the single element base case (already sorted) 
	{
		int mid = (low+high)/2;							// we use mid to divide the range into two halves
		mergesort(array, low, mid, c);						// we recursively sort the elements of each half
		mergesort(array, mid+1, high, c);

		
		if(c == 1)										// merging with O(n) extra space
		{
			int temp[high - low + 1], i = low, j = mid+1, k=0;		// temp is the temporary array used to merge the 2 sorted halves
																	// temp allows merging in O(range) time
			while(i <= mid && j <= high)				// while the 2 halves are not empty, we compare the first elements and 
			{											// keep adding them to temp
				if(array[i] > array[j])
					temp[k++] = array[j++];
				else
					temp[k++] = array[i++];
			}

			while( i <= mid)							// we add the left out elements consecutively to temp
				temp[k++] = array[i++];

			while( j <= high)
				temp[k++] = array[j++];
		}
		else 											// merging with O(1) extra space and 
		{												// time complexity O((range of 1st half) * (range of 2nd half))
			int i,j,temp;
			for(i = mid; i >= low; i--)					// using insertion sort like technique to insert each element of 1st half into the 2nd
			{
				temp = array[i];						// temporary variable to store the valur
				j = i+1;
				while(j <= high && array[j] < temp)		// we keep pushing elements backward as long as they are smaller than temp
				{
					array[j-1] = array[j];
					j++;
				}	

				array[j-1] = temp;						// we insert temp back at the correct spot
			}
		}
	}
}


int main()
{
	int m,n,i,c;
	printf("Choose sorting method (0 - Mergesort; 1 - Quicksort) :- \n");
	scanf("%d",&m);										// decides the sorting technique

	if(m == 0)
	{
		printf("Choose merging method (0 - O(1) extra space; 1 - O(n) extra space) :- \n");
		scanf("%d",&c);									// decides the mering technique used in mergesort
	}
	printf("Enter number of elements :- \n");			
	scanf("%d",&n);										// stores number of elements in array
	int array[n];										// array to be sorted

	printf("\nEnter elements:- \n");					// getting array input
	for(i=0; i<n; i++)
	scanf("%d",&array[i]);

	if(m = 1)											// calling sorting technique based on option chosen
		quicksort(array, 0, n-1);
	else
		mergesort(array, 0, n-1, c);

	printf("\nSorted Array :- \n");						// printing the sorted array

	for(i=0; i<n; i++)
	printf("%d  ",array[i]);
	printf("\n");

	return 0;
}