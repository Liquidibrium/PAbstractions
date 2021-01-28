#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <map.h>

#define TEST_RESULTS_FOLDER_PATH "D:\\freeuni\\courses\\cs106b\\exams repo\\cs106b\\testing\\"
#define PROJECT_ROOT_FOLDER "D:\\freeuni\\courses\\cs106b\\exams repo\\cs106b\\2020\\final\\testing\\final 1\\project\\Blank Project\\"


struct threadDataT {
	int testNum;
	int *passedCounter;
	bool (*foo)(int);
	sem_t * lock;
	sem_t * wait;
};

struct problemDataT {
	string problemName;
	int totalTestNum;
	bool (*foo)(int);
};



void * wrapper(void * data);

void runAllTestsInThreads(Map<string, problemDataT> problemFunctions);