/***********************************************************************************************************************
*                              Authors: Srijan R Shetty, Shouvik Sachdeva                                              *
*	               			   Roll nos: 11727, 11693                                  								   *			
*																				                                       *
* Program for: An efficient Data structure to store a sparse matrix.                                                   *
* 																				                                       *
* Important points:                                      *
***********************************************************************************************************************/

//Including necessary header files
#include<stdio.h>
#include<malloc.h>

/*The basic idea for using the following data structure is that every node row/column/value has two links, one to the 
next node in the series and one to the node just below it. We also store three values with every node. The data field
is exclusive for the value node while the row field stores the row index and the column one stores the column index; 
for a column index row field is set to zero and similar is the case for the column index*/

//Creating a structure to store the information of the data structure
struct NODE{
	int row;//To store the row index
	int column;//To store the column index
	int data;//To store the data for the value node
	struct NODE *right;//The right node
	struct NODE *down;//The left node
};

//Renaming structure for easier referncing
typedef struct NODE node;

//Function to create a new node with given data
node *create_node(int row, int column, int data);

//Function to create a matrix of size size
void create_mat(node* rows, node* columns, int size);

//Function to print a matrix
void print_mat(node* rows, node* columns);

main(){
	int size, row, column, mat, data, i;//necessary variables
	node *rows[2], *columns[2];//Row and Column list arrays to store both matrices conviniently
	node *temp, *temp_r[2], *temp_c;//Temporary nodes
		
	//Accepting the input from the user and creating the matrix
	scanf("%d", &size);
	for(i=0;i<2;++i){
		rows[i]=create_node(1,0,0);
		columns[i]=create_node(0,1,0);
		create_mat(rows[i], columns[i], size);
		temp_r[i]=rows[i];
	}
	
	scanf("%d %d %d %d", &mat, &row, &column, &data);
	while(mat!=0){
		mat=mat-1;//
		temp=create_node(row, column,data);
		temp_r[mat]->right=temp;
		for(i=1, temp_c=columns[mat];i<=column;++i,temp_c=temp_c->right);//Moving to the columnth column and linking it with the value node
		temp_c->down=temp;

		//Scanning entries again
		scanf("%d %d %d %d", &mat, &row, &column, &data);
	}
	print_mat(rows[0], columns[0]);
}

//Function to create a new node with given data
node *create_node(int row, int column, int data){
	node* temp;//Temporary node to store the newly created node
	temp->right=NULL;
	temp->down=NULL;
	temp->data=data;
	temp->row=row;
	temp->column=column;

	//Returning the created node
	return temp;
}

//Function to create a matrix of size size
void create_mat(node *rows, node *columns, int size){
	int i;//A loop control variable 
	node *temp, *temp1;
	
	//Creating a list for the rows & columns
	temp1=rows;//temp1 now points to rows head
	for(i=2;i<=size;++i){
		temp=create_node(0,i,0);
		temp1->down=temp;
		temp1=temp;
	}

	temp1=columns;//temp1 now points to column head
	for(i=2;i<=size;++i){
		temp=create_node(i,0,0);
		temp1->right=temp;
		temp1=temp;
	}
}

//Function to print a matrix
void print_mat(node *rows, node *columns){
	node *temp_r, *temp_c;//Loop control variables
	temp_r=rows;
	temp_c=columns;

	//Printing the elements
	while(temp_r!=NULL){
		printf("\n%d %d %d", temp_r->row, temp_r->column, temp_r->data);
		temp_c=temp_c->right;
		if(temp_c==NULL){
			temp_r=temp_r->down;
			temp_c=columns;
		}
	}
}



