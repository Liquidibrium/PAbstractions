
#include "MyLexicon.h"
#include "error.h"

MyLexicon::MyLexicon() {
	root = NULL;
}

MyLexicon::~MyLexicon() {
	freeTree(root);
}

void MyLexicon::freeTree(Node* r) {
	if (r == NULL) return;
	for (int i = 0; i < 26; i++)
		freeTree(r->children[i]);
	delete r;
}

bool MyLexicon::isEmpty() {
	return root == NULL;
}

int MyLexicon::countWords(Node* r) {
	if (r == NULL) return 0;
	int result = 0;
	if (r->isWord) result++;
	for (int i = 0; i < 26; i++)
		result += countWords(r->children[i]);
	return result;
}

int MyLexicon::size() {
	return countWords(root);
}

void MyLexicon::recAddWord(Node*& node, int index, string &word) {
	if (node == NULL) {
		node = new Node;
		node->isWord = false;
		for (int i = 0; i < 26; i++)
			node->children[i] = NULL;
	}
	if (index == word.length())
		node->isWord = true;
	else 
		recAddWord(node->children[word[index] - 'a'], index + 1, word);
}

void MyLexicon::addWord(string word) {
	recAddWord(root, 0, word);
}

MyLexicon::Node* MyLexicon::recFindNode(Node* node, int index, string &word) {
	if (index == word.length()) return node;
	if (node == NULL) return NULL;
	return recFindNode(node->children[word[index] - 'a'], index + 1, word);
}

MyLexicon::Node* MyLexicon::findNode(string &word) {
	return recFindNode(root, 0, word);
}

bool MyLexicon::containsWord(string word) {
	Node* node = findNode(word);
	return node != NULL && node->isWord;
}

bool MyLexicon::containsPrefix(string pref) {
	return findNode(pref) != NULL;
}

void MyLexicon::recRemoveWord(Node*& node, int index, string &word) {
	if (node == NULL) return;

	if (index == word.size())
		node->isWord = false;
	else
		recRemoveWord(node->children[word[index] - 'a'], index + 1, word);
	
	for (int i = 0; i < 26; i++)
		if (node->children[i] != NULL) return;

	if (!node->isWord) {
		delete node;
		node = NULL;
	}
}

void MyLexicon::removeWord(string word) {
	recRemoveWord(root, 0, word);
}
