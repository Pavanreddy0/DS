#ifndef malloc
	#include<malloc.h>
#endif
#ifndef limits
	#include<limits.h>
#endif
#ifndef stdio
		#include<stdio.h>
#endif

#include "queue.c"

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
void bfs(graph **, int, int *);//bfs of the list. Parameters: graph, id of starting element, distance	
void dfs(graph **, int , int *, int , int *);//dfs of the list. Parameters: graph, id of starting element, list of visited entries, dfn, dfn array
	
//Functions from other files
/*
queue *create_node_queue(int);//Cretaing a node. parameters: number
void enqueue(int, queue **, queue **);//Enqueue a number to the queue. Parameters: number, add of front, add of rear
int get_front(queue *);//Front of queue. parameter: front
int get_rear(queue *);//Rear of queue. parameters: rear
int dequeue(queue **,queue **);//Dequeue function. Parameters: add of front, add of rear
int isnotempty(queue *);//checks if queue is empty. Parameters: front
*/	

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

void print_list(graph **adj, int size){
	//Intializing each entry
	int i;
	graph *temp;
	for(i=0;i<size;++i){
		printf("\n%d", adj[i]->id);	
		if(adj[i]->next!=NULL){
			temp=adj[i];
			do{
				printf("->%d", temp->next->id);
				temp=temp->next;
			}while(temp->next!=NULL);
			printf("->NULL");
		}
		else
			printf("->NULL");
	}
	printf("\n");
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

void bfs(graph **adj, int x, int *distance){
	int pos,id;//to store the temporary's variables id
	graph *temp;//variable to store dequeue element
	//Initializing visited as true
	distance[x]=0;
	
	//creating an empty queue and adding x to it	
	queue *front=NULL;
	queue *rear=NULL;
	enqueue(x, &front, &rear);

	//Going through the entire list
	while(isnotempty_queue(front)){
		id=dequeue(&front,&rear);
		temp=adj[id]->next;
		while(temp!=NULL){
			pos=temp->id;
			if(distance[pos]==INT_MAX){
				enqueue(pos,&front,&rear);
				distance[pos]=distance[id]+1;
			}
			temp=temp->next;
		}
	}
}

void dfs(graph **adj, int x, int *visited, int count_dfn, int *dfn){
	int id;//Temporarily store the id of element
	graph *temp;//Loop variable
	
	visited[x]=1;//Marking x as visited
	dfn[x]=count_dfn++;//Updating the dfn value of element
	
	//Parsing through all the neighbours of x
	temp=adj[x]->next;
	while(temp!=NULL){
		id=temp->id;
		if(visited[id]==0){
			dfs(adj,id,visited,count_dfn,dfn);
		}
		temp=temp->next;
	}
}
