#ifndef malloc
	#include<malloc.h>
#endif

//Function prototypes	
void swap(int *, int, int);//Function to swap elements in a string. Parameters: string, src, destination
void permute(int *, int, int);//Parameters: string, start, size

void swap(int *string, int i, int j){
	int temp=string[i];
	string[i]=string[j];
	string[j]=temp;
}

void permute(int *string, int i, int n){
	//Base case
	if(i==n){
		int k;
		printf("\n");
		for(k=0;k<=n;++k){
			printf("%d ", string[k]);
		}
	}

	//Permuting through the string
	int j;
	for(j=i;j<=n;++j){
		swap(string, i, j);
		permute(string, (i+1), n);
		swap(string, i, j);
	}
}
