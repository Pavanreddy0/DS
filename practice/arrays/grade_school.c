
/*********************************************************************************************************************
*                                     Authors: Srijan R Shetty, Shouvik Sachdeva                                     *
*			                                 Roll nos: 11727, 11693                  							     *			
*																				                                     *
* Program: For grade school multiplication of two numbers stored as arrays.											 *
*																													 *
**********************************************************************************************************************/

int *grade_school(int *, int *, int , int *);//Grade School multiplication. Parameters: array1, size1, array2, size2, size of result

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
