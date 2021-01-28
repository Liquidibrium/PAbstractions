
#include "MyStack_.h"

MyStack_::MyStack_() {
	logSize = 0;
	alocSize = START_ALOCATED_SIZE_;
	data = new int[alocSize];
}

MyStack_::~MyStack_() {
	delete[] data;
}

void MyStack_::clear() {
	alocSize = START_ALOCATED_SIZE_;
	delete[] data;
	data = new int[alocSize];
	logSize = 0;
}

bool MyStack_::isEmpty() {
	return size() == 0;
}

int MyStack_::peek() {
	if (isEmpty()) return -1;
	return data[size() - 1];
}

int MyStack_::pop() {
	if (isEmpty()) return -1;
	return data[--logSize];
}

void MyStack_::push(int value) {
	checkAlocSize();
	data[logSize++] = value;
}

int MyStack_::size() {
	return logSize;
}

void MyStack_::checkAlocSize() {
	if (size() == alocSize) {
		int* tmp = data;
		alocSize *= 2;
		data = new int[alocSize];
		for (int i = 0; i < size(); i++)
			data[i] = tmp[i];
		delete[] tmp;
	}
}
