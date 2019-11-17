#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int search(int* data, int size, int value, int numProcesses){

	
	int start=0;
	int end;
	int i;
	int pid;
	int value2;

	int sizeEachArr = size/numProcesses;	

	for (i = 0; i<numProcesses; i++){
		pid = fork();
		
		if (pid<0){
			printf("Fork Error");
			exit(1);
			}
			
		//else if it is a child	 
		else if (pid == 0){
	
				start = i*sizeEachArr;
				end =start + sizeEachArr-1;
				//printf("The value of i is: %d, Start is: %d, End is: %d\n",i,start, end);
				value2 = searchArray(data, start,end, value); 
				printf("The possible index is: %d\n", value2);
				exit(0);
			
			}
		}	
		
	int x; 	
	for (x =0; x<numProcesses; x++){
		
		wait(NULL);
		}
	return 0;

} 

//iterative search function
int searchArray(int* data, int start, int end, int value){
	int i;
	for (i = start; i <= end; i++){
		if (data[i] == value)
			return i;
		}
	return -1;
		

}

//main function just for testing
int main (){
	
	int array[6] = {1,2,3,4,5,6};
	
	search(array, 6,3, 2); 

	//int variable = searchArray(array,0,2,3);
	//printf("%d", variable);	

	return 0; 
}


 
