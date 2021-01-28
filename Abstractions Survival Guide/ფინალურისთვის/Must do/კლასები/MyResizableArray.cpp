
#include "MyResizableArray.h"
#include "error.h"

MyResizableArray::MyResizableArray(int size) {
	curSize = size;
	data = new double[curSize];
	for (int i = 0; i < curSize; i++)
		data[i] = 0.0;
}

MyResizableArray::~MyResizableArray() {
	delete[] data;
}

void MyResizableArray::resize(int newSize) {
	double* tmp = data;
	data = new double[newSize];
	for (int i = 0; i < curSize; i++)
		data[i] = tmp[i];
	for (int j = curSize; j < newSize; j++)
		data[j] = 0.0;
	curSize = newSize;
	delete[] tmp;
}

double MyResizableArray::getAt(int index) {
	if (index < 0 || index >= curSize) error("");
	return data[index];
}

void MyResizableArray::setAt(int index, double value) {
	if (index < 0 || index >= curSize) error("");
	data[index] = value;
}

int MyResizableArray::size() {	return curSize;}