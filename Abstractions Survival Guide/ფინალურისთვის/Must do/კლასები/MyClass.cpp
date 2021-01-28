
#include "MyClass.h"

MyClass::MyClass() {
	root = NULL;
	curSize = 0;
}

MyClass::~MyClass() {
	freeTree(root);
}

void MyClass::freeTree(Node* r) {
	if (r != NULL) {
		freeTree(r->neighbors[0]);
		freeTree(r->neighbors[1]);
		delete r;
	}
}

bool MyClass::isEmpty() {
	return size() == 0;
}

int MyClass::size() {
	return curSize;
}

bool MyClass::containsNumber(string n) {
	Node* node = findNode(n);
	return node != NULL && node->isNumber;
}

bool MyClass::containsPrefix(string pref) {
	return findNode(pref) != NULL;
}

MyClass::Node* MyClass::findNode(string &n) {
	return recFindNode(0, n, root);
}

MyClass::Node* MyClass::recFindNode(int index, string &n, Node* r) {
	if (index == n.length()) return r;
	if (r == NULL) return NULL;
	return recFindNode(index + 1, n, r->neighbors[n[index] - '0']);
}

void MyClass::addNumber(string n) {
	recAddNumber(0, n, root);
}

void MyClass::recAddNumber(int index, string &n, Node* &r) {
	if (r == NULL) {
		r = new Node;
		r->isNumber = false;
		r->neighbors[0] = NULL;
		r->neighbors[1] = NULL;
	}
	if (index == n.length()) {
		if (!r->isNumber) curSize++;
		r->isNumber = true;
	}
	else recAddNumber(index + 1, n, r->neighbors[n[index] - '0']);
}

void MyClass::removeNumber(string n) {
	recRemoveNumber(0, n, root);
}

void MyClass::recRemoveNumber(int index, string &n, Node* &r) {
	if (r == NULL) return;
	if (index == n.length()) {
		if (r->isNumber) curSize--;
		r->isNumber = false;
	}
	else recRemoveNumber(index + 1, n, r->neighbors[n[index] - '0']);

	if (r->neighbors[0] == NULL
		 && r->neighbors[1] == NULL
		  && !r->isNumber) {
		delete r;
		r = NULL;
	}
}
