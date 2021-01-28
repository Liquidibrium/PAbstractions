
#include "MySet.h"
#include <iostream>
using namespace std;

MySet :: MySet () {
	root = NULL;
	curSize = 0;
}

void MySet :: freeTree (Node* r) {
	if (r != NULL) {
		freeTree (r->left);
		freeTree (r->right);
		delete r;
	}
}

MySet :: ~MySet () {
	freeTree (root);
}

MySet :: Node*& MySet :: recFindNode (Node*& r, int key) {
	if (r == NULL || key == r->key) return r;
	if (key < r->key) return recFindNode (r->left, key);
	return recFindNode (r->right, key);
}

MySet :: Node*& MySet :: findNode (int key) {
	return recFindNode (root, key);
}

void MySet :: add (int key) {
	Node*& node = findNode (key);
	if (node != NULL) return;
	node = new Node;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	curSize++;
}

MySet :: Node*& MySet :: findSubstitute (Node* node) {
	Node*& subs = node->left;
	while (subs->right != NULL)
		subs = subs->right;
	return subs;
}

void MySet :: remove (int key) {
	Node*& node = findNode (key);
	if (node == NULL) return;
	if (node->left == NULL && node->right == NULL) {
		delete node;
		node = NULL;
	} else if (node->left != NULL && node->right == NULL) {
		Node* left = node->left;
		delete node;
		node = left;
	} else if (node->left == NULL && node->right != NULL) {
		Node* right = node->right;
		delete node;
		node = right;
	} else {
		Node*& subs = findSubstitute (node);
		node->key = subs->key;
		Node* subs_left = subs->left;
		delete subs;
		subs = subs_left;
	}
	curSize--;
}

bool MySet :: contains (int key) {
	Node*& node = findNode (key);
	return node != NULL;
}

int MySet :: first () {
	if (root == NULL) return -1;
	Node* leftest = root;
	while (leftest->left != NULL)
		leftest = leftest->left;
	return leftest->key;
}

bool MySet :: isEmpty () {
	return size() == 0;
}

int MySet :: size () {
	return curSize;
}

void MySet :: recPrintSet(Node* r) {
	if (r != NULL) {
		recPrintSet(r->left);
		cout << r->key << ' ';
		recPrintSet(r->right);
	}
}

void MySet :: printSet() {
	recPrintSet(root);
	cout << '\n';
}
