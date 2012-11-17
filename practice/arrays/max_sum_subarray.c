//Program to implement merge sort
#include<stdio.h>
#include<malloc.h>

//Function to compute maximum sum sub array
void max_sum_subarray(int *, int);//Parameters: array, size

main(){
	//Decalring the necessay variables
	int *array;
	int n,i;

	//ASking the user for the size of the array
	printf("\nEnter the size of the array: ");
	scanf("%d", &n);
	
	//Allocating memeory to the array
	array=(int*)malloc(n*sizeof(int));

	printf("\nEnter the elements of the array: ");
	for(i=0;i<n;++i){
		scanf("%d", &array[i]);
	}

	//Computing the maximum sum sub array
	max_sum_subarray(array,n);

	//Freeing the memory
	free(array);
}


void max_sum_subarray(int *array, int n){
	//Declaring required variables
	int i, sum, max, max_start, start, max_end, end;
	sum=array[0];
	max=array[0];
	max_start=0;
	max_end=0;
	start=0;
	end=0;

	for(i=1;i<n;++i){
		//Incrementing sum
		if(sum<=0){
			sum=array[i];
			start=i;
			end=i;
		}
		else{
			sum+=array[i];
			end++;
		}

		//Checking if it is the maximum sum
		if(sum>max){
			max=sum;
			max_start=start;
			max_end=end;
		}
	}

	//Printing the output
	printf("\nThe Maximum sum subarray is:");
	for(i=max_start; i<=max_end; ++i){
		printf(" %d", array[i]);
	}
	printf("\nWith a sum of: %d", max);
}

