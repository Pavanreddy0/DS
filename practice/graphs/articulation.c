#include<stdio.h>
#include<malloc.h>
#include<limits.h>
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
void dfs_articulation(graph **, int , int , int *, int *, int *, int *);//Articulation points. Parameters: graph, start, count of dfn, dfn, visited, parrent, high_pt
int min(int,int);
	
main(){
	graph **adj_list;
	int n, m, n1, n2,count_dfn;
	count_dfn=-1;
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
	int *visited, *parent, *high_pt,*dfn;
	visited=(int *)malloc(n*sizeof(int));
	dfn=(int *)malloc(n*sizeof(int));
	high_pt=(int *)malloc(n*sizeof(int));
	parent=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;++i){
		parent[i]=0;
		high_pt[i]=0;
		visited[i]=0;
		dfn[i]=0;
	}

	//Printing the connected componenets
	printf("\n\nThe articulation points are: ");
	for(i=0;i<n;++i){
		if(visited[i]==0){
			dfs_articulation(adj_list,i,count_dfn,dfn,visited,parent,high_pt);
		}
	}
}

int min(int n1, int n2){
	if(n1<n2)
		return n1;
	else
		return n2;
}

void dfs_articulation(graph **adj, int x, int count_dfn, int *dfn, int *visited, int *parent, int *high_pt){
	//Initializing the parameters of the element
	visited[x]=1;
	count_dfn++;
	dfn[x]=count_dfn;
	high_pt[x]=INT_MAX;

	//Checking all the neighbours of the element
	graph *temp=adj[x]->next;
	int id;//To temporary store the id of the loop variable
	while(temp!=NULL){
		id=temp->id;
		if(visited[id]==0){
			parent[id]=x;
			dfs_articulation(adj,id,count_dfn,dfn,visited,parent,high_pt);
			high_pt[x]=min(high_pt[id],high_pt[x]);
			if(high_pt[id]>=dfn[x])
				printf("%d,",x);
		}
		else if(id!=parent[x])
			high_pt[x]=min(dfn[id],high_pt[x]);
		temp=temp->next;
	}
}
