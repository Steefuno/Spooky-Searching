#include <pthread.h>
#include <stdio.h>

int search(int* data, int value, int numProcesses)
{

	//find size of the array
	//This probably doesnt work, since its the pointer: pass in sizeof array instead? 
	int size = sizeof(data)/sizeof(data[0]);		

	int i =0;
	int value;
	//fork all the processes
	while (i< numProccesses){
		i++; 
		fork();
	
		//use pid
		//figure out start and ending indices using the value of i and search
		//also need a way to figure out indices for variable sized arrays '%' if they cannot be evenly divided
		value = search(data, ,);
	
		//use system macros of wait()
		//extract lower 8 bits... to see if child found the value
	
	}
	return 0;

} 

//iterative search function
int searchArray(int* data, int start, int end){

} 
