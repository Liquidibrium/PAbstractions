
#include "MyPQueue.h"
#include "error.h"

MyPQueue::MyPQueue() {
	alocSize = START_ALOCATED_SIZE;
	data = new int[alocSize];
	logSize = 0;
}

MyPQueue::~MyPQueue() {
	delete[] data;
}

int MyPQueue::size() {
	return logSize;
}

bool MyPQueue::isEmpty() {
	return size() == 0;
}

void MyPQueue::enqueue(int value) {
	checkAlocSize();
	data[logSize++] = value;
	int son_i = size() - 1;
	int par_i = (son_i - 1) / 2;
	while (son_i != 0 && data[son_i] < data[par_i]) {
		swap(son_i, par_i);
		son_i = par_i;
		par_i = (son_i - 1) / 2;
	}
}

int MyPQueue::peek() {
	if (isEmpty()) error("error");
	return data[0];
}

int MyPQueue::dequeueMin() {
	int min = peek();
	data[0] = data[size() -  1];
	logSize--;
	int par_i = 0;
	while (true) {
		int son_i = getLessSonIndex(par_i);
		if (son_i == -1) break;
		if (data[par_i] <= data[son_i]) break;
		swap(son_i, par_i);
		par_i = son_i;
	}
	return min;
}

void MyPQueue::checkAlocSize() {
	if (size() == alocSize) {
		int* tmp = data;
		alocSize *= 2;
		data = new int[alocSize];
		for (int i = 0; i < size(); i++)
			data[i] = tmp[i];
		delete[] tmp;
	}
}

void MyPQueue::swap(int i, int j) {
	int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}

int MyPQueue::getLessSonIndex(int par_i) {
	int son1_i = 2 * par_i + 1;
	int son2_i = 2 * par_i + 2;
	if (son1_i >= size()) return -1;
	if (son2_i >= size()) return son1_i;
	int son1 = data[son1_i];
	int son2 = data[son2_i];
	if (son1 < son2) return son1_i;
	return son2_i;
}
