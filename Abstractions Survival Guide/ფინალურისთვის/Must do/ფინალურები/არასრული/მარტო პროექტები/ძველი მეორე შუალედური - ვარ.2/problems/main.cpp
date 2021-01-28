#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "parent.h"
#include "circle.h"
#include <time.h>
#include "lexicon.h"
#include "random.h"



using namespace std;

void printTestResults(bool passed, int & testNum, int & passedCounter) {
	testNum++;
	if (passed) {
		passedCounter++;
		cout << "test " << testNum << " passed, total passed tests: " << passedCounter << endl;
	} else {
		cout << "test " << testNum << " failed, total passed tests: " << passedCounter << endl;
	}
}

Node * find(Node * root, int v) {
	if (root == NULL) {
		return NULL;
	}
	if (root->v == v) {
		return root;
	}
	if (root->v < v) {
		return find(root->right, v);
	} else {
		return find(root->left, v);
	}
}

void insertIntoTree(Node * &root, int v) {
	if (root == NULL) {
		root = new Node;
		root->left = NULL;
		root->right = NULL;
		root->v = v;
		return;
	}
	if (root->v < v) {
		insertIntoTree(root->right, v);
	} else {
		insertIntoTree(root->left, v);
	}
}

Node* buildTree(Vector<int> &v) {
	Node * root = NULL;
	for (int i=0; i<v.size(); i++) {
		insertIntoTree(root, v[i]);
	}
	return root;
}

Node * insertNode(Node * &root, int value, int weight) {
	if (root == NULL) {
		root = new Node;
		root->v = value;
		root->weight = weight;
		root->left = NULL;
		root->right = NULL;
		return root;
	}

	if (root->weight < weight) {
		return insertNode(root->right, value, weight);
	} else {
		return insertNode(root->left, value, weight);
	}
}

Node * randomBT(bool bst, Node * &e1, Node * &e2) {
	Node * r = NULL;
	int n = randomInteger(100, 1000);
	int v, w;
	Set<int> weights;
	Vector<Node *> elems;
	for (int i=0; i<n; i++) {
		v = randomInteger(0, 1000);
		w = randomInteger(0, 1000);
		if (bst) {
			w = v;
		}
		if (weights.contains(w)) {
			continue;
		}
		Node * e = insertNode(r, v, w);
		elems.add(e);
	}
	e1 = elems[randomInteger(0, elems.size()-1)];
	e2 = e1;
	while (e2 == e1) {
		e2 = elems[randomInteger(0, elems.size()-1)];
	}
	return r;
}

