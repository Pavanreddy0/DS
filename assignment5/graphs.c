#include<malloc.h>
#include<limits.h>
#include<stdio.h>
	
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
int dequeue(queue **,queue **);//Dequeue function. Parameters: add of front, add of rear
	
//Requred functions
int min(int, int);//Computes minimum of two numbers

//Adjacency list representation of a graph
struct GRAPH{
	int id;
	struct GRAPH* next;
};

//typedef for easier use
typedef struct GRAPH graph;

//Function prototypes
//Functions related to graphs
graph *create_node(int);//creating a node. Parameters: id
graph **create_empty_list(graph **, int );//creating an adjacency list. Parameter: adjlist, size
void print_list(graph **, int );//Printing the adjlist. Parameter: list, siz
void create_edge(int, int, graph **, int);//Creating an edge. Parameter: start, end, adjlist, size
void dfs(graph **, int , int , int *, int *, int *, int *, int*, queue **, queue**, int *, int, int*);

main(){
	graph **adj_list;
	int n, m, n1, n2,count_dfn,count_con;
	
	//Creating the adjacency list
	scanf("%d %d", &n, &m);
	adj_list=create_empty_list(adj_list, n);
	
	//Creating edges
	int i;
	for(i=0;i<m;++i){
		scanf("%d %d", &n1, &n2);
		create_edge(n1,n2,adj_list,n);
		create_edge(n2,n1,adj_list,n);
	}

	//Initializing the needed arrays
	int *visited, *parent, *high_pt,*dfn,*ap,*label,*bridge;
	queue *con_h,*con_t;//Queue to store the connected components
	con_h=NULL;
	con_t=NULL;
	dfn=(int *)malloc(n*sizeof(int));
	visited=(int *)malloc(n*sizeof(int));
	label=(int *)malloc(n*sizeof(int));
	high_pt=(int *)malloc(n*sizeof(int));
	parent=(int *)malloc(n*sizeof(int));
	bridge=(int *)malloc(n*sizeof(int));
	ap=(int *)malloc(n*sizeof(int));//articulation point
	for(i=0;i<n;++i){
		parent[i]=-1;
		high_pt[i]=0;
		visited[i]=0;
		dfn[i]=0;
		ap[i]=0;
		label[i]=0;
		bridge[i]=-1;
	}
	count_dfn=-1;//Stores the dfn count 
	count_con=0;//Stores the connected component count

	//Performing computations on the DFS tree
	for(i=0;i<n;++i){
		if(visited[i]==0){
			count_con++;
			label[i]=count_con;
			dfs(adj_list,i,count_dfn,dfn,visited,parent,high_pt,ap,&con_h,&con_t,label,count_con,bridge);
		}
	}

	//Printing the results
	//Connected componenets
	printf("\nThere are %d connected componenets in the graph.\nThese are: {", count_con);
	queue *temp1,*temp2;//Loop variables
	temp1=con_h;
	printf("%d,",temp1->n);//Printing the first element
	for(temp2=con_h->next;temp2!=NULL;temp1=temp1->next,temp2=temp2->next){
		if(label[temp1->n]==label[temp2->n])
			printf("%d,",temp2->n);
		else{
			printf("\b}, {%d,",temp2->n);
		}
	}
	printf("\b}");

	//Articulation points
	printf("\nThe articualtion points are: ");
	for(i=0;i<n;++i){
		if(ap[i]==1)
			printf("%d,",i);
	}
	printf("\b ");

	printf("\nThe bridges are: ");
	for(i=0;i<n;++i){
		if(bridge[i]!=-1)
			printf("(%d,%d),",bridge[i],i);
	}
	printf("\b \n");


}

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

int min(int n1, int n2){
	if(n1<n2)
		return n1;
	else
		return n2;
}

graph *create_node(int id){
	graph *temp;
	temp=(graph *)malloc(sizeof(graph));
	
	temp->id=id;
	temp->next=NULL;
}

graph **create_empty_list(graph **adj_list, int size){
	//Allocating size for the adjacency list
	adj_list=(graph **)malloc(size*sizeof(graph));

	//Intializing each entry
	int i;
	for(i=0;i<size;++i){
		adj_list[i]=create_node(i);
	}

	return adj_list;
}

void create_edge(int start, int end, graph **adj, int size){
	//inserting new vertices at the end of the list
	graph *loop, *node, *temp;

	if(start==end)//For same edge
		return;
			
	//Making an edge from start to end
	loop=adj[start];
	node=create_node(end);
	
	if(adj[start]->next==NULL)
		loop->next=node;
	else{
		if((adj[start]->next->id)>end)
			loop=adj[start];	
		else{
			while(loop->next!=NULL){
				if(end<(loop->next->id))
					break;
				else if(end==(loop->next->id))
					return;
				loop=loop->next;
			}
		}
		
		temp=loop->next;
		loop->next=node;
		node->next=temp;
	}
}

void dfs(graph **adj, int x, int count_dfn, int *dfn, int *visited, int *parent, int *high_pt,int *ap,queue **con_h, queue **con_t, int *label, int count_con,int *bridge){
	//Initializing the parameters of the element
	enqueue(x,&(*con_h),&(*con_t));
	visited[x]=1;
	high_pt[x]=x;
	count_dfn++;
	dfn[x]=count_dfn;

	//Checking all the neighbours of the element
	graph *temp=adj[x]->next;
	int id;//To temporary store the id of the loop variable
	while(temp!=NULL){
		id=temp->id;//id of neighbour
		if(visited[id]==0){//In case id is a child
			label[id]=count_con;//Giving same label to connected componenets
			parent[id]=x;//assigning parent
			dfs(adj,id,count_dfn,dfn,visited,parent,high_pt,ap,&(*con_h),&(*con_t),label,count_con,bridge);//recursive dfs call
			high_pt[x]=min(high_pt[id],high_pt[x]);//recomputing high_pt
			if((high_pt[id]>=dfn[x])&&parent[x]!=-1)
				ap[x]=1;
			if(high_pt[id]>dfn[x]){	
					bridge[id]=x;
			}
		}
		else if(id!=parent[x])//In case id is an ancestor
			high_pt[x]=min(dfn[id],high_pt[x]);
		temp=temp->next;
	}
}
