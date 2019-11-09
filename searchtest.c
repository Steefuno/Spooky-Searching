#include <stdio.h>
#include <stdlib.h>

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

	return NULL;
}

/*
 * creates a new array of random data if no data
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
	}
	return data;
}