void runParentTests() {
	cout << "### Run Parent tests ###" << endl;
	int testNum = 0;
	int passedCounter = 0;
	Node * res;
	Node * root = NULL;
	Vector<int> v;
	//#1
	v.clear();
	v += 1, 2;
	root = buildTree(v);
	res = getParent(root, root, root->right);
	printTestResults(res == root, testNum, passedCounter);
	//#2
	v.clear();
	v += 2, 1, 3;
	root = buildTree(v);
	res = getParent(root, root->left, root->right);
	printTestResults(res == root, testNum, passedCounter);
	//#3
	v.clear();
	v += 3, 1, 2, 4, 5;
	root = buildTree(v);
	res = getParent(root, root->left->right, root->left);
	printTestResults(res == root->left, testNum, passedCounter);
	//#4
	v.clear();
	v += 10, 1, 2, 9, 14, 15;
	root = buildTree(v);
	res = getParent(root, root->left->right, root->right->right);
	printTestResults(res == root, testNum, passedCounter);
	//#5
	v.clear();
	v += 10, 5, 18, 16, 15, 12, 20, 19;
	root = buildTree(v);
	res = getParent(root, root->right->left->left, root->right->right->left);
	printTestResults(res == root->right, testNum, passedCounter);
	//#6
	v.clear();
	v += 20, 5, 1, 10, 30, 25, 40, 36, 35, 34, 33, 41, 42, 43;
	root = buildTree(v);
	res = getParent(root, root->right->right->right->right, 
			root->right->right->left->left);
	printTestResults(res == root->right->right, testNum, passedCounter);
	//#7
	v.clear();
	v += 20, 5, 1, 10, 30, 25, 40, 36, 35, 34, 33, 41, 42, 43;
	root = buildTree(v);
	res = getParent(root, root->right->right->right->right, 
			root->right);
	printTestResults(res == root->right, testNum, passedCounter);
	//#8
	v.clear();
	v += 30, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5;
	root = buildTree(v);
	res = getParent(root, find(root, 8), find(root, 11));
	printTestResults(res == find(root, 10), testNum, passedCounter);
	//#9
	v.clear();
	v += 30, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5, 55, 60, 57;
	root = buildTree(v);
	res = getParent(root, find(root, 1), find(root, 18));
	printTestResults(res == find(root, 1), testNum, passedCounter);
	//#10
	v.clear();
	v += 34, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5, 30, 31, 32, 33;
	root = buildTree(v);
	res = getParent(root, find(root, 32), find(root, 5));
	printTestResults(res == find(root, 25), testNum, passedCounter);
	//#11
	v.clear();
	v += 34, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5, 30, 31, 32, 33, 3;
	root = buildTree(v);
	res = getParent(root, find(root, 20), find(root, 32));
	printTestResults(res == find(root, 25), testNum, passedCounter);
	//#12
	v.clear();
	v += 34, 50, 1, 25, 27, 29, 4, 14, 15, 16, 17, 18, 19, 20, 10, 12, 11, 9, 8, 7, 6, 5, 30, 31, 32, 33, 3;
	root = buildTree(v);
	res = getParent(root, find(root, 3), find(root, 11));
	printTestResults(res == find(root, 4), testNum, passedCounter);

	//ofstream o;
	//o.open("1.txt");
	Node * e1;
	Node * e2;
	int answ[90] = {535, 172, 841, 538, 440, 507, 787, 541, 713, 84, 103, 318, 989, 497, 697, 531, 385, 677, 454, 629, 638, 506, 867, 304, 628, 194, 620, 517, 490, 573, 208, 774, 803, 101, 342, 488, 629, 143, 747, 533, 434, 185, 221, 198, 402, 716, 463, 272, 348, 389, 155, 578, 217, 195, 323, 489, 170, 678, 141, 688, 380, 692, 17, 377, 591, 325, 351, 194, 417, 596, 529, 927, 534, 650, 228, 410, 869, 795, 396, 925, 537, 483, 752, 412, 512, 882, 306, 697, 714, 406};
	for (int i=0; i<90; i++) {
		root = randomBT(i<40, e1, e2);
		res = getParent(root, e1, e2);
		//o << res->weight << ", ";
		printTestResults(res != NULL && res->weight == answ[i], testNum, passedCounter);
	}
	//o.close();

	cout << "###### passed " << passedCounter << " tests ######" << endl;
}

bool equalsCircle(string s, Circle *c) {
	if (c == NULL) {
		return false;
	}
	if (s.length() != c->length()) {
		return false;
	}
	for (int i=0; i<2*c->length(); i++) {
		if (s[i%s.length()]-'0' != c->get(i)) {
			return false;
		}
	}
	return true;
}

Circle* initCircle(string s) {
	Circle* c = new Circle;
	for (int i=0; i<s.length(); i++) {
		c->insert(i, s[i]-'0');
	}
	return c;
}

void randomLengthInsertGetTest(Circle * &s, string &res) {
	s = new Circle;
	res = "";
	int len = randomInteger(10, 10);
	for (int i=0; i<len; i++) {
		size_t pos = randomInteger(0, s->length());
		int v = randomInteger(0, 9);
		s->insert(pos, v);
		res.insert(pos, integerToString(v));
	}
}

void randomSetTest(Circle * &s, string &res) {
	int len = randomInteger(s->length()/2, s->length());
	for (int i=0; i<len; i++) {
		size_t pos = randomInteger(0, 2*s->length());
		int v = randomInteger(0, 9);
		s->set(pos, v);
		res[pos%res.length()] = '0' + v;
	}
}

Circle * randomSubstrTest(Circle * &s, string &res) {
	int start = randomInteger(0, s->length()-2);
	int end = randomInteger(start+1, s->length());
	res = res.substr(start, end-start);
	return s->subCircle(start, end);
}

