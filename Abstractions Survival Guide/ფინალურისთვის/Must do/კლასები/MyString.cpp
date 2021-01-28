#include "MyString.h"

MyString::MyString(string other) {
	head = NULL;
	for (int i = other.length() - 1; i >= 0; i--) {
		Node* tmp = new Node;
		tmp->ch = other[i];
		tmp->next = head;
		head = tmp;
	}
}

MyString::MyString(MyString& other) {
	head = copyOther(other);
}

MyString::~MyString() {
	while (head != NULL) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
}

string MyString::toString() {
	string result = "";
	for (Node* cur = head; cur != NULL; cur = cur->next)
		result += cur->ch;
	return result;
}

MyString MyString::concat(MyString& other) {
	return MyString(toString() + other.toString());
}

MyString::Node* MyString::copyOther(MyString& other) {
	Node* others_head = NULL;
	Node* tail = NULL;
	Node* cur = other.head;
	while (cur != NULL) {
		Node* tmp = new Node;
		tmp->ch = cur->ch;
		tmp->next = NULL;
		if (others_head == NULL) others_head = tmp;
		else tail->next = tmp;
		tail = tmp;
		cur = cur->next;
	}
	return others_head;
}
