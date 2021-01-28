
#include "MyPQueue_.h"
#include "error.h"

MyPQueue_::MyPQueue_() {
	head = tail = NULL;
	curSize = 0;
}

MyPQueue_::~MyPQueue_() {
	while (head != NULL) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
}

int MyPQueue_::size() {
	return curSize;
}

bool MyPQueue_::isEmpty() {
	return size() == 0;
}

int MyPQueue_::peekMin() {
	if (isEmpty()) error("");
	return head->value;
}

int MyPQueue_::peekMax() {
	if (isEmpty()) error("");
	return tail->value;
}

void MyPQueue_::enqueue(int value) {

	Node* node = new Node;
	node->value = value;
	node->prev = node->next = NULL;

	curSize++;

	if (size() == 1) {
		head = tail = node;
		return;
	}
	
	if (value <= head->value) {
		head->prev = node;
		node->next = head;
		head = node;
		return;
	}

	if (value >= tail->value) {
		tail->next = node;
		node->prev = tail;
		tail = node;
		return;
	}

	Node* place = head;
	while (place->value < value)
		place = place->next;

	node->prev = place->prev;
	node->next = place;

	node->prev->next = node;
	node->next->prev = node;

}

int MyPQueue_::dequeueMin() {
	int min = peekMin(); curSize--;
	Node* tmp = head;
	head = head->next;
	delete tmp;
	if (head == NULL) tail = NULL;
	else head->prev = NULL;
	return min;
}

int MyPQueue_::dequeueMax() {
	int max = peekMax(); curSize--;
	Node* tmp = tail;
	tail = tail->prev;
	delete tmp;
	if (tail == NULL) head = NULL;
	else tail->next = NULL;
	return max;
}
