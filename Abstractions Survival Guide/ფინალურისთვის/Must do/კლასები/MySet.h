
#ifndef MY_SET_H_
#define MY_SET_H_

#include "error.h"

class MySet
{
	public:

		MySet ();
		~MySet ();
		void add (int key);
		void remove (int key);
		bool contains (int key);
		int first ();
		bool isEmpty ();
		int size ();
		void printSet();

	private:

		struct Node {
			int key;
			Node *left, *right;
		};

		Node* root;

		int curSize;
		
		void freeTree (Node* r);

		Node*& findNode (int key);
		Node*& recFindNode (Node*& r, int key);

		Node*& findSubstitute (Node* node);

		void recPrintSet(Node* root);

};

#endif
