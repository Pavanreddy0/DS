/**********************************************************************************
*                Authors: Srijan R Shetty, Shouvik Sachdeva                       *
*				 Roll nos: 11727, 11693											  *			
*																				  *
* Program for: Computing the factorial of larger numbers (thousands)              *
* 																				  *
* Important points: Shows the use of data structure in solving difficult problems *
*                   Here arrays are used to solve the problem of small size of    *
*					long long int which prooves inefficient in computing the      *
*					factorial of even 20!										  *
**********************************************************************************/

//Including necessary header files
#include<stdio.h>
#include<malloc.h>
#include<time.h>

//Program to compute factorial
long long int *factorial(long long int );

main(){
	//Declaring the necessary varaibles
	long long int* fact;									//To store factorial
	clock_t start, end;										//To store starting and ending times

	//Dynamically allocating array
	fact=(long long int*)malloc(20000*sizeof(long long int ));

	//A loop running through all the numbers to check the time	
	long long int i;
	for(i=20000; i<100000; ++i){
		//Checking time taken
		start=clock();
		factorial(i);
		end=clock();

		//Computing the time taken
		double time=(double)((end-start)/1000000.0);
		printf("\n%lld \t%lf", i, time);		
		if(time>1.0){
			printf("\n%lld", i);
			break;
		}
	}
}

long long int *factorial(long long int n){
	//Delcaring and allocating an array to store the factorial
	long long int* fact;
	fact=(long long int *)malloc(200000*sizeof(long long int ));
	fact[0]=1;

	//Start of computation
	long long int i,j;										//Loop control
	long long int carry=0;									//For carry over
	long long int num;										//To store the number
	long long int temp;										//Temporary variable
	long long int size=1;									//To store the size of the array
	
	for(i=2; i<=n; ++i){
		for(j=0;j<size;++j){
			//Getting the digits from the array and then using simple multiplication
			num=fact[j];
			temp=num*i+carry;	
			num=temp%100000000000000;
			carry=temp/100000000000000;

			//Storing the number back in the array
			fact[j]=num;
		}
			
		//Special case, when we reach the end of the array and have carry!=0. We have to manually add the carry into the array so that
		//No garbage values turn in
		if(carry!=0){
			//Using a loop to push the carry into the array
			while(carry>0){
				temp=carry%100000000000000;
				fact[j]=temp;
				carry=carry/100000000000000;
				++j;
				++size;
			}
		}
	}

	//Returning the array
	return fact;
}

