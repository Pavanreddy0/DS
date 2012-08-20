/**********************************************************************************
*                Authors: Srijan R Shetty, Shouvik Sachdeva                       *
*				 Roll nos: 11727, 11693											  *			
*																				  *
* Program for: Computing fibonacci numbers using recursion, iteration and matrices*
* 																				  *
* Important points: Comparing the efficiency of the three methods of computing    *
*                   the nth fibonacci number and then computing the mod of the    *
*					nth fibonacci number n. This also showcases the space         *
*					complexity of the various algorithms.                         *
**********************************************************************************/

//Including standard header files
#include<stdio.h>
#include<malloc.h>

//Function to compute fmondn iteratively	
long long int fmodm_i(long long int n, long int m);													//n,m

//Function to compute fmodn recursively
long long int fmodm_r(long long int n, long int m);													//n,m

//Function to allocate memory
long long int** allocate(long long int n);															//size of matrix

//Function for multiplying two square matrices of same order
long long int **mat_mul(long long int **a, long long int **b, long int m);							//array1, array2
	
//Evaluating M^n for a square matrix
long long int **mat_n(long long int **a, long long int n, long int m);								//array, power

//Function to compute fmodm via matrix multiplication
long long int fmodm_m(long long int n, long int m);

//main function
main(){
	//Declaring the necessary variables
	long int m;																						//To store m
	long long int n;																				//To store number of fibonacci
	int ch;																							//Users choice

	//Asking user for inputs
	printf("\nEnter the desired method for computing f(n)mod(m):\n");
	printf("\n1.Recursive");
	printf("\n2.Iterative");
	printf("\n3.Matrix\n:");
	scanf("%d", &ch);
	printf("\nEnter n:");
	scanf("%lld", &n);
	printf("Enter m:");
	scanf("%ld", &m);

	//Checking users choice
	switch(ch){
		case 1: printf("\nThe value of f(n)mod(m), computed recursively is: %lld\n", fmodm_r(n,m));
			break;
		case 2: printf("\nThe value of f(n)mod(m), computed iteratively is: %lld\n", fmodm_i(n,m));
			break;
		case 3: printf("\nThe value of f(n)mod(m), computed via matrix method is: %lld\n", fmodm_m(n,m));
			break;
		default: printf("\nWrong input");
			break;
	}
}

//Function definations

long long int fmodm_i(long long int n, long int m){
	//Declaring the necessary variables
	long long int i;																			//Loop control variable
	long long int a,b,res;																		//To compute res

	//Computing the result
	if(n==1||n==0)
		return 1;
	a=1;																						//First number
	b=1;																						//Second number
	for(i=3;i<=n;++i){
		res=(a+b)%m;
		a=b;
		b=res;
	}
	return res;
}

long long int fmodm_r(long long int n, long int m){
	//Base case
	if(n==1||n==2)
		return 1;

	//Using recursive relation	
	else
		return ((fmodm_r(n-1,m)%m)+(fmodm_r(n-2,m)%m))%m;
}

long long int** allocate(long long int n){
	//Creating a new array
	long long int **a;

	//Allocating space to the pointer of pointers
	a=(long long int**)malloc(n*sizeof(long long int*));

	//Allocating space to each pointer in the array
	long long int i;																				//Loop variable
	for(i=0; i<n; ++i){
		a[i]=(long long int*)malloc(n*sizeof(long long int));
	}
	return a;											
}	

long long int **mat_mul(long long int **a, long long int **b, long int m){
	//Delcaring the necessasry variables
	long long int i,j,k;					 														//Loop variable
	
	//allocating the result matrix
	long long int **c;																				//Result array
	c=allocate(2);
	
	//Computing the product
	for(i=0; i<2; ++i){
		for(j=0; j<2; ++j){
			c[i][j]=0;
			for(k=0; k<2; ++k){
				c[i][j]=c[i][j]+a[i][k]*b[k][j];
			}
			c[i][j]%=m;																				//Taking mod at each multiplication
		}
	}
	return c;	
}

long long int **mat_n(long long int **a, long long int n, long int m){
	//Temporary variable to store the final answer
	long long int** temp;
	temp=allocate(2);

	//Computation
	if(n==1)
		temp=a;
	else if(n==2)
		temp=mat_mul(a,a,m);
	
	//For even case we compute M^n/2 and mul it with itself
	else if(n%2==0){
		temp=mat_n(a, n/2,m);
		return mat_mul(temp,temp,m);
	}

	//For odd cases we compute M^(n-1)/2 and mul it with itself followed by multiplication by M
	else{
		temp=mat_n(a, (n-1)/2,m);
		temp=mat_mul(temp,temp,m);
		temp=mat_mul(temp,a,m);
	}

	//Returning final answer
	return temp;
}
	
long long int fmodm_m(long long int n, long int m){
	//Declaring necessary varaibles
	long long int **a;																				//Matrix
	a=allocate(2);
	*(*(a+0)+0)=1;
	*(*(a+0)+1)=1;
	*(*(a+1)+0)=1;
	*(*(a+1)+1)=0;

	//Computing result matrix
	a=mat_n(a, n-1,m);
	//Here the first element of a is the fibonacci number
	return 	(*(*(a+0)+0))%m;
}
