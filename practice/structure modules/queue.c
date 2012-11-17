/*********************************************************************************************************************
*                                     Authors: Srijan R Shetty 														 *
*																				                                     *
* Program: For implementing queues. 																				 *
*                                                                                                                    *
**********************************************************************************************************************/
#ifndef malloc
	#include<malloc.h>
#endif
#ifndef stdio
		#include<stdio.h>
#endif


//The queue data structure
struct QUEUE{
	int n;
	struct QUEUE *next;
};

//using typedef for ease of use
typedef struct QUEUE queue;

//Functions related to queues
queue *create_node_queue(int);//Cretaing a node. parameters: number
void enqueue(int, queue **, queue **);//Enqueue a number to the queue. Parameters: number, add of front, add of rear
int get_front(queue *);//Front of queue. parameter: front
int get_rear(queue *);//Rear of queue. parameters: rear
int dequeue(queue **,queue **);//Dequeue function. Parameters: add of front, add of rear
int isnotempty_queue(queue *);//checks if queue is empty. Parameters: front
	
queue *create_node_queue(int n){
	//Creating a new temporary node
	queue *temp=(queue *)malloc(sizeof(queue));
	temp->n=n;
	temp->next=NULL;

	return temp;
}

void enqueue(int n, queue **front, queue **rear){
	//Creating a temporay variable
	queue *temp;
	temp=create_node_queue(n);

	//Reallocating the pointers
	if(*rear==NULL){
		*rear=temp;
		*front=temp;
	}
	else{
		(*rear)->next=temp;
		*rear=temp;
	}
}

int get_front(queue *front){
	return front->n;
}

int get_rear(queue *rear){
	return rear->n;
}

int dequeue(queue **front, queue **rear){
	//Rellocation the pointers
	queue *temp=*front;
	int value=temp->n;
	(*front)=temp->next;

	//Checking for empty
	if((*front)==NULL){
		(*rear)=NULL;
	}

	free(temp);//Freeing the not needed node

	//Returning the top element
	return value;
}

int isnotempty_queue(queue *front){
	if(front!=NULL)
		return 1;
	else
		return 0;
}
