
#include "MyHashMap.h"
#include "error.h"
#include <iostream>
using namespace std;

const int kNumBuckets = 1;

MyHashMap::MyHashMap() {
	numBuckets = kNumBuckets;
	arr = new Node*[numBuckets];
	for (int i = 0; i < numBuckets; i++)
		arr[i] = NULL;
	curSize = 0;
}

MyHashMap::~MyHashMap() {
	for (int i = 0; i < numBuckets; i++) {
		Node* head = arr[i];
		while (head != NULL) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
	}
	delete[] arr;
}

MyHashMap::Node* MyHashMap::findNode(int key) {
	Node* node = arr[key % numBuckets];
	while (node != NULL) {
		if (node->key == key) return node;
		node = node->next;
	}
	return NULL;
}

bool MyHashMap::containsKey(int key) {
	return findNode(key) != NULL;
}

int MyHashMap::get(int key) {
	Node* node = findNode(key);
	if (node == NULL) return -1;
	return node->value;
}

bool MyHashMap::isEmpty() {
	return size() == 0;
}

void MyHashMap::put(int key, int value) {
	Node* node = findNode(key);
	if (node != NULL) {
		node->value = value;
	} else {
		node = new Node;
		node->key = key;
		node->value = value;
		node->next = arr[key % numBuckets];
		arr[key % numBuckets] = node;
		curSize++;
		rehash();
	}
}

void MyHashMap::remove(int key) {
	Node* prev = NULL;
	Node* cur = arr[key % numBuckets];
	while (cur != NULL) {
		if (cur->key == key) {
			if (prev != NULL) prev->next = cur->next;
			else arr[key % numBuckets] = cur->next;
			delete cur;
			curSize--;
			break;
		}
		prev = cur;
		cur = cur->next;
	}
}

int MyHashMap::size() {
	return curSize;
}

/**/
void MyHashMap::rehash() {

	if ((double)curSize/numBuckets <= 2) return;

	int newNumBuckets = numBuckets * 2;
	Node** newArr = new Node*[newNumBuckets];
	for (int i = 0; i < newNumBuckets; i++)
		newArr[i] = NULL;

	for (int j = 0; j < numBuckets; j++) {
		Node* head = arr[j];
		while (head != NULL) {
			int index = head->key % newNumBuckets;
			Node* next = head->next;
			head->next = newArr[index];
			newArr[index] = head;
			head = next;
		}
	}

	numBuckets = newNumBuckets;
	delete[] arr;
	arr = newArr;

}
