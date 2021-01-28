
#include "MyVector.h"

MyVector::MyVector() {
	alocSize = START_ALOCATED_SIZE;
	data = new int[alocSize];
	logSize = 0;
}

MyVector::~MyVector() {
	delete[] data;
}

void MyVector::add(int value) {
	checkAlocSize();
	data[logSize++] = value;
}

int MyVector::get(int index) {
	if (index >= size()) return -1;
	return data[index];
}

void MyVector::insert(int index, int value) {
	if (index > size()) return;
	if (index == size()) {
		add(value);
		return;
	}
	checkAlocSize();
	for (int i = size() - 1; i >= index; i--)
		data[i + 1] = data[i];
	data[index] = value;
	logSize++;
}

bool MyVector::isEmpty() {
	return size() == 0;
}

void MyVector::remove(int index) {
	if (index >= size()) return;
	for (int i = index; i < size() - 1; i++)
		data[i] = data[i + 1];
	logSize--;
}

int MyVector::size() {
	return logSize;
}

void MyVector::clear() {
	delete[] data;
	alocSize = START_ALOCATED_SIZE;
	data = new int[alocSize];
	logSize = 0;
}

void MyVector::checkAlocSize() {
	if (size() == alocSize) {
		int* tmp = data;
		alocSize *= 2;
		data = new int[alocSize];
		for (int i = 0; i < logSize; i++)
			data[i] = tmp[i];
		delete[] tmp;
	}
}
