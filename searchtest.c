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
double test(int size, int numThreads)
{
	getNewRandom(size); //create array

	struct timeval start, end;
	gettimeofday(&start, 0);
	
	search(data,size,0,numThreads); //search array
	
	gettimeofday(&end, 0);
	double elapsed = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);

	return elapsed;
}

void outputResults(double* total0, double* total1, int numTests, double* max, double* min)
{
	double average = *total0/numTests;
	double std = sqrt(*total1/numTests);
	
	printf("\tAverage time is %f\n", average);
	printf("\tStandard deviation is %f\n", std);
	printf("\tMax time is %f\n\tMin time is %f\n", *max, *min);

	*total0 = 0;
	*total1 = 0;
	*max = 0;
	*min = -1;
	return;
}

int main(int argc, char* argv)
{	
	int numTests = 100;

	int i = 0;
	double min = -1;
	double max = 0;
	double total0 = 0;
	double total1 = 0;
	double t;

	printf("\naSize 50, Procs 1\n"); //for 100 times, get time of size 50 array with 1 proc
	while (i < numTests) {
		t = test(50, 1);

		total0 += t;
		total1 += t*t;
		if (t < min || min == -1) min = t;
		if (t > max) max = t;

		++i;
	}
	outputResults(&total0, &total1, numTests, &max, &min);

	i = 0;
	printf("\naSize 2, Procs 2\n"); //for 100 times , get time of size 2 array with 2 procs
	while (i < numTests) {
		t = test(2, 2);

		total0 += t;
		total1 += t*t;
		if (t < min || min == -1) min = t;
		if (t > max) max = t;
		++i;
	}
	outputResults(&total0, &total1, numTests, &max, &min);

	int n = 2;
	int size;
	int m;
	int procs;
	while (n < 13) {
		size = pow(2, n); //Size of array is 2^n
		m = 2;
		while (m < 14) {
			i = 0;
			procs = m*m; //# of procs is m^2
			if (procs > size) break;

			//for 100 times, get time of size "size" array with "procs" procs
			printf("\naSize %d, Procs %d\n", size, procs);
			while (i < numTests) {
				t = test(size, procs);

				total0 += t;
				total1 += t*t;
				if (t < min || min == -1) min = t;
				if (t > max) max = t;
				++i;
			}
			outputResults(&total0, &total1, numTests, &max, &min);

			++m;
		}

		++n;
	}

	return 1;
}
