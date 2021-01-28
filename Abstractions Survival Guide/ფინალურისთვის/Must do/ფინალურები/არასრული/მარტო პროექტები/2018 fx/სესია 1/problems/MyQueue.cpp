#include "myQueue.h"

bool myQueue::isEmpty() {
	return in.isEmpty() && out.isEmpty();
}

int myQueue::size() {
	return in.size() + out.size();
}

void myQueue::enqueue(int value) {
	in.push(value);
}

int myQueue::peek() {
	if (out.isEmpty()) {
		while (!in.isEmpty()) {
			out.push(in.pop());
		}
	}
	
	return out.peek();
}

int myQueue::dequeue() {
	int result = peek();
	out.pop();
	return result;
}
