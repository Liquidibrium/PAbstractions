
#include "MyHashSet.h"
#include "error.h"

int const kNumBuckets = 1;

MyHashSet::MyHashSet() {
	numBuckets = kNumBuckets;
	data = new Node*[numBuckets];
	for (int i = 0; i < numBuckets; i++)
		data[i] = NULL;
	curSize = 0;
}

MyHashSet::~MyHashSet() {
	for (int i = 0; i < numBuckets; i++) {
		Node* first = data[i];
		while (first != NULL) {
			Node* tmp = first;
			first = first->next;
			delete tmp;
		}
	}
	delete[] data;
}

void MyHashSet::add(int key) {
	Node* node = findNode(key);
	if (node != NULL) return;
	node = new Node;
	node->key = key;
	int index = key % numBuckets;
	node->next = data[index];
	data[index] = node;
	curSize++;
	rehash();
}

void MyHashSet::remove(int key) {
	Node* prev = NULL;
	Node* cur = data[key % numBuckets];
	while (cur != NULL) {
		if (cur->key == key) {
			if (prev == NULL) data[key % numBuckets] = cur->next;
			else prev->next = cur->next;
			curSize--;
			delete cur;
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

bool MyHashSet::contains(int key) {
	return findNode(key) != NULL;
}

bool MyHashSet::isEmpty () {
	return size() == 0;
}

int MyHashSet::size() {
	return curSize;
}

MyHashSet::Node* MyHashSet::findNode(int key) {
	Node* node = data[key % numBuckets];
	while (node != NULL) {
		if (node->key == key)
			return node;
		node = node->next;
	}
	return NULL;
}

void MyHashSet::rehash() {

	if ((double) size() / numBuckets <= 2) return;

	Node** tmp = data;
	int newNumBuckets = numBuckets * 2;
	data = new Node*[newNumBuckets];
	for (int i = 0; i < newNumBuckets; i++)
		data[i] = NULL;

	for (int j = 0; j < numBuckets; j++) {
		Node* first = tmp[j];
		while (first != NULL) {
			Node* temp = first;
			first = first->next;
			int index = temp->key % newNumBuckets;
			temp->next = data[index];
			data[index] = temp;
		}
	}

	numBuckets = newNumBuckets;
	delete[] tmp;

}
