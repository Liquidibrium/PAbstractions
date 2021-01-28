#include "circle.h"
#include <iostream>
#include "error.h"

Circle::Circle() {
	zoma = 0;
	head = NULL;
}
Circle::~Circle() {
	Node* cur = head;
	for (int i = 0; i < zoma; i++) {
		Node* tmp = cur->next;
		delete cur;
		cur = tmp;
	}
}

int Circle::length() {
	return zoma;
}
void Circle::insert(int pos, int v) {
	zoma++;
	Node* axali = new Node;
	axali->val = v;

	if(head == NULL && pos == 0) {
		head = axali;
		head->next = head;
		return;
	} else if(head == NULL && pos != 0) {
		zoma--;
		error ("aasdf");
	}

	Node* temp = head;

	if( pos == 0 ) {
		Node* bolo = head;
		for(int i = 0; i < zoma - 2; i++) {
			bolo = bolo->next;
		}
		bolo->next = axali;
		axali->next = head;
		head = axali;
		return;
	}
	
	for(int i = 0; i <pos - 1; i++) {
		temp = temp->next;
	}
	axali->next = temp->next;
	temp->next = axali;
	
}

int Circle::get(int pos) {
	if(pos < 0) error("adsasd");
	Node* temp = head;
	for( int i =0; i < pos; i++) {
		temp = temp->next;
	}
	return temp->val;
}

void Circle::set(int pos, int v) {
	if(pos < 0) error("adsasd");
	Node* temp = head;
	for( int i =0; i < pos; i++) {
		temp = temp->next;
	}
	temp->val = v;
}

Circle * Circle::subCircle(int start, int end) {

	Circle* axali = new Circle();
	Node* dawkeba = head;

	for( int i = 0; i < start; i++) {
		dawkeba = dawkeba->next;
	}

	if( end < start ) end += zoma;
	if( start != end )
	axali->insert(0, dawkeba->val);
	for( int i = 0; i< end - start -1; i++ ){
		axali->insert(i+1, dawkeba->next->val);
		dawkeba = dawkeba->next;
	}

	return axali;
}

int Circle::contains(Circle * c){
	
	for( int i = 0; i < this->length(); i++) {
		for( int j  = 0; j < c->length(); j++) {
			if(this->get(i+j) != c->get(j)) break;
			if(j == c->length() - 1) return i;
		}
	}
	
	return -1;
}


