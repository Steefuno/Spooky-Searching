#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int* searchData = NULL;
int result = -1;
int target = -1;

void* scanAt(void* args)
{
	int i = *(int*)(args);
	int end = *(int*)(args+sizeof(int));
	while (i < end) {
		if (searchData[i] == target) {
			result = i;
			break;
		}
		++i;
	}
	pthread_exit(NULL);
}

int search(int* data, int size, int value, int numThreads)
{
	printf("Searching with threads");
	searchData = data;
	target = value;

	pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t)*numThreads);
	int output = -1;
	int* status = NULL;

	int threadNum = 0;
	while (threadNum < numThreads) {
		void* args = malloc(sizeof(int)*2);
		*(int*)(args) = threadNum*(size/numThreads);
		*(int*)(args+sizeof(int)) = (threadNum+1)*(size/numThreads);
		pthread_create(threads+threadNum, NULL, scanAt, args);
		++threadNum;
	}

	threadNum = 0;
	pthread_yield();
	while (threadNum < numThreads) {
		pthread_join(threads[threadNum], NULL);
		++threadNum;
	}

	//printf("Found %d at %d\n", target, result);

	return 0;
}
