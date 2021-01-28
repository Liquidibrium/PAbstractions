
#ifndef MY_LEXICON_H_
#define MY_LEXICON_H_

#include <string>
using namespace std;

class MyLexicon {

	public:

		MyLexicon();
		~MyLexicon();
		bool isEmpty();
		int size();
		void addWord(string word);
		bool containsWord(string word);
		bool containsPrefix(string pref);
		void removeWord(string word);

	private:

		struct Node {
			bool isWord;
			Node* children[26];
		};

		Node* root;

		Node* findNode(string &word);
		Node* recFindNode(Node* node, int index, string &word);

		void recAddWord(Node*& node, int index, string &word);
		
		void recRemoveWord(Node*& node, int index, string &word);

		int countWords(Node* r);

		void freeTree(Node* r);

};

#endif
