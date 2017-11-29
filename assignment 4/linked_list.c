/*
		Contains definitions for the functions required to execute a
		singely linked list of integer elements
														*/

// importing header files
#include<stdio.h>										
#include<stdlib.h>										
#include "linked_list.h"								//	Header file containing definition of linked list 
														// data structure and related function prototypes

void insertNode(node* end, int val) 					// Function to insert new node of given value at the end of linked list
{
	node* temp = (node*)malloc(sizeof(node));			//	Allocating memory for new node and storing value, next
	temp->value = val;									
	temp->next = NULL;									
	end->next = temp;									//	new node becomes the node after previous end node
}

void printNodes(node* head)								// Function to print value of nodes in the linked list
{
	node* temp = head;
	while(temp->next != NULL)							// we loop through all the nodes
	{
		printf("%d ,",temp->value);						
		temp = temp->next;								// jumping to the next node
	}
	printf("%d \n\n",temp->value);						// last node printed separately to avoid the trailing comma 
}

void freeNodes(node* head)								// function to free the memory allocated to the linked list
{
	node* temp;
	while(head!=NULL)									// we loop through all the nodes till we reach NULL
	{
		temp = head->next;								// we use "temp" to keep track of the next node to be deleted
		free(head);										// current node is freed
		head = temp;
	}
}