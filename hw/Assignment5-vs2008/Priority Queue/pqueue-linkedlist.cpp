/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"


LinkedListPriorityQueue::LinkedListPriorityQueue() {
	first = NULL;
	length = 0 ;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while(first!=NULL){
		Node *nxt = first->next;
		delete first;
		first = nxt ;
	}
}

int LinkedListPriorityQueue::size() {	
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return length==0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node* newNode = new Node;
	newNode->value = value;
	if(isEmpty()) {
		newNode->next = first ;
		first = newNode;
	}
	else if((first->value).compare(value) == 1){
			newNode->next = first;
			first = newNode; 
		}
	else{
		Node *nd = first;
		while(nd->next != NULL && (nd->next->value).compare(value) == -1){
			nd = nd->next;
		}
		newNode->next = nd->next;
		nd->next = newNode;
	}
	length++;
}

string LinkedListPriorityQueue::peek() {
	if(isEmpty()) error(" fafu ");
	return first->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()) error(" fafu ");
	length--;
	string str = first->value;
	Node* tmp = first->next;
	delete first;
	first = tmp;
	return str;
}

