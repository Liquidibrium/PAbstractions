/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"


VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	return queue.size();
}

bool VectorPriorityQueue::isEmpty() {
	return queue.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	queue.add(value);
}

string VectorPriorityQueue::peek() {
	if(isEmpty()) error(" fafu");
	int currMin=0;
	for(int i = 1; i<queue.size();i++){
		if(queue[i].compare(queue[currMin])==-1){
			currMin = i;
		}
	}
	return queue[currMin];
}

string VectorPriorityQueue::dequeueMin() {
	if(isEmpty()) error(" fafu");
	int currMin=0;
	for(int i = 1; i<queue.size();i++){
		if(queue[i].compare(queue[currMin])==-1){
			currMin = i;
		}
	}
	string str = queue[currMin];
	queue.remove(currMin);
	return str;
}

