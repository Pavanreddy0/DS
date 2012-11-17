//Program to implement merge sort
#ifndef malloc
	#include<malloc.h>
#endif

//Function prototypes
void merge(int*, int, int*, int, int *);//Function to merge two arrays. Parameters: source, source, destination
void merge_sort(int *, int, int);//Merge Sort function. Parameters: Array, start, end 

void merge(int *A, int n1, int *B, int n2, int *C){
	int i=0,j=0,k=0;//Loop variables
	while(i<n1 &&j<n2){
		if(A[i]<B[j]){
			C[k]=A[i];
			++k;++i;
		}
		else if(B[j]<A[i]){
			C[k]=B[j];
			++k;++j;
		}
		else{//Both equal
			C[k]=B[j];
			++k;++j;
			C[k]=A[i];
			++k;++i;
		}
	}

	//For residual values
	if(i<n1){
		while(i<n1){
			C[k]=A[i];
			++k;++i;
		}
	}
	
	else if(j<n2){
		while(j<n2){
			C[k]=B[j];
			++k;++j;
		}
	}
}

void merge_sort(int *array, int start, int end){
	//Base case
	if(start==end)
		return;
	
	//Dividing the array in the middle
	int middle=(start+end)/2;

	//Recursive step
	merge_sort(array, start, middle);
	merge_sort(array, middle+1, end);

	//Meging the two sorted arrays
	int size=end-start+1;
	int *C=(int*)malloc(size*sizeof(int));
	merge((array+start), middle-start+1, (array+middle+1), end-middle, C);
	
	//Copying C into array
	int i;
	for(i=0; i<size;++i){
		*(array+start+i)=C[i];
	}
}
