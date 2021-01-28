
#ifndef MY_INT_LEXICON_H_
#define MY_INT_LEXICON_H_

#include <string>
using namespace std;

class MyIntLexicon {

	public:

		MyIntLexicon();
		~MyIntLexicon();
		bool isEmpty();
		int size();
		bool containsNumber(int n);
		void addNumber(int n);
		void removeNumber(int n);

	private:

		struct Node {
			bool isPositive;
			bool isNegative;
			Node* children[10];
		};

		Node* root;

		int curSize;

		void freeTree(Node* r);

		Node* findNode(int n);
		Node* recFindNode(Node* r, int i, string &n);

		void recAddNumber(Node*& r, int i, string &n, int number);

		void recRemoveNumber(Node*& r, int i, string &n, int number);

};

#endif
