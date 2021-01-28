
#include "MyBitsicon.h"

MyBitsicon::MyBitsicon() {
	root = NULL;
	curSize = 0;
}

MyBitsicon::~MyBitsicon() {
	freeTree(root);
}

void MyBitsicon::freeTree(Node* r) {
	if (r != NULL) {
		freeTree(r->neighbors[0]);
		freeTree(r->neighbors[1]);
		delete r;
	}
}

bool MyBitsicon::isEmpty() {
	return size() == 0;
}

int MyBitsicon::size() {
	return curSize;
}

bool MyBitsicon::containsNumber(string n) {
	Node* node = findNode(n);
	return node != NULL && node->isNumber;
}

bool MyBitsicon::containsPrefix(string pref) {
	return findNode(pref) != NULL;
}

MyBitsicon::Node* MyBitsicon::findNode(string &n) {
	return recFindNode(0, n, root);
}

MyBitsicon::Node* MyBitsicon::recFindNode(int index, string &n, Node* r) {
	if (index == n.length()) return r;
	if (r == NULL) return NULL;
	return recFindNode(index + 1, n, r->neighbors[n[index] - '0']);
}

void MyBitsicon::addNumber(string n) {
	recAddNumber(0, n, root);
}

void MyBitsicon::recAddNumber(int index, string &n, Node* &r) {
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

void MyBitsicon::removeNumber(string n) {
	recRemoveNumber(0, n, root);
}

void MyBitsicon::recRemoveNumber(int index, string &n, Node* &r) {
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
