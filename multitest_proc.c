#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int search(int* data, int size, int value, int numProcesses){

	
	//have to make sure the array is only split up into sizes of no more than 250 elements

	int i =0;
	int valueResult;
	int start;
	int end;
	int rc; 	
			
	//int sizeEachArr = size/numProcesses;	
	int sizeEachArr = 2;
	//fork all the processes
	while (i< numProcesses){
		i++; 
//		if (fork()==0){
		
		//use pid
		//figure out start and ending indices using the value of i and search
		
		if(size % numProcesses!=0 && i==numProcesses){
			//array cannot be divided evenly 		
			//split up the last portion of the array here
			
			start = i*sizeEachArr+1; 
			end = start + sizeEachArr + (size - (start+sizeEachArr));	
		
			valueResult = search(data,start,end, value);
				printf("%d\n", valueResult);	
			//	exit(0);	
		}
		else{
			if (i==1){
				start =0;
				end = start + sizeEachArr; 
				valueResult = search(data,start,end, value);
			
				printf("%d\n", valueResult);
			//	exit(0);

				}
			
			else{
				start = i*sizeEachArr + 1;
				end = start+sizeEachArr;
			
		
				valueResult = search(data,start,end, value);
					printf("%d\n", valueResult);
			//		exit(0);
				}
			}
		
		
//		 }
	} 
			//	if (rc>0){
/*			while(i>0){
				int status;
				wait(&status);
					
				i--;
			}
	
*/	
	
		//use system macros of wait()
		//extract lower 8 bits... to see if child found the value
	
	return 0;

} 

//iterative search function
int searchArray(int* data, int start, int end, int value){
	while(start<end){
		if(data[start] == value){
			return start;	
			}
			
		start++;
		}		
	
	if (start == end){
		return -1; 
		}

}

int main (){
	
	int array[6] = {1,2,3,4,5,6};
	
	search(array, 6, 3, 3); 
	
	

return 0; 
}


 
