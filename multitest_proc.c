#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char* multimode = "process";

int search(int* data, int size, int value, int numProcesses){
	printf("Search using processes\n");
	int start=0;
	int end;
	int i;
	int pid;
	int value2;
	pid_t rc_pid[numProcesses];

	int sizeEachArr = size/numProcesses;	

	if(sizeEachArr > 250){
		printf("Error: array partitions too large. Increase process count. ");
		return; 
	}
	
	for (i = 0; i<numProcesses; i++){
		pid = fork();
		rc_pid[i] = (pid_t)pid;
			
		if (pid<0){
			printf("Fork Error");
			exit(1);
			}
			
		//else if it is a child	 
		else if (pid == 0){	
					printf("searching iteration:%d\n", i); 
					start = i*sizeEachArr;	
					end =(i + 1) *sizeEachArr;
					//printf("The value of i is: %d, Start is: %d, End is: %d\n",i,start, end);
					value2 = searchArray(data, start,end, value); 
					//if (value2>-1){printf("Value found at index: %d\n", value2); }
					exit(value2);
			}
		}
	if(pid>0){	
		
		int x; 	
		int status;
		for (x =0; x<numProcesses; x++){
			waitpid(rc_pid[x],&status,0);
		}
		
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
 
