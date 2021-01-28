
#include "MyIntLexicon.h"
#include "error.h"
#include "strlib.h"

MyIntLexicon::MyIntLexicon() {
	root = NULL;
	curSize = 0;
}

MyIntLexicon::~MyIntLexicon() {
	freeTree(root);
}

void MyIntLexicon::freeTree(Node* r) {
	if (r != NULL) {
		for (int i = 0; i < 10; i++)
			freeTree(r->children[i]);
		delete r;
	}
}

bool MyIntLexicon::isEmpty() {
	return size() == 0;
}

int MyIntLexicon::size() {
	return curSize;
}

bool MyIntLexicon::containsNumber(int n) {
	Node* node = findNode(n);
	if (node == NULL) return false;
	if (n == 0) return true;
	if (n < 0 && node->isNegative) return true;
	if (n > 0 && node->isPositive) return true;
	return false;
}

MyIntLexicon::Node* MyIntLexicon::findNode(int n) {
	int tmp = n; if (n < 0) tmp *= -1;
	string str_n = integerToString(tmp);
	return recFindNode(root, 0, str_n);
}

MyIntLexicon::Node* MyIntLexicon::recFindNode(Node* r, int i, string &n) {
	if (i == n.length()) return r;
	if (r == NULL) return NULL;
	return recFindNode(r->children[n[i] - '0'], i + 1, n);
}

void MyIntLexicon::addNumber(int n) {
	int tmp = n; if (tmp < 0) tmp *= -1;
	string str_n = integerToString(tmp);
	recAddNumber(root, 0, str_n, n);
}

void MyIntLexicon::recAddNumber(Node*& r, int i, string &n, int number) {
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
			if (!r->isPositive) curSize++;
			r->isPositive = true;
		}
	} else recAddNumber(r->children[n[i] - '0'], i + 1, n, number);
}

void MyIntLexicon::removeNumber(int n) {
	int tmp = n; if (tmp < 0) tmp *= -1;
	string str_n = integerToString(tmp);
	recRemoveNumber(root, 0, str_n, n);
}

void MyIntLexicon::recRemoveNumber(Node*& r, int i, string &n, int number) {
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
