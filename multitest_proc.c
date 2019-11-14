#include <pthread.h>
#include <stdio.h>

int search(int* data, int value, int numProcesses)
{

	//find size of the array
	//This probably doesnt work, since its the pointer: pass in sizeof array instead? 
	int size = sizeof(data)/sizeof(data[0]);		

	int i =0;
	int value;
	int start;
	int end; 
	
	int sizeEachArr = size/numProccesses;	

	//fork all the processes
	while (i< numProccesses){
		i++; 
		fork();
	
		//use pid
		//figure out start and ending indices using the value of i and search
		
		if(size % numProccesses!=0 && i==numProccesses){
			//array cannot be divided evenly 		
			//split up the last portion of the array here
			
			start = i*sizeEachArr+1; 
			end = start + sizeEachArr + (size - (start+sizeEachArr));
	
			value = search(data,start,end);
			}
		else{
			if (i==1){
				start =0;
				end = start + sizeEachArr; 
				value = search(data,start,end);
			}
			
			else{
				start = i*sizeEachArr + 1;
				end = start+sizeEachArr;
				value = search(data,start,end);

				}

			

					} 
		
	
	
		//use system macros of wait()
		//extract lower 8 bits... to see if child found the value
	
	}
	return 0;

} 

//iterative search function
int searchArray(int* data, int start, int end){

} 
