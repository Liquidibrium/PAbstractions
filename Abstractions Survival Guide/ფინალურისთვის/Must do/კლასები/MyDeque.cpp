
#include "MyDeque.h"
#include "error.h"

MyDeque::MyDeque() {
	head = NULL;
	tail = NULL;
	curSize = 0;
}

MyDeque::~MyDeque() {
	while (head != NULL) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
}

bool MyDeque::isEmpty() {
	return curSize == 0;
}

void MyDeque::pushFront(int value) {
	Node* tmp = new Node;
	tmp->value = value;
	tmp->prev = NULL;
	tmp->next = head;
	if (isEmpty()) tail = tmp;
	else head->prev = tmp;
	head = tmp;
	curSize++;
}

void MyDeque::pushBack(int value) {
	Node* tmp = new Node;
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = tail;
	if (isEmpty()) head = tmp;
	else tail->next = tmp;
	tail = tmp;
	curSize++;
}

int MyDeque::popFront() {
	if (isEmpty()) return -1;
	Node* tmp = head;
	head = head->next;
	if (head == NULL) tail = NULL;
	else head->prev = NULL;
	int value = tmp->value;
	delete tmp;
	curSize--;
	return value;
}

int MyDeque::popBack() {
	if (isEmpty()) return -1;
	Node* tmp = tail;
	tail = tail->prev;
	if (tail == NULL) head = NULL;
	else tail->next = NULL;
	int value = tmp->value;
	delete tmp;
	curSize--;
	return value;
}
