#include <pthread.h>
#include <stdio.h>

int* searchData = NULL;

void* scanAt(void* args)
{
	pthread_exit(15);
}

int search(int* data, int value, int numThreads)
{
	searchData = data;

	pthread_t threads[] = (pthread_t*)malloc(sizeof(pthread_t)*numThreads);
	int output = -1;
	int* status = NULL;

	int threadNum = 0;
	while (threadNum < numThreads) {
		pthread_create(threads+threadNum, NULL, scanAt, );
		++threadNum;
	}

	return 0;
} 
