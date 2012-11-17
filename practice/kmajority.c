//Program to find k majority element in an array
#include<stdio.h>
#include<malloc.h>

void kmajority(int *, int, int);//Function to determine kmajority. Parameters: array, size

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

	int k;
	printf("\nEnter k:");
	scanf("%d", &k);
	
	//Computing the k majority element
	kmajority(array,n,k);

	//Freeing the memory
	free(array);
}


void kmajority(int *array, int n, int k){
	//Declaring required variables
	int *temp, *count;
	temp=(int *)malloc(k*sizeof(int));
	count=(int *)malloc(k*sizeof(int));
	
	//Initializing the temp array to be zero
	int j;
	for(j=0;j<k;++j){
		temp[k]=0;
		count[k]=0;
	}

	//Trivially assigning the first element of temp
	temp[0]=array[0];
	count[0]=1;

	//Looping through all the elements of the array
	int i,flag;//Loop variable
	for(i=1;i<n;++i){
		flag=-1;
		for(j=0;j<k;++j){
			if(temp[j]==0){
				temp[j]=array[i];
				count[j]=1;
				flag=j;
			}
			else if(array[i]==temp[j]){
				count[j]++;
				if(flag!=-1){
					count[flag]==0;
					temp[j]=0;
				}
				break;
			}
		}
	}

	//Checking if any element of temp is k majority
	int c=0;
	for(j=0;j<k;++j){
		c=0;
		for(i=0;i<n;++i){
			if(temp[j]==0)
				break;
			if(temp[j]==array[i]){
				c++;
			}
		}
		if(c>(n/k)){
			printf("%d is a kmajority element.", temp[k]);
		}
	}

	//Freeing space
	free(temp);
	free(count);
}
