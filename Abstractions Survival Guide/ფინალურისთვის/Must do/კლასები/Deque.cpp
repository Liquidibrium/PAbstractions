#include "Deque.h"

Deque::Deque(void)
{
	head = NULL;
	tail = NULL;
}

Deque::~Deque(void)
{
	while (head != NULL) {
		Node* tmp = head->next;
		delete head;
		head = tmp;
	}
}

bool Deque::isEmpty() {
	return head == NULL;
}

void Deque::pushBack(int value) {
	Node* node = new Node;
	node->value = value;
	node->prev = tail;
	node->next = NULL;
	if (head == NULL) head = node;
	else tail->next = node;
	tail = node;
}

void Deque::pushFront(int value) {
	Node* node = new Node;
	node->value = value;
	node->next = head;
	node->prev = NULL;
	if (head == NULL) tail = node;
	else head->prev = node;
	head = node;
}

int Deque::popBack() {
	if (head == NULL) error("empty");
	int value = tail->value;
	Node* tmp = tail;
	tail = tail->prev;
	if (tail == NULL) head = NULL;
	else tail->next = NULL;
	delete tmp;
	return value;
}

int Deque::popFront() {
	if (head == NULL) error("empty");
	int value = head->value;
	Node* tmp = head;
	head = head->next;
	delete tmp;
	if (head == NULL) tail = NULL;
	else head->prev = NULL;
	return value;
}