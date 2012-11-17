#ifndef malloc
	#include<malloc.h>
#endif

//Function prototypes
int *left_shift(int *, int, int, int *);//Fucntion to shift the array. Parameters: array, size, m, final size of result
int *add(int *, int, int*, int, int *);//Adding two n bit numbers. Parameters: array1, size, array2, size, size of result	
int *ones_complement(int *, int , int *);//Computing ones compliment of the array. Parameters: array, size, final size of result
int *subtract(int *, int , int *, int , int *);//Subtract two n bit numbers. Parameters: array1, size, array2, size, size of result	

int *add(int *array1, int size1, int *array2, int size2, int *size){
	int i,j;//Loop vairable
	
	//Computing the size of the array and initializing it
	int *result;//temporary array to store the sum
	if(size1>=size2)
		*size=size1+1;
	else
		*size=size2+1;
	result=(int *)malloc(*size*sizeof(int));

	//Computing the result
	int carry=0;//To store carry
	int dg=0;//To store sum
	int k=*size-1;
	
	for(i=(size1-1),j=(size2-1);i>=0&&j>=0;--i,--j){
		dg=array1[i]+array2[j]+carry;
		result[k]=dg%2;
		carry=dg/2;
		--k;
	}

	//For residuals
	if(i>=0){
		while(i>=0){
			dg=array1[i]+carry;
			result[k]=dg%2;
			carry=dg/2;
			--i;
			--k;
		}
	}

	else{
		while(j>=0){
			dg=array2[j]+carry;
			result[k]=dg%2;
			carry=dg/2;
			--j;
			--k;
		}
	}

	//For the last digit left out
	if(carry>0)
		result[k]=carry;
	else
		result[0]=0;

	return result;
}

int *ones_complement(int *array1, int size1, int *size){
	//Declaring necessary variables
	int *array;
	array=(int *)malloc(*size*sizeof(int));
	
	int i,j;
	for(i=(size1-1), j=(*size-1);i>=0&&j>=0;--i,--j){
		array[j]=!array1[i];
	}
	
	//Adding the remaining zeroes
	while(j>=0){
		array[j]=1;
		--j;
	}

	//returning the array
	return array;
}

int *subtract(int *array1, int size1, int *array2, int size2, int *size){
	
	int *result;
	//Chopping off unnecessary zeroes in the beginning
	int s1, s2;

	s1=0;
	while(array1[s1]==0){
		s1=s1+1;
	}

	//Chopping off unnecessary zeroes in the beginning
	s2=0;
	while(array2[s2]==0){
		s2=s2+1;
	}

	int max;
	if((size1-s1)>=(size2-s2)){
		*size=(size1-s1)+1;
		max=*size;
	}
	else{
		*size=(size2-s2)+1;
		max=*size;
	}
	
	//Performing subtraction using one's complement
	result=ones_complement((array2+s2),(size2-s2), size);
	result=add(array1,size1,result,*size, size);
	
	//Chopping off unnecessary zeroes in the beginning in the result 
	int i=0;
	while(result[i]==0){
		result=result+1;
		*size=*size-1;
	}

	//Checking for overflow bit, in one's compliment
	if(*size>max){
		int *arr;
		arr=(int *)malloc(sizeof(int));
		arr[0]=1;
		*size=*size-1;
		result=(result+1);
		result=add(result,*size,arr,1,size);
		free(arr);//freeing the temporary array
	}

	//Returning the finla result
	return result;
}

int *left_shift(int *array, int size, int m, int *s){
	//Defining a temporary array
	int *res;
	res=(int *)malloc((m+size)*sizeof(int));

	//Copying the first size digits of the array
	int i;//Loop variable
	for(i=0;i<size;++i){
		res[i]=array[i];
	}

	//Intializing the digits after size as 0
	for(;i<(size+m);++i){
		res[i]=0;
	}

	//Returning the result
	*s=size+m;//Updating the size of the array
	return res;
}
