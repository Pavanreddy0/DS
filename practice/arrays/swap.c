//Function to swap elements

//Function prototype
void swap(int *, int, int);//Function to swap elements in a string. Parameters: string, src, destination

void swap(int *string, int i, int j){
	int temp=string[i];
	string[i]=string[j];
	string[j]=temp;
}
