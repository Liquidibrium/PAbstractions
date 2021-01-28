
#ifndef MYQueue
#define MYQueue

#include "myStack.h"

class myQueue {
public:
	void enqueue(int value);
	int dequeue();
	int peek();
	
	bool isEmpty();
	int size();

private:
//		myStack in;
//		myStack out;
};


#endif
