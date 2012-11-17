#include<stdio.h>
#include<malloc.h>
#include "list.c"

/*
//Functions related to graphs
graph *create_node(int);//creating a node. Parameters: id
graph **create_empty_list(graph **, int );//creating an adjacency list. Parameter: adjlist, size
void print_list(graph **, int );//Printing the adjlist. Parameter: list, siz
void create_edge(int, int, graph **, int);//Creating an edge. Parameter: start, end, adjlist, size
void bfs(graph **, int, int *);//bfs of the list. Parameters: graph, id of starting element, distance	
void dfs(graph **, int , int *, int , int *);//dfs of the list. Parameters: graph, id of starting element, list of visited entries, dfn, dfn array
*/

//Functions related to this program	
void dfs_cycle(graph **, int , int *, int *);
	
main(){
	graph **adj_list;
	int n, m, n1, n2;

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
	print_list(adj_list, n);

	//Marking elements as visited
	int *visited,*parent;
	visited=(int *)malloc(n*sizeof(int));
	parent=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;++i){
		visited[i]=0;
		parent[i]=-1;
	}

	//Printing the connected componenets
	printf("\n\nThe cycles are: \n");
	for(i=0;i<n;++i){
		if(visited[i]==0){
			dfs_cycle(adj_list,i,visited,parent);
		}
	}
}


void dfs_cycle(graph **adj, int x, int *visited, int *parent){
	int id;//Temporarily store the id of element
	graph *temp;//Loop variable
	
	visited[x]=1;//Marking x as visited
	
	//Parsing through all the neighbours of x
	temp=adj[x]->next;
	while(temp!=NULL){
		id=temp->id;
		if(visited[id]==0){
			parent[id]=x;
			dfs_cycle(adj,id,visited,parent);
		}
		else if(visited[id]==1&&parent[id]!=x)
			//write statements for printing the cycle
		temp=temp->next;
	}
}
