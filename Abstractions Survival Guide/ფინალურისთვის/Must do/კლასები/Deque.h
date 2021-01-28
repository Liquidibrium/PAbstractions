#pragma once
#include "error.h"

class Deque
{
private:
	struct Node {
		int value;
		Node* next;
		Node* prev;
	};
	Node* head;
	Node* tail;

public:
	Deque(void);
	~Deque(void);
	bool isEmpty();
	void pushBack(int value);
	void pushFront(int value);
	int popBack();
	int popFront();
};
