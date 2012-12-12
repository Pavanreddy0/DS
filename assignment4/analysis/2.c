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
//Functions pertaining to quick sort
void quick_sort(int *a, int p, int r);//Function for sorting recursively(Conquer)
int partition(int *a, int p,int r);//Function for partitioning(Divide)
int choose_pivot(int *a,int p,int r);//Function for choosing pivot
void time_quick_sort(int *, int, int);//To time quick sort.Parameters: array, start, end

main(){
	int i,j;
	int n1, n2;
	scanf("%d %d", &n1, &n2);
	
	int *array;
	
	for(i=n1*100000; i<=n2*100000; i+=500000){
			//Geerating a random array
			array=(int*)malloc(i*sizeof(int));
			generate(array,i);
			
			time_quick_sort(array,0,i-1);
			free(array);
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
	int i;
	double time;

	//Clocking the time
	startt=clock();
	quick_sort(array, start, end);
	endt=clock();
	time=((endt-startt)/1000000.0);
	

	FILE *fout;
	fout=fopen("q4.txt", "a");
	fprintf(fout,"\n%d %lf", (end+1), time);
	fclose(fout);
}
