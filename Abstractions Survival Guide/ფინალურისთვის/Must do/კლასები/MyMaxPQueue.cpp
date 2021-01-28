
#include "MyMaxPQueue.h"

MyMaxPQueue::MyMaxPQueue() {
	alocSize = START_ALOCATED_SIZE_;
	data = new int[alocSize];
	logSize = 0;
}

MyMaxPQueue::~MyMaxPQueue() {
	delete[] data;
}

int MyMaxPQueue::size() {
	return logSize;
}

bool MyMaxPQueue::isEmpty() {
	return size() == 0;
}

void MyMaxPQueue::enqueue(int value) {
	checkAlocSize();
	data[logSize++] = value;
	int son = size() - 1;
	int par = (son - 1) / 2;
	while (son != 0 && data[son] > data[par]) {
		swap(son, par);
		son = par;
		par = (son - 1) / 2;
	}
}

int MyMaxPQueue::peek() {
	if (isEmpty()) return -1;
	return data[0];
}

int MyMaxPQueue::dequeueMax() {
	if (isEmpty()) return -1;
	swap(0, size() - 1);
	int max = data[--logSize];
	int par = 0;
	while (true) {
		int son = getBiggestSon(par);
		if (son == -1) break;
		if (data[par] >= data[son]) break;
		swap(par, son);
		par = son;
	}
	return max;
}

void MyMaxPQueue::checkAlocSize() {
	if (size() != alocSize) return;
	int* tmp = data;
	alocSize *= 2;
	data = new int[alocSize];
	for (int i = 0; i < size(); i++)
		data[i] = tmp[i];
	delete[] tmp;
}

int MyMaxPQueue::getBiggestSon(int parent) {
	int son1 = 2 * parent + 1;
	int son2 = 2 * parent + 2;
	if (son1 >= size()) return -1;
	if (son2 >= size()) return son1;
	return data[son1] > data[son2] ? son1 : son2;
}

void MyMaxPQueue::swap(int i, int j) {
	int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}
