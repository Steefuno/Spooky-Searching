#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "multitest.h"

int length = 1; //temporary value, it'll be set in 
int* data = NULL;

/*
 * generates an array of ints from 0 to length-1
 * random order
 * Note: make sure to use malloc to store data on heap rather than stack
 */
int* initializeRandomList()
{
	data  = malloc(length *sizeof(int));
	int i = 0;
	while(i<length){
		data[i] = i;
		i++; 
	}
	
	i=0;
	while (i < length) {
		int pos0 = (rand() % length); //assumes length < MAX_RAND
		int pos1 = (rand() % length);
		int val0 = data[pos0];
		data[pos0] = data[pos1];
		data[pos1] = val0;
		i++;
	}

	return data;
}

/*
 * creates a new array of random data if no data
 * saved in variable: data
 * otherwise, scambles the random data
 */
int* getNewRandom(int newLength)
{
	//If no existing data, create new data
	if (data == NULL) {
		srand((unsigned int)time(NULL)); //initialize random
		return initializeRandomList();
	} else if (newLength != length) { //If an array of differerent length is wanted, create new data
		free(data);
		return initializeRandomList();
	}

	int i = 0;
	//for the length of data, swap 2 random values
	while (i < length) {
		int pos0 = (rand() % length); //assumes length < MAX_RAND
		int pos1 = (rand() % length);
		int val0 = data[pos0];
		data[pos0] = data[pos1];
		data[pos1] = val0;
		i++;
	}
	return data;
}

//Single process/thread search with 50 items
double test0()
{
	getNewRandom(50); //create array

	struct timeval start, end;
	gettimeofday(&start, 0);
	
	search(data,50,0,1); //search array
	
	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);

	return elapsed;
}

int main(int argc, char* argv)
{	
	int i = 0;
	double  min;
	double max;
	double stdev;
	while (i < argc) {
		printf("%s\n", argv[i++]);
	}

	double test0time = 0;
	i = 0;
	while (i < 100) {
		test0time += test0();
	}
	printf("Average time taken for test0: %f\n", test0time/100);
	printf("Min time taken for test0: %f\n", min);
	printf("Max time taken for test0: %f\n", max);
	printf("Standard deviation for test0: %f\n",stdev);
	return 1;
}
