//Function to generate an arbitary array
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
