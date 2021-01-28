
#ifndef MY_INTEGER_LEXICON_
#define MY_INTEGER_LEXICON_

#include <string>
using namespace std;

class MyIntegerLexicon {

	public:

		MyIntegerLexicon();
		~MyIntegerLexicon();
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
