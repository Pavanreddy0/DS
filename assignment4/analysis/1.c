/*********************************************************************************************************************
*                                     Authors: Srijan R Shetty, Shouvik Sachdeva                                     *
*			                                 Roll nos: 11727, 11693                  							     *			
*																				                                     *
* Program: For implementation of karatsuba's fast multiplication algorithm.											 *
*																													 *
* Important points: As, we am using malloc over here, the code stops after a particular threshold because the memory *
*                   of the computer gets exhausted.                                                                  *
**********************************************************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<time.h>

//Function to generate an arbitary array
void generate(int *, int, int);//Parameters: array, size, parameter

//Function to related to fast multiply using karatsuba's algorithm
int *shift(int *, int, int, int *);//Fucntion to shift the array. Parameters: array, size, m, final size of result
int *add(int *, int, int*, int, int *);//Adding two n bit numbers. Parameters: array1, size, array2, size, size of result	
int *ones_complement(int *, int , int *);//Computing ones compliment of the array. Parameters: array, size, final size of result
int *subtract(int *, int , int *, int , int *);//Subtract two n bit numbers. Parameters: array1, size, array2, size, size of result	
int *grade_school(int *, int *, int , int *);//Normal multipliaction by grade school method. Parameters: array1, size1, arry2, size2, result
int *karatsuba(int *, int *, int , int *);//Karatsuba multiplication. Parameters: array1, size1, array2, size2, size of result
void time_karatsuba(int *, int *, int , int *);//timing karatsuba by clock_t
void time_grade_school(int *, int *, int , int *);//timing grade school by clock_t
		
main(){
	//Generating two random arrays
	int *array1;
	int *array2;
	int i,j, temp,s;

	scanf("%d %d", &i, &j);

	for(temp=i*10000;temp<=j*10000;temp=temp+10000){
		array1=(int*)malloc(temp*sizeof(int));
		generate(array1,temp,0);

		array2=(int*)malloc(temp*sizeof(int));
		generate(array2,temp,1);

		time_grade_school(array1,array2,temp,&s);
		
		free(array1);
		free(array2);
	}
}

//Function definations
void generate(int *array, int n, int p){
	//we needed two different arrays, p takes care of just that
	if(p==0)
		srand(time(NULL));
	else
		srand(time(NULL)*time(NULL));

	int i;//Loop variable
	for(i=0;i<n;++i){
		array[i]=rand()%2;//Divding by n so that the number remains in the range 1 to n
	}
}

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

int *shift(int *array, int size, int m, int *s){
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

int *grade_school(int *a, int *b, int size, int *s) {
	int i,j;//loop variable
	
	//Declaring the necessary variables
	int *ret,*carry,*result;
	ret=(int *)(malloc(2*size*(sizeof(int))));
	result=(int *)(malloc(2*size*(sizeof(int))));
	carry=(int *)(malloc(2*size*(sizeof(int))));
	
	for(i=0;i<2*size;i++) {
		carry[i]=0;
		ret[i]=0;
	}
	
	for(i=size-1;i>=0;i--){
		for(j=size-1;j>=0;j--) {
			ret[2*(size-1)-(i+j)]+=a[i]*b[j];
		}
	}
	
	for(i=0;i<2*size-1;i++){
		carry[i+1]=(ret[i]+carry[i])/2;
		ret[i]=(ret[i]+carry[i])%2;
	}
	
	if(carry[2*size-1]>0) 
		ret[2*size-1]=(ret[2*size-1]+carry[2*size-1])%2;
	else 
		ret[2*size-1]=-1;
	
	i=2*size-1;j=0;
	while(ret[i]!=1){
		i--;
    }

    for(;i>=0;i--,j++){
		result[j]=ret[i];
    }

	//Freeing space
	free(carry);
	free(ret);

	*s=j;//Updating the size of array
 	return result;
}

int *karatsuba(int *array1, int *array2, int size, int *s){
	int *result;
	*s=2*size;
	result=(int*)malloc(*s*sizeof(int));
	
	//Base case, this ensures a fast code other wise time taken by karatsuba increases
	if(size<=100){
		result=grade_school(array1,array2,size,s);
		return result;
	}
	
	else{
		int mid=size/2;
		mid=size-mid;
			
		int *o1, *o2, *o3, *o4, *o5;//Temporary variables
		
		//variables to store size
		int s1, s2, s3, s4, s5;
		o1=karatsuba(array1, array2, mid, &s1);//ac
		o2=karatsuba((array1+mid), (array2+mid), (size-mid), &s2);//bd
		o4=add(array1, mid, (array1+mid), (size-mid), &s4);//(a+b)
		o5=add(array2, mid, (array2+mid), (size-mid), &s5);//(c+d)
		o3=karatsuba(o4,o5,s4, &s3);//(a+b)(c+d)
		o4=add(o1,s1, o2, s2, &s4);//ac+bd
		o5=subtract(o3, s3, o4, s4, &s5);//(a+b)(c+d)-ac-bd
		o1=shift(o1, s1, 2*(size-mid), &s1);//ac*2^2m
		o2=add(o1, s1, o2, s2, &s2);//ac*2^2m+bd
		o5=shift(o5, s5, (size-mid), &s5);//(ad+bc)*2^m
		
		result=add(o5, s5, o2, s2, s);//ac*2^2m+(ad+bc)*2^m+bd	
		
		free(o1);
		free(o2);
		free(o3);
		free(o4);
		free(o5);
		return result; 
	
	}
}

void time_karatsuba(int *array1, int *array2, int size, int *s){
	clock_t start,end;
	double time;
	int i;	
	int *result;
		
	//Clocking the time
	start=clock();
	result=karatsuba(array1, array2, size, s);
	end=clock();

	time=((end-start)/1000000.0);

	printf("\n%d %lf", size, time);
	free(result);//Freeing space
}

void time_grade_school(int *array1, int *array2, int size, int *s){
	clock_t start,end;
	double time;
	int i;	
	int *result;	
	
	//Clocking the time
	start=clock();
	result=grade_school(array1, array2, size, s);
	end=clock();

	time=((end-start)/1000000.0);

	FILE *fout;
	fout=fopen("g.txt", "a");
	fprintf(fout, "\n%d %lf\n", size, time);
	free(result);//Freeing space
	fclose(fout);
}

