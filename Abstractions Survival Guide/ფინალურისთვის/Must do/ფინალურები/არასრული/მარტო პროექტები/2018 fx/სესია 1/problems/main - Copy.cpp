#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "random.h"
#include "console.h"
#include "vector.h"
#include <time.h>
#include <sys/timeb.h>
#include "lexicon.h"
#include "multi_queue.h"
#include "queue.h"
#include <cmath> 

using namespace std;

void printTestResults(bool passed, int & testNum, int & passedCounter) {
	testNum++;
	if (passed) {
		passedCounter++;
		cout << "test " << testNum << " passed, total passed tests: " << passedCounter << endl;
	} else {
		cout << "test " << testNum << " failed, total passed tests: " << passedCounter << endl;
	}
}


long currTimeInMS() {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

bool equalsQueue(MultiQueue * q, int queueIndex, Queue<int> &qc) {
	if (qc.size() != q->size(queueIndex)) {
		return false;
	}

	while (!qc.isEmpty()) {
		if (qc.dequeue() != q->dequeue(queueIndex)) {
			return false;
		}	
	}
	return true;
}

bool singleQueueRandomTest(MultiQueue * q, int queueIndex) {
	Queue<int> qc;
	int num = randomInteger(100, 1000);
	for (int i=0; i<num; i++) {
		int v = randomInteger(0, 100);
		qc.enqueue(v);
		q->enqueue(queueIndex, v);
	}

	for (int i=0; i<num; i++) {
		int v = randomInteger(0, 100);
		int dequeue = randomChance(0.8);
		if (dequeue) {
			if (qc.dequeue() != q->dequeue(queueIndex)) {
				return false;
			}
		} else {
			qc.enqueue(v);
			q->enqueue(queueIndex, v);
		}
	}

	if (!equalsQueue(q, queueIndex, qc)) {
		return false;
	}

	for (int i=0; i<2*num; i++) {
		int v = randomInteger(0, 100);
		qc.enqueue(v);
		q->enqueue(queueIndex, v);
	}
	return equalsQueue(q, queueIndex, qc);
}

bool multiQueueRandomTest() { 
	MultiQueue * q;
	q = new MultiQueue();
	int num = randomInteger(1000, 10000);
	for (int i=0; i<num; i++) {
		q->addQueue();
	}
	
	for (int i=0; i<10; i++) {
		int indx = randomInteger(0, num-1);
		if (!singleQueueRandomTest(q, indx)) {
			return false;
		}
	}
	return true;
}

bool enqueueTimeTest() { 
	MultiQueue * q;
	q = new MultiQueue();
	for (int i=0; i<10000; i++) {
		q->addQueue();
	}
	int startTime = currTimeInMS();
	q->enqueue(0, 0);
	int endTime = currTimeInMS();
	int diff1 = endTime - startTime;
	startTime = currTimeInMS();
	q->enqueue(9999, 0);
	endTime = currTimeInMS();
	int diff2 = endTime - startTime;
	if (abs(diff2 - diff1) > 20) {
		return false;
	}

	for (int i=0; i<10000; i++) {
		q->enqueue(0, 0);
	}
	startTime = currTimeInMS();
	q->enqueue(0, 0);
	endTime = currTimeInMS();
	diff2 = endTime - startTime;
	if (abs(diff2 - diff1) > 20) {
		return false;
	}
	return true;
}

bool dequeueTimeTest() { 
	MultiQueue * q;
	q = new MultiQueue();
	q->addQueue();
	q->enqueue(0, 0);
	int startTime = currTimeInMS();
	q->dequeue(0);
	int endTime = currTimeInMS();
	int diff1 = endTime - startTime;

	for (int i=0; i<10000; i++) {
		q->enqueue(0, 0);
	}
	startTime = currTimeInMS();
	q->dequeue(0);
	endTime = currTimeInMS();
	int diff2 = endTime - startTime;
	if (abs(diff2 - diff1) > 20) {
		return false;
	}
	return true;
}

void runMultiQueueTests() {
	int testNum = 0;
	int passedCounter = 0;
	bool passed;
	
	MultiQueue * q;
	// #1
	q = new MultiQueue();
	passed = q->numQueues() == 0;
	printTestResults(passed, testNum, passedCounter);
	// #2
	q = new MultiQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	passed = q->numQueues() == 3;
	printTestResults(passed, testNum, passedCounter);
	// #3
	q = new MultiQueue();
	q->addQueue();
	passed = q->numQueues() == 1 && q->size(0) == 0;
	printTestResults(passed, testNum, passedCounter);
	// #4
	q = new MultiQueue();
	q->addQueue();
	q->enqueue(0, 1);
	q->enqueue(0, 2);
	passed = q->numQueues() == 1 && q->size(0) == 2;
	printTestResults(passed, testNum, passedCounter);
	// #5
	q = new MultiQueue();
	q->addQueue();
	q->enqueue(0, 1);
	q->enqueue(0, 2);
	passed = q->numQueues() == 1 && q->size(0) == 2;
	passed = passed && q->dequeue(0) == 1 && q->size(0) == 1;
	passed = passed && q->size(0) == 1 && q->dequeue(0) == 2 && q->size(0) == 0;
	printTestResults(passed, testNum, passedCounter);
	// #6
	q = new MultiQueue();
	q->addQueue();
	q->enqueue(0, 1);
	q->enqueue(0, 2);
	passed = q->numQueues() == 1 && q->size(0) == 2;
	passed = passed && q->dequeue(0) == 1 && q->size(0) == 1;
	q->enqueue(0, 3);
	passed = passed && q->size(0) == 2 && q->dequeue(0) == 2;
	passed = passed && q->size(0) == 1 && q->dequeue(0) == 3 && q->size(0) == 0;
	printTestResults(passed, testNum, passedCounter);
	// #7
	q = new MultiQueue();
	q->addQueue();
	q->enqueue(0, 1);
	q->enqueue(0, 2);
	q->dequeue(0);
	q->dequeue(0);
	q->enqueue(0, 11);
	q->enqueue(0, 21);
	passed = q->numQueues() == 1 && q->size(0) == 2;
	passed = passed && q->dequeue(0) == 11 && q->size(0) == 1;
	q->enqueue(0, 3);
	passed = passed && q->size(0) == 2 && q->dequeue(0) == 21;
	passed = passed && q->size(0) == 1 && q->dequeue(0) == 3 && q->size(0) == 0;
	printTestResults(passed, testNum, passedCounter);
	
	for (int i=8; i<=30; i++) {
		q = new MultiQueue();
		q->addQueue();
		passed = singleQueueRandomTest(q, 0);
		printTestResults(passed, testNum, passedCounter);
	}
	for (int i=31; i<=40; i++) {
		passed = multiQueueRandomTest();
		printTestResults(passed, testNum, passedCounter);
	}
	// #41 
	q = new MultiQueue();
	q->addQueue();
	q->addQueue();
	q->enqueue(0, 0);	
	q->enqueue(0, 0);	
	q->enqueue(1, 1);
	q->enqueue(1, 1);
	q->removeQueue(0);
	passed = q->numQueues() == 1 && q->size(0) == 4;
	passed = passed && q->dequeue(0) == 1 && q->dequeue(0) == 1;
	passed = passed && q->dequeue(0) == 0 && q->dequeue(0) == 0;
	printTestResults(passed, testNum, passedCounter);
	// #42 
	q = new MultiQueue();
	q->addQueue();
	q->addQueue();
	q->enqueue(0, 0);	
	q->enqueue(0, 0);	
	q->enqueue(1, 1);
	q->enqueue(1, 1);
	q->removeQueue(1);
	passed = q->numQueues() == 1 && q->size(0) == 4;
	passed = passed && q->dequeue(0) == 0 && q->dequeue(0) == 0;
	passed = passed && q->dequeue(0) == 1 && q->dequeue(0) == 1;
	q->removeQueue(0);
	passed = passed && q->numQueues() == 0;	
	printTestResults(passed, testNum, passedCounter);
	// #43
	q = new MultiQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->enqueue(1, 0);	
	q->enqueue(1, 0);	
	q->enqueue(1, 0);
	q->removeQueue(0);
	q->removeQueue(0);
	passed = q->numQueues() == 2 && q->size(0) == 2 && q->size(1) == 1;		
	printTestResults(passed, testNum, passedCounter);
	// #44
	q = new MultiQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->enqueue(1, 0);	
	q->enqueue(1, 1);	
	q->enqueue(1, 2);	
	q->removeQueue(0);
	q->removeQueue(0);
	q->removeQueue(0);
	passed = q->numQueues() == 1 && q->size(0) == 3;
	passed = passed && q->dequeue(0) == 1 && q->dequeue(0) == 0 && q->dequeue(0) == 2;
	printTestResults(passed, testNum, passedCounter);
	// #45
	q = new MultiQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->enqueue(0, 0);	
	q->enqueue(1, 1);	
	q->enqueue(2, 2);	
	q->enqueue(3, 3);	
	q->removeQueue(0);
	q->removeQueue(0);
	q->removeQueue(0);
	passed = q->numQueues() == 1 && q->size(0) == 4;
	passed = passed && q->dequeue(0) == 3 && q->dequeue(0) == 0 && q->dequeue(0) == 2 && q->dequeue(0) == 1;
	printTestResults(passed, testNum, passedCounter);
	// #46
	q = new MultiQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->addQueue();
	q->enqueue(0, 0);	
	q->enqueue(1, 1);	
	q->enqueue(2, 2);	
	q->enqueue(3, 3);	
	q->removeQueue(0);
	q->removeQueue(0);
	q->addQueue();
	q->removeQueue(0);
	passed = q->numQueues() == 2 && q->size(0) == 3 && q->size(1) == 1;
	passed = passed && q->dequeue(0) == 3 && q->dequeue(0) == 0 && q->dequeue(0) == 2 && q->dequeue(1) == 1;
	printTestResults(passed, testNum, passedCounter);
	// #47
	q = new MultiQueue();
	for (int i=0; i<100; i++) {
		q->addQueue();
	}
	q->enqueue(0, 1);
	for (int i=0; i<99; i++) {
		q->removeQueue(0);
	}
	passed = q->numQueues() == 1 && q->size(0) == 1 && q->dequeue(0) == 1;
	printTestResults(passed, testNum, passedCounter);
	// #48
	q = new MultiQueue();
	for (int i=0; i<100; i++) {
		q->addQueue();
	}
	q->enqueue(0, 0);
	q->enqueue(1, 1);
	q->enqueue(2, 2);
	for (int i=0; i<99; i++) {
		q->removeQueue(0);
	}
	passed = q->numQueues() == 1 && q->size(0) == 3;
	passed = passed && q->dequeue(0) == 0 && q->dequeue(0) == 2 && q->dequeue(0) == 1;
	printTestResults(passed, testNum, passedCounter);
	// #49
	q = new MultiQueue();
	for (int i=0; i<100; i++) {
		q->addQueue();
		q->enqueue(i, i);
	}
	for (int i=0; i<99; i++) {
		q->removeQueue(0);
	}
	passed = q->numQueues() == 1 && q->size(0) == 100 && q->dequeue(0) == 99 && q->dequeue(0) == 85;
	printTestResults(passed, testNum, passedCounter);
	// #50
	q = new MultiQueue();
	for (int i=0; i<100; i++) {
		q->addQueue();
		q->enqueue(i, i);
	}
	for (int i=0; i<99; i++) {
		q->removeQueue(99 - i);
	}
	passed = q->numQueues() == 1 && q->size(0) == 100 && q->dequeue(0) == 0 && q->dequeue(0) == 99;
	printTestResults(passed, testNum, passedCounter);

	if (!enqueueTimeTest()) {
		cout << "failed enqueue time test!! " << endl;
	}
	if (!dequeueTimeTest()) {
		cout << "failed dequeue time test!! " << endl;
	}
	cout << "###### passed " << passedCounter << " tests ######" << endl;
}


int main() {
	setRandomSeed(1);
	runMultiQueueTests();
	return 0;
}