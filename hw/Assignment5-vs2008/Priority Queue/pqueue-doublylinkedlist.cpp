/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"
#include <iostream>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	length = 0;
	first = NULL;
	last = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (first != NULL){
		Node *tmp = first;
		first = first->next;
		delete tmp;
	  }
}

int DoublyLinkedListPriorityQueue::size() {	
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {	
	return length == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	Node* nd = new Node;
	nd->value = value;
	nd->prev = NULL;
	if(isEmpty()){
		nd->next = NULL;
		first = nd;
		last = nd;
	}
	else{
		nd->next = first;
		first->prev = nd;
		first = nd;
	}
	length++;
}

string DoublyLinkedListPriorityQueue::peek() {
	if(isEmpty()) error(" emprty");
	Node* currMin = first;
	for(Node* curr = first->next; curr!=NULL; curr = curr->next){
		if((curr->value).compare(currMin->value) == -1)
			currMin = curr;
	}
	return currMin->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if(isEmpty()) error(" emprty");					
	string str =  first->value;
	if(size() == 1){
		first = NULL;
		last = NULL;
	}
	else{
		Node* currMin = first;
		Node* curr = currMin->next;
		while(curr->next!=NULL){
			if((curr->value).compare(currMin->value) == -1)	{
				currMin = curr;
			}
			curr = curr->next;
		}
		if((curr->value).compare(currMin->value) == -1)	{
				currMin = curr;
			}
		str = currMin->value;
		if(currMin->next!=NULL && currMin->prev !=NULL){
			currMin->prev->next=currMin->next;
			currMin->next->prev=currMin->prev;
		}else if(currMin->next==NULL){	
			currMin->prev->next=currMin->next;
			last = currMin->prev;
		}else if(currMin->prev==NULL){
			currMin->next->prev=currMin->prev;
			first = currMin->next;
		}
		delete currMin;
	}
	length--;
	return str;

}

