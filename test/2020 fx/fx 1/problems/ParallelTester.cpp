#include "ParallelTester.h"


void * wrapper(void * data) { 
	threadDataT * info = (threadDataT *)data;
	bool passed = info->foo(info->testNum);
	if (passed) {
		sem_wait(info->lock);
		(*(info->passedCounter))++;
		sem_post(info->lock);
	}
	sem_post(info->wait);
	return NULL;
}

void runAllTestsInThreads(Map<string, problemDataT> problemsData) {
	string testFile = string(TEST_RESULTS_FOLDER_PATH) + "test.txt";
	ifstream inp(testFile.c_str());
	string problemName;
	inp >> problemName;

	string outputFile = string(TEST_RESULTS_FOLDER_PATH) + "result.txt";
	string outputFileFinal = string(TEST_RESULTS_FOLDER_PATH) + "result_final.txt";

	problemDataT problemData = problemsData[problemName];
	int totalTestNum = problemData.totalTestNum;
	bool (*foo)(int) = problemData.foo;

	pthread_t * threads = new pthread_t[totalTestNum];
	sem_t * lock = new sem_t;
	sem_t * wait = new sem_t;
	sem_init(lock, 0, 1);
	sem_init(wait, 0, 0);
	int * passedCounter = new int;
	*passedCounter = 0;
	for (int i=0; i<totalTestNum; i++) {
		threadDataT * data = new threadDataT;
		data->passedCounter = passedCounter;
		data->testNum = i;
		data->foo = foo;
		data->lock = lock;
		data->wait = wait;
		pthread_create(&threads[i], NULL, wrapper, data);
	}

	for (int i=0; i<totalTestNum; i++) {
		sem_wait(wait);
		ofstream out(outputFile.c_str());
		out << *passedCounter;
		out.close();
	}

	ofstream outFinal(outputFileFinal.c_str());
	outFinal << *passedCounter;
	outFinal.close();
}
