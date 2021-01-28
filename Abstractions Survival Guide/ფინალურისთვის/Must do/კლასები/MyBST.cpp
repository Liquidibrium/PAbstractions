
#include "MyBST.h"
#include "error.h"

MyBST::MyBST() {
	root = NULL;
	curSize = 0;
}

void MyBST::freeTree(Node* r) {
	if (r == NULL) return;
	freeTree(r->left);
	freeTree(r->right);
	delete r;
}

MyBST::~MyBST() {
	freeTree(root);
}

void MyBST::add(int value) {

	Node* new_node = new Node;
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;

	Node** pointer = &root;
	Node* node = findNode(value, root, pointer);

	while (node != NULL) {
		if (node->value == value) {
			pointer = &node->right;
			node = node->right;
		} else {
			pointer = &node->left;
			node = node->left;
		}
	}

	*pointer = new_node;
	curSize++;
}

bool MyBST::contains(int value) {
	Node** pointer = &root;
	Node* node = findNode(value, root, pointer);
	return node != NULL;
}

bool MyBST::equals(Node* r1, Node* r2) {
	if (r1 == NULL && r2 == NULL) return true;
	if (r1 == NULL || r2 == NULL) return false;
	if (r1->value != r2->value) return false;
	return equals(r1->left, r2->left)
		 && equals(r1->right, r2->right);
}

bool MyBST::recIsSubtreeOf(Node* r) {
	if (r == NULL) return false;
	if (equals(root, r)) return true;
	if (root->value > r->value) return recIsSubtreeOf(r->right);
	return recIsSubtreeOf(r->left);
}

bool MyBST::isSubtreeOf(MyBST& other) {
	return recIsSubtreeOf(other.root);
}

void MyBST::remove(int value) {
	Node** pointer = &root;
	Node* node = findNode(value, root, pointer);
	if (node == NULL) return;
	if (node->left == NULL && node->right == NULL) {
		*pointer = NULL;
	} else if (node->left == NULL && node->right != NULL) {
		*pointer = node->right;
	} else if (node->left != NULL && node->right == NULL) {
		*pointer = node->left;
	} else {
		Node** ptr = &node->left;
		Node* subs = findSubstitute(node, ptr);
		*ptr = subs->left;
		*pointer = subs;
		subs->left = node->left;
		subs->right = node->right;
	}
	delete node;
	curSize--;
}

int MyBST::smallest() {
	if (isEmpty()) return -1;
	Node* s = root;
	while (s->left != NULL)
		s = s->left;
	return s->value;
}

bool MyBST::isEmpty() {
	return size() == 0;
}

int MyBST::size() {
	return curSize;
}

MyBST::Node* MyBST::findNode(int value, Node* r, Node**& pointer) {
	if (r == NULL) return NULL;
	if (value == r->value) return r;
	if (value < r->value) {
		pointer = &r->left;
		return findNode(value, r->left, pointer);
	} else {
		pointer = &r->right;
		return findNode(value, r->right, pointer);
	}
}

MyBST::Node* MyBST::findSubstitute(Node* r, Node**& pointer) {
	Node* subs = r->left;
	while (subs->right != NULL) {
		pointer = &subs->right;
		subs = subs->right;
	}
	return subs;
}
