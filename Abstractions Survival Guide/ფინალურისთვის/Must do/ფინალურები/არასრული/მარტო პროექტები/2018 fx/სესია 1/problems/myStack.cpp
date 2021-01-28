#include "myStack.h"


const int DefaultSize = 10;

myStack::OurStack() {
	numElements = 0;
	allocated = DefaultSize;
	elems = new int[allocated];
}

myStack::~OurStack() {
	delete[] elems;
}

int myStack::size() {
	return numElements;
}

bool myStack::isEmpty() {
	return size() == 0;
}

void myStack::grow() {
	allocated *= 2;
	int* newArray = new int[allocated];
	for (int i = 0; i < numElements; i++) {
		newArray[i] = elems[i];
	}
	delete[] elems;
	elems = newArray;
}
void myStack::push(int value) {
	if (allocated == numElements) {
		grow();
	}
	elems[numElements] = value;
	numElements++;
}

int myStack::peek() {
	return elems[numElements - 1];
}

int myStack::pop() {
	int result = peek();
	numElements--;
	return result;
}