bool randomFindTestPassed(Circle * &s, string &res) {
	int start = randomInteger(0, s->length()-2);
	int end = randomInteger(start+1, s->length());
	string substr = res.substr(start, end-start);
	return res.find(substr) == s->contains(initCircle(substr));
}
void runCircleTests() {
	cout << "### Run Circle tests ###" << endl;
	int testNum = 0;
	int passedCounter = 0;
	Circle * s;
	bool passed;
	//#1
	s = new Circle;
	printTestResults(s->length() == 0, testNum, passedCounter);
	//#2
	s = new Circle;
	s->insert(0, 3);
	passed = s->length() == 1 && s->get(0) == 3 && s->get(5) == 3;
	printTestResults(passed, testNum, passedCounter);
	//#3
	s = new Circle;
	s->insert(0, 2);
	s->insert(0, 1);
	s->insert(2, 3);
	passed = s->length() == 3 && equalsCircle("123", s) &&
			s->get(4) == 2 && s->get(8) == 3 && s->get(12) == 1;
	printTestResults(passed, testNum, passedCounter);
	//#4
	s = new Circle;
	s->insert(0, 2);
	s->insert(0, 1);
	s->insert(2, 3);
	s->insert(1, 1);
	s->insert(2, 2);
	passed = s->length() == 5 && equalsCircle("11223", s) && 
		s->get(27) == s->get(47) && s->get(27) == 2;
	printTestResults(passed, testNum, passedCounter);
	//#5
	s = new Circle;
	s->insert(0, 2);
	s->insert(0, 1);
	s->insert(2, 3);
	s->insert(1, 3);
	s->insert(2, 4);
	s->set(0, 9);
	passed = s->length() == 5 && equalsCircle("93423", s);
	printTestResults(passed, testNum, passedCounter);
	//#6
	s = new Circle;
	s->insert(0, 1);
	s->insert(1, 3);
	s->insert(1, 3);
	s->insert(2, 4);
	s->set(s->length(), 9);
	s->set(7, 9);

	passed = s->length() == 4 && equalsCircle("9349", s);
	printTestResults(passed, testNum, passedCounter);
	//#7
	s = new Circle;
	s->insert(0, 1);
	s->insert(1, 3);
	s->insert(1, 3);
	s->insert(2, 4);
	s->set(8, 9);
	s->insert(0, 1);
	s->set(19, 9);
	s->insert(s->length(), 8);
	passed = s->length() == 6 && equalsCircle("193498", s);
	printTestResults(passed, testNum, passedCounter);
	//#8
	s = new Circle;
	s->insert(0, 1);
	s = s->subCircle(0, 1);
	passed = equalsCircle("1", s);
	printTestResults(passed, testNum, passedCounter);
	//#9
	s = new Circle;
	s->insert(0, 1);
	s = s->subCircle(0, 0);
	passed = equalsCircle("", s);
	printTestResults(passed, testNum, passedCounter);
	//#10
	s = new Circle;
	s->insert(0, 1);
	s->insert(1, 2);
	s->insert(2, 3);
	s->insert(3, 4);
	s->insert(4, 5);
	s = s->subCircle(3, 5);
	passed = equalsCircle("45", s);
	printTestResults(passed, testNum, passedCounter);
	//#11
	s = new Circle;
	s->insert(0, 1);
	s->insert(1, 2);
	s->insert(2, 3);
	s->insert(3, 4);
	s->insert(4, 5);
	s = s->subCircle(0, s->length());
	passed = equalsCircle("12345", s);
	printTestResults(passed, testNum, passedCounter);
	//#12
	s = initCircle("12345");
	s = s->subCircle(0, s->length());
	passed = equalsCircle("12345", s);
	printTestResults(passed, testNum, passedCounter);
	//#13
	s = new Circle;
	s = initCircle("12345");
	passed = s->contains(initCircle("abcdef")) == -1;
	printTestResults(passed, testNum, passedCounter);
	//#14
	s = new Circle;
	s = initCircle("12345");
	passed = s->contains(initCircle("12345")) == 0;
	printTestResults(passed, testNum, passedCounter);
	//#15
	s = initCircle("12345");
	passed = s->contains(initCircle("45")) == 3;
	printTestResults(passed, testNum, passedCounter);
	//#16
	s = initCircle("12345");
	passed = s->contains(initCircle("1233")) == -1;
	printTestResults(passed, testNum, passedCounter);

	int num = 84;
	string res;
	//insert, get, length
	for (int i=0; i<num*0.5; i++) {
		randomLengthInsertGetTest(s, res);
		printTestResults(equalsCircle(res, s), testNum, passedCounter);
	}
	//set
	for (int i=0; i<num*0.1; i++) {
		randomLengthInsertGetTest(s, res);
		randomSetTest(s, res);
		printTestResults(equalsCircle(res, s), testNum, passedCounter);
	}
	//substr
	for (int i=0; i<num*0.2; i++) {
		randomLengthInsertGetTest(s, res);
		printTestResults(equalsCircle(res, randomSubstrTest(s, res)), testNum, passedCounter);
	}
	//find
	for (int i=0; i<num*0.2; i++) {
		randomLengthInsertGetTest(s, res);
		printTestResults(randomFindTestPassed(s, res), testNum, passedCounter);
	}
	cout << "###### passed " << passedCounter << " tests ######" << endl;
}


int main() {
	setRandomSeed(0);
//	runParentTests();
	runCircleTests();
	return 0;
}