#include<stdio.h>
#include<time.h>

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

main(){
	clock_t start, end;
	double time;

	long long int i;
	for(i=21801609; i<=21900000; ++i){
		start=clock();
		fmodm_i(i,12345);
		end=clock();
		time=(double)((end-start)/1000000.0);
		printf("\n%lld\t%lf", i, time);
	}
}
