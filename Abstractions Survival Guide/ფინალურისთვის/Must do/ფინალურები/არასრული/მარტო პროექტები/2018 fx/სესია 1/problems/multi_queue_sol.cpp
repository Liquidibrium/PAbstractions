#include "multi_queue.h"

#define INIT_ALLOC_LEN 10

MultiQueue::MultiQueue() {
	allocLen = INIT_ALLOC_LEN;
	queues = new Queue[allocLen];
	for (int i=0; i<allocLen; i++) {
		queues[i].size = 0;
		queues[i].list = NULL;
		queues[i].tail = NULL;
	}
	logLen = 0;
}
int MultiQueue::numQueues() {
	return logLen;
}
int MultiQueue::size(int qPos) {
	return queues[qPos].size;
}
void MultiQueue::doubleSpace() {
	allocLen *= 2;
	Queue *queuesTmp = new Queue[allocLen];
	for (int i=0; i<allocLen/2; i++) {
		queuesTmp[i].size = queues[i].size;
		queuesTmp[i].list = queues[i].list;
		queuesTmp[i].tail = queues[i].tail;
	}
	queues = queuesTmp;
}

void MultiQueue::addQueue() {
	if (allocLen == logLen) {
		doubleSpace();
	}
	queues[logLen].size = 0;
	queues[logLen].list = NULL;
	queues[logLen].tail = NULL;
	logLen++;
}
void MultiQueue::removeQueue(int qPos) {
	Queue q = queues[qPos];
	logLen--;
	if (logLen == 0) {
		return;
	}
	for (int i=qPos; i<logLen; i++) {
		queues[i] = queues[i+1];
	}
	Node * curr = q.list;
	int index = 0;
	while (curr != NULL) {
		enqueue(index % logLen, curr->v);
		index++;
		curr = curr->next;
	}
}
void MultiQueue::enqueue(int qPos, int v) {
	Node * el = new Node;
	el->next = NULL;
	el->v = v;
	queues[qPos].size++;
	if (queues[qPos].list == NULL) {
		queues[qPos].list = el;
		queues[qPos].tail = el;
	} else {
		queues[qPos].tail->next = el;		
		queues[qPos].tail = el;
	}
}
int MultiQueue::dequeue(int qPos) {
	int v = queues[qPos].list->v;
	queues[qPos].size--;
	if (queues[qPos].size == 0) {
		queues[qPos].list = NULL;
		queues[qPos].tail = NULL;
	} else {
		queues[qPos].list = queues[qPos].list->next;
	}
	return v;
}
