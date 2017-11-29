/* 
		This header file contains the definition of the structure
		"QNode" and "Queue" and also prototypes of all functions that are
		used in the queue. The definitions of these functions
		are available in file "queue.c"
																		*/
	
typedef struct QNode 												// linked list data structure holding node* values
{
    node* element;
    struct QNode *next;
} QNode;
 
// The queue, front stores the front node of LL and rear stores ths
typedef struct Queue
{
    struct QNode *front, *rear;
} Queue;
 
QNode* QnewNode(node* key);											//function to initialize qnode
Queue *createQueue();												//function to initialize queue
void enQueue(Queue *q, node* key);									//function to enqueue
QNode *deQueue(Queue *q);											//function to dequeue