/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
 
#include "pqueue-extra.h"
#include "error.h"

ExtraPriorityQueue::ExtraPriorityQueue() {
	// TODO: Fill this in!
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	// TODO: Fill this in!
}

int ExtraPriorityQueue::size() {
	return queue.size();
}

bool ExtraPriorityQueue::isEmpty() {
	return queue.isEmpty();
}

void ExtraPriorityQueue::enqueue(string value) {
	if(isEmpty()) queue.add(value);
	else{
		int start = 0 ;
		int end = size();
		int middle;
		while(start<end){
			middle = (start+end)/2;
			if(queue[middle].compare(value)==1){
				start = middle +1;
			}else if(queue[middle].compare(value)== -1){
				end = middle;
			}else {
				start = middle;
				break;
			}
		}
		queue.insert(start,value);
	}
}

string ExtraPriorityQueue::peek() {
	if(isEmpty()) error(" fafu");
	return queue[queue.size()-1];
}

string ExtraPriorityQueue::dequeueMin() {
	if(isEmpty()) error(" fafu");
	string str = queue[queue.size()-1];
	queue.remove(queue.size()-1);
	return str;
}

