/*********************************************************************************************************************
*                                     Authors: Srijan R Shetty, Shouvik Sachdeva                                     *
*			                                 Roll nos: 11727, 11693                  							     *			
*																				                                     *
* Program: For implementing expression evaluation using stacks. 													 *
*                                                                                                                    *
**********************************************************************************************************************/

//Including necessary header files
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>

//The stack data structure
struct STACK{
	char op;
	double n;
	struct STACK *next;
};

//using typedef for ease of use
typedef struct STACK stack;

//Function prototypes

//Functions related to stacks
stack *create_node(double, char);//Cretaing a node parameters: number, operator
void push_number(double, stack **);//pushing a number to number stack parameters: number
void push_operator(char, stack **);//pushing an operator to operator stack parameters: operator
double top_number(stack *);//Top of number stack
char top_operator(stack *);//Top of operator stack
double pop_number(stack **);// pop function
char pop_operator(stack **);

//Function to compute the in stack and out stack priority of operators
int in_stack_priority(char);//Gives in stack prioirty. Parameters: operator
int in_stack_priority(char);//Gives out stack priority. Parameters: operator
void eval_exp(char *, int);//Evaluates expression. Parameters: expression, length
double compute(double, char, double);//Does infix computation. Parameters: n1, op, n2
void eval(stack **, stack **, double *, double *);//To update stacks. Parameters: n_stack, o_Stack, n1, n2

//main function
main(){
	//Asking the user to enter the expression
	char *exp;//To store the expression
	exp=(char*)malloc(10000*sizeof(char));
	printf("\nEnter the expression to be evaluated: ");
	
	//module to get the expression
	int len=0;
	char c;
	while(c=getchar(), c!='\n'){
		exp[len]=c;
		++len;
	}
	exp[len]='\0';	

	//Getting the result
	eval_exp(exp,len);
}

//Function definations

stack *create_node(double n, char op){
	//Creating a new temporary node
	stack *temp=(stack *)malloc(sizeof(stack));
	temp->n=n;
	temp->op=op;
	temp->next=NULL;

	return temp;
}

void push_number(double n, stack **n_stack){
	//Creating a temporay variable
	stack *temp;
	temp=create_node(n,'0');

	//Reallocating the pointers
	if(*n_stack==NULL)
		*n_stack=temp;
	else{
		temp->next=*n_stack;
		*n_stack=temp;
	}
}

void push_operator(char op, stack **o_stack){
	//Creating a temporay variable
	stack *temp;
	temp=create_node(0.0,op);

	//Reallocating the pointers
	if(*o_stack==NULL)
		*o_stack=temp;
	else{
		temp->next=*o_stack;
		*o_stack=temp;
	}
}

double top_number(stack *n_stack){
	return n_stack->n;
}

char top_operator(stack *o_stack){
	return o_stack->op;
}

double pop_number(stack **n_stack){
	//Rellocation the pointers
	stack *temp=*n_stack;
	double value=temp->n;
	*n_stack=temp->next;
	free(temp);//Freeing the not needed node

	//Returning the top element
	return value;
}

char pop_operator(stack **o_stack){
	//Rellocation the pointers
	stack *temp=*o_stack;
	char value=temp->op;
	*o_stack=temp->next;
	free(temp);//Freeing the not needed node

	//Returning the top element
	return value;
}

int isnotempty(stack *head){
	if(head!=NULL)
		return 1;
	else
		return 0;
}

int in_stack_priority(char op){
	//Using a switch case branch to return the priorities
	switch(op){
		case '{': return -1;
		case 'x':
		case 'y': return 6;
		case '=': return 0;
		case '(': return 1;
		case '+': 
		case '-': return 2;
		case '*':
		case '/': return 3;
		case '^': return 4;
	}
}

int out_stack_priority(char op){
	//Using a switch case branch to return the priorities
	switch(op){
		case 'x': 
		case 'y': return 9;
		case '=': return 8;
		case '+': 
		case '-': return 2;
		case '*':
		case '/': return 3;
		case '^': return 5;
		case '(': return 7;
	}
}

double compute(double n1, char op, double n2){
	//Evaluating the infix expression on the basis of the operator op
	double res;
	switch(op){
		case '+': res=n2+n1;
				  break;
		case '-': res=n2-n1;
				  break;
		case '*': res=n2*n1;
				  break;
		case '/': res=n2/n1;
				  break;
		case '^': res=pow(n2,n1);
				  break;
	}
    return res;//returning result
}

void eval(stack **n_stack, stack **o_stack, double *x, double *y){
	//Using easier names
	char op=top_operator(*o_stack);
	double n1, n2;
		
	//Checking the different cases for the top of the stack
	if(op=='='){
		pop_operator(&(*o_stack));
		if(pop_operator(&(*o_stack))=='x')
			*x=top_number(*n_stack);
		else
			*y=top_number(*n_stack);
	}
	else if(op=='x'){
		pop_operator(&(*o_stack));
		push_number(*x, &(*n_stack));
	}
	else if(op=='y'){
		pop_operator(&(*o_stack));
		push_number(*y, &(*n_stack));
	}
	else{//Push the computed result into the n_stack
		n1=pop_number(&(*n_stack));
		n2=pop_number(&(*n_stack));
		op=pop_operator(&(*o_stack));
		push_number(compute(n1, op, n2), &(*n_stack));
	}
}

void eval_exp(char *exp, int len){
	//Using two stacks
	stack *n_stack=NULL;//number stack
	int i=0;//counter for the above array
	double n;//To store the converted number
	char c;//To store the character in the expression
	double x=1.0, y=1.0;

	//Making changes so that the end and beginning of the exoression can be identified
	stack *o_stack=NULL;
	push_operator('{', &o_stack);;//initializing the first value of o_stack
	strcat(exp,"}");
	++len;

	while(isnotempty(o_stack)){
		c=exp[i];
		if(isdigit(c)){
			n=atof((exp+i));//Getting the entire number
			while(isdigit(c)||c=='.'){
				++i;
				c=exp[i];
			}
			--i;//The last increment takes an extra character from the expression

			//Pushing into n stack
			push_number(n, &n_stack);
		}
		else{
			if(c=='}'){//End of the expression
				while(top_operator(o_stack)!='{'){
					//Updating stacks after computation
					eval(&n_stack, &o_stack, &x, &y);
				}
				pop_operator(&o_stack);//poping the '{' from the o_stack
			}
			else if(c==')'){//Priority of parenthesis
				while(top_operator(o_stack)!='('){
					//updating stacks after computation
					eval(&n_stack, &o_stack, &x, &y);
				}
				pop_operator(&o_stack);//popping the '(' operator from the o_stack
			}
			else if(in_stack_priority(top_operator(o_stack))>=out_stack_priority(c)){
				do{
					//Pooping elements and taking temporary values
					eval(&n_stack, &o_stack, &x, &y);
				}while(in_stack_priority(top_operator(o_stack))>=out_stack_priority(c));
				push_operator(c, &o_stack);//Pushing the new operator into the o_stack
			}
			else{//Pushing the operator in the o_stack
				push_operator(c, &o_stack);
			}
		}
		++i;//incrementing the counter
	}

	//returning the final result
	printf("\nThe value of x is %lf and y is %lf.\nThe value of the expression is: %lf\n", x, y, pop_number(&n_stack));
}
