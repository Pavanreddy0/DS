/*********************************************************************************************************************
*                                     Authors: Srijan R Shetty, Shouvik Sachdeva                                     *
*			                                 Roll nos: 11727, 11693                  							     *			
*																				                                     *
* Program: For analysis of merge sort and quick sort.           													 *
*                                                                                                                    *
**********************************************************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<time.h>

//Function to generate an arbitary array
void generate(int *, int);//Parameters: array, size
//Functions pertaining to merge sort
void merge(int*, int, int*, int, int *);//Function to merge two arrays. Parameters: source, source, destination
void merge_sort(int *, int, int);//Merge Sort function. Parameters: Array, start, end 
void time_merge_sort(int *, int, int);//To time mergesort.Parameters: array, start ,end

//Functions pertaining to quick sort
void quick_sort(int *a, int p, int r);//Function for sorting recursively(Conquer)
int partition(int *a, int p,int r);//Function for partitioning(Divide)
int choose_pivot(int *a,int p,int r);//Function for choosing pivot
void time_quick_sort(int *, int, int);//To time quick sort.Parameters: array, start, end

main(){
	//Declaring the required variables
	int n;//size of the array
	int ch;//Choice

	printf("\nEnter size of the array:");
	scanf("%d", &n);
	printf("\nEnter choice:");
	printf("\n\n1. Input and output of the algorithms.");
	printf("\n2. Time taken.\n");
	scanf("%d",&ch);

	int i;
	//Geerating a random array
	int *array;
	array=(int*)malloc(n*sizeof(int));
	generate(array,n);
	
	//Copying the above array into another array
	int *array1;
	array1=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;++i){
		array1[i]=array[i];
	}

	switch(ch){//to handle choices
		case 1:
			   printf("\nThe input array is:\n");
			   for(i=0;i<n;++i){
			   	printf("%d ",array[i]);
			   }

			   //Sorting the array using merge sort
			   merge_sort(array,0,(n-1));
			   printf("\nThe output of merge sort is:");
			   for(i=0;i<n;++i){
			   		printf("%d ",array[i]);
			   }

			   //Sorting the array using quick sort
			   quick_sort(array1,0,(n-1));
			   printf("\nThe output of quick sort is:");
			   for(i=0;i<n;++i){
			   		printf("%d ",array1[i]);
			   }
			   printf("\n");
			   break;
		
		case 2:time_merge_sort(array,0,n-1);
			   time_quick_sort(array1,0,n-1);
			   break;
		
		default: printf("\nWrong Input");
	}
}

//Function definations
void generate(int *array, int n){
	srand(time(NULL));
	int i;//Loop variable
	for(i=0;i<n;++i){
		array[i]=rand()%n+1;//Divding by n so that the number remains in the range 1 to n
	}
}

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

void time_merge_sort(int *array, int start, int end){
	clock_t startt,endt;
	
	//Clocking the time
	startt=clock();
	merge_sort(array, start, end);
	endt=clock();
	
	double time=((endt-startt)/1000000.0);
	printf("\nThe time taken by Merge Sort is: %lf", time);
}

int partition(int *a,int p,int r)
{
        int i,j,x,temp,piv;                             //Declaring variables
        piv=choose_pivot(a,p,r);                //Choosing pivot
        //Arranging pivot as first element
        temp=a[p];
        a[p]=a[piv];
        a[piv]=temp;
        i=p+1;                                          
        j=r;
        x=a[p];                                         
        while(i<=j)                                     //For i>j, Array is now partitioned
        {
        
                while((j>=p)&&(a[j]>x)) //Finding smaller element to the right of pivot
                {
                        j--;
                }
                while((i<=r)&&(a[i]<=x)) //Finding larger element to the left of pivot
                {
                        i++;
                }
                if(i<j)                                 //Swapping position of wrongly placed elements
                {
                        temp=a[j];
                        a[j]=a[i];
                        a[i]=temp;
                }
        }
        //Positioning the pivot correctly
        temp=a[p];
        a[p]=a[j];
        a[j]=temp;
        return j;                                       //Returning the index of the pivot
}

int choose_pivot(int *a, int p, int r)
{
        int pivot;
        //Choosing pivot as the median of first last and middle element of the array
        if(a[p]>=a[r]&&a[p]<=a[(p+r)/2]) pivot=p;
        else if(a[p]<=a[r]&&a[p]>=a[(p+r)/2]) pivot=p;
        else if(a[r]>=a[p]&&a[p]<=a[(p+r)/2]) pivot=r;
        else if(a[r]<=a[p]&&a[p]>=a[(p+r)/2]) pivot=r;
        else pivot=(p+r)/2;
        return pivot;
}

void quick_sort(int *a,int p,int r)
{
        int q;                                          //Declaring new variable to store index which partitions the array
        if(p<r)                                         //Else it is already sorted
        {
                q = partition(a,p,r);   //Partitioning the array s.t. the left of the pivot has smaller values and the right of the pivot has larger values
                quick_sort(a,p,q-1);    //Sorting the array to the left of the pivot recursively
                quick_sort(a,q+1,r);    //Sorting the array to the right of pivot recursively
        }
        return;
}

void time_quick_sort(int *array, int start, int end){
	clock_t startt,endt;
	
	//Clocking the time
	startt=clock();
	quick_sort(array, start, end);
	endt=clock();
	
	double time=((endt-startt)/1000000.0);
	printf("\nThe time taken by Quick Sort is: %lf\n", time);
}
