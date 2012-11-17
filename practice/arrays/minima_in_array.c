#include<stdio.h>
#include<malloc.h>

main(){
	//DEclaring the neccessary variables
	int n;
	int A[6];//To store the numbers
	int i;
	n=6;

	//Asking the user for the array
	printf("\nEnter the elements of the array:\n");
	for(i=0;i<n;++i){
		scanf(" %d", &A[i]);
	}

	//Now checking for a local minima
	int mid;
	for(i=0;i<n;++i){
		mid=(n-i)/2;
		if((A[mid]<A[mid+1])&&(A[mid]<A[mid-1])){
			printf("\nLocal Minima at %d", (mid+1));
			break;
		}
		else if(A[mid+1]<A[mid]){
			i=mid+1;
		}
		else
			i=mid-1;
	}
}
