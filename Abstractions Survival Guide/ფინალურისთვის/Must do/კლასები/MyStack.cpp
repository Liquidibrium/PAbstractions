
#include "MyStack.h"
#include "error.h"

MyStack::MyStack() {
	head = NULL;
	curSize = 0;
}

MyStack::~MyStack() {
	clear();
}

void MyStack::clear() {
	while (head != NULL) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
	curSize = 0;
}

bool MyStack::isEmpty() {
	return size() == 0;
}

int MyStack::peek() {
	if (isEmpty()) error("");
	return head->value;
}

int MyStack::pop() {
	int value = peek();
	Node* tmp = head;
	head = head->next;
	delete tmp;
	curSize--;
	return value;
}

void MyStack::push(int value) {
	Node* n = new Node;
	n->value = value;
	n->next = head;
	head = n;
	curSize++;
}

int MyStack::size() {
	return curSize;
}
