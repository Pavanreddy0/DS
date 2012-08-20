
#include<stdio.h>
#include<time.h>


long long int fmodm_r(long long int n, long int m){
	//Base case
	if(n==1||n==2)
		return 1;

	//Using recursive relation	
	else
		return ((fmodm_r(n-1,m)%m)+(fmodm_r(n-2,m)%m))%m;
}

main(){
	clock_t start, end;
	double time;

	long long int i;
	for(i=1; i<=100; ++i){
		start=clock();
		fmodm_r(i,13);
		end=clock();
		time=(double)((end-start)/1000000.0);
		printf("\n%lld\t%lf", i, time);
	}
}
