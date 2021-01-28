
#ifndef MY_BITSICON_H_
#define MY_BITSICON_H_

#include <string>
using namespace std;

class MyBitsicon {

	public:

		MyBitsicon();
		~MyBitsicon();
		bool isEmpty();
		int size();
		void addNumber(string n);
		bool containsNumber(string n);
		bool containsPrefix(string pref);
		void removeNumber(string n);

	private:

		struct Node {
			bool isNumber;
			Node* neighbors[2];
		};

		Node* root;

		int curSize;

		void freeTree(Node* r);

		Node* findNode(string &n);
		Node* recFindNode(int index, string &n, Node* r);

		void recAddNumber(int index, string &n, Node* &r);

		void recRemoveNumber(int index, string &n, Node* &r);

};

#endif
