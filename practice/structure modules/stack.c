/*********************************************************************************************************************
*                                     Authors: Srijan R Shetty 														 *
*																				                                     *
* Program: For implementing expression evaluation using stacks. 													 *
*                                                                                                                    *
**********************************************************************************************************************/
#ifndef malloc
	#include<malloc.h>
#endif
#ifndef stdio
	#include<stdio.h>
#endif


//The stack data structure
struct STACK{
	int n;
	struct STACK *next;
};

//using typedef for ease of use
typedef struct STACK stack;

//Function prototypes

//Functions related to stacks
stack *create_node_stack(int);//Cretaing a node. parameters: number
void push(int, stack **);//pushing a to number stack parameters: number, stack top
int top(stack *);//Top of stack. parameter: stack top
int pop(stack **);// pop function. Parameter: address of stack top
int isnotempty_stack(stack *);//Is not empty stack. Parameter: stack

stack *create_node_stack(int n){
	//Creating a new temporary node
	stack *temp=(stack *)malloc(sizeof(stack));
	temp->n=n;
	temp->next=NULL;

	return temp;
}

void push(int n, stack **n_stack){
	//Creating a temporay variable
	stack *temp;
	temp=create_node_stack(n);

	//Reallocating the pointers
	if(*n_stack==NULL)
		*n_stack=temp;
	else{
		temp->next=*n_stack;
		*n_stack=temp;
	}
}

int top(stack *n_stack){
	return n_stack->n;
}

int pop(stack **n_stack){
	//Rellocation the pointers
	stack *temp=*n_stack;
	int value=temp->n;
	*n_stack=temp->next;
	free(temp);//Freeing the not needed node

	//Returning the top element
	return value;
}

int isnotempty_stack(stack *head){
	if(head!=NULL)
		return 1;
	else
		return 0;
}
