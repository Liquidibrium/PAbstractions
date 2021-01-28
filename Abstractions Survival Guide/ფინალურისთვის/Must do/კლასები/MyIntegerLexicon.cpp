
#include "MyIntegerLexicon.h"
#include "error.h"
#include "strlib.h"

MyIntegerLexicon::MyIntegerLexicon() {
	root = NULL;
	curSize = 0;
}

MyIntegerLexicon::~MyIntegerLexicon() {
	freeTree(root);
}

void MyIntegerLexicon::freeTree(Node* r) {
	if (r != NULL) {
		for (int i = 0; i < 10; i++)
			freeTree(r->children[i]);
		delete r;
	}
}

bool MyIntegerLexicon::isEmpty() {
	return size() == 0;
}

int MyIntegerLexicon::size() {
	return curSize;
}

bool MyIntegerLexicon::containsNumber(int n) {
	int tmp = n; if (tmp < 0) tmp *= -1;
	Node* node = findNode(tmp);
	if (node == NULL) return false;
	if (n == 0) return true;
	if (n > 0 && node->isPositive) return true;
	if (n < 0 && node->isNegative) return true;
	return false;
}

MyIntegerLexicon::Node* MyIntegerLexicon::findNode(int n) {
	return recFindNode(root, 0, integerToString(n));
}

MyIntegerLexicon::Node* MyIntegerLexicon::recFindNode(Node* r, int i, string &n) {
	if (i == n.length()) return r;
	if (r == NULL) return NULL;
	return recFindNode(r->children[n[i] - '0'], i + 1, n);
}

void MyIntegerLexicon::addNumber(int n) {
	int tmp = n; if (tmp < 0) tmp *= -1;
	string str = integerToString(tmp);
	recAddNumber(root, 0, str, n);
}

void MyIntegerLexicon::recAddNumber(Node*& r, int i, string &n, int number) {
	bool rootWasNull = false;
	if (r == NULL) {
		r = new Node;
		for (int j = 0; j < 10; j++)
			r->children[j] = NULL;
		r->isNegative = false;
		r->isPositive = false;
		rootWasNull = true;
	}
	if (i == n.length()) {
		if (number == 0) {
			if (rootWasNull) curSize++;
		}
		else if (number < 0) {
			if (!r->isNegative) curSize++;
			r->isNegative = true;
		}
		else {
			if (!r->isPositive)	curSize++;
			r->isPositive = true;
		}
	} else recAddNumber(r->children[n[i] - '0'], i + 1, n, number);
}

void MyIntegerLexicon::removeNumber(int n) {
	int tmp = n; if (tmp < 0) tmp *= -1;
	string str = integerToString(tmp);
	recRemoveNumber(root, 0, str, n);
}

void MyIntegerLexicon::recRemoveNumber(Node*& r, int i, string &n, int number) {
	if (r == NULL) return;
	if (i == n.length()) {
		if (number == 0) curSize--;
		else if (number < 0) {
			if (r->isNegative) curSize--;
			r->isNegative = false;
		}
		else {
			if (r->isPositive) curSize--;
			r->isPositive = false;
		}
	} else recRemoveNumber(r->children[n[i] - '0'], i + 1, n, number);

	for (int j = 0; j < 10; j++)
		if (r->children[j] != NULL) return;

	if (!r->isNegative && !r->isPositive) {
		delete r;
		r = NULL;
	}
}
