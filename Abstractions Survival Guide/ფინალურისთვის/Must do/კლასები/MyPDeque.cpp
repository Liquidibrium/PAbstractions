
#include "MyPDeque.h"
#include "error.h"

MyPDeque::MyPDeque() {
	root = NULL;
	curSize = 0;
}

MyPDeque::~MyPDeque() {
	freeTree(root);
}

void MyPDeque::freeTree(Node* r) {
	if (r != NULL) {
		freeTree(r->left);
		freeTree(r->right);
		delete r;
	}
}

int MyPDeque::size() {
	return curSize;
}

bool MyPDeque::isEmpty() {
	return size() == 0;
}

void MyPDeque::enqueue(int value) {
	Node** node = findNode(value);
	while ((*node) != NULL) {
		if (value < (*node)->value)
			node = &(*node)->left;
		else node = &(*node)->right;
	}
	Node* newNode = new Node;
	newNode->value = value;
	newNode->left = newNode->right = NULL;
	*node = newNode;
	curSize++;
}

MyPDeque::Node** MyPDeque::findNode(int value) {
	return recFindNode(&root, value);
}

MyPDeque::Node** MyPDeque::recFindNode(Node** r, int value) {
	if ((*r) == NULL || (*r)->value == value) return r;
	if (value < (*r)->value) return recFindNode(&(*r)->left, value);
	return recFindNode(&(*r)->right, value);
}

int MyPDeque::peekMin() {
	return (*findSmallest())->value;
}

int MyPDeque::peekMax() {
	return (*findBiggest())->value;
}

int MyPDeque::dequeueMin() {
	if (isEmpty()) return -1;
	Node** s = findSmallest();
	Node* smallest = *s;
	int min = smallest->value;
	*s = smallest->right;
	delete smallest;
	curSize--;
	return min;
}

int MyPDeque::dequeueMax() {
	if (isEmpty()) return -1;
	Node** b = findBiggest();
	Node* biggest = *b;
	int max = biggest->value;
	*b = biggest->left;
	delete biggest;
	curSize--;
	return max;
}

MyPDeque::Node** MyPDeque::findSmallest() {
	Node** s = &root;
	while ((*s)->left != NULL)
		s = &(*s)->left;
	return s;
}

MyPDeque::Node** MyPDeque::findBiggest() {
	Node** b = &root;
	while ((*b)->right != NULL)
		b = &(*b)->right;
	return b;
}
