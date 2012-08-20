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
#include<string.h>
#include<malloc.h>

main(){
	//Declaring the necessary varaibles
	char *fact;									//To store factorial
	int n;										//To store the users input
	
	//Dynamically allocating array
	fact=(char*)malloc(200000*sizeof(char));
	fact[0]='1';								//Factorial of 1 is 1

	//Asking the user for the number
	printf("\nEnter number: ");
	scanf("%d", &n);

	//Start of computation
	int i,j;									//Loop control
	int carry=0;									//For carry over
	int num;									//To store the number
	int temp;									//Temporary variable
	for(i=2; i<=n; ++i){
		for(j=0;j<strlen(fact);++j){
			//Getting the digits from the array and then using simple multiplication
			num=(int)(fact[j]-'0');
			temp=num*i+carry;	
			num=temp%10;
			carry=temp/10;

			//Storing the number back in the array
			fact[j]=(char)('0'+num);
		}
			
		//Special case, when we reach the end of the array and have carry!=0. We have to manually add the carry into the array so that
		//No garbage values turn in
		if(j==strlen(fact)&&carry!=0){
			//Using a loop to push the carry into the array
			while(carry>0){
				temp=carry%10;
				fact[j]=(char)('0'+temp);
				carry=carry/10;
				++j;
			}
		}
	}

	//As the array was kept in reverse order for simplicity, here we are printing the reverse of the array
	printf("\nThe factorial of %d is: ", n);
	for(j=(strlen(fact)-1);j>=0; --j){
		printf("%c", fact[j]);
	}
	printf("\n");

	//Deallocating array
	free(fact);
}

