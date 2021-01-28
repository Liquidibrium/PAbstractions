
#include <iostream>
#include <string>
using namespace std;

struct Node {
	string key;
	Node *left, *right;
};

Node* findSubstitute (Node* n, Node**& pointer_to_subs) {
	Node* res = n->left;
	while (res->right != NULL) {
		pointer_to_subs = &res->right;
		res = res->right;
	}
	return res;
}

Node* findNode (string &key, Node* tree, Node**& pointer) {
	if (key == tree->key) return tree;
	if (key < tree->key) {
		pointer = &tree->left;
		return findNode (key, tree->left, pointer);
	} else {
		pointer = &tree->right;
		return findNode (key, tree->right, pointer);
	}
}

void removeNodeBST(Node*& tree, string key) {
	Node** pointer = &tree;
	Node* n = findNode (key, tree, pointer);
	if (n->left == NULL && n->right == NULL) {
		*pointer = NULL;
	} else if (n->left != NULL && n->right == NULL) {
		*pointer = n->left;
	} else if (n->left == NULL && n->right != NULL) {
		*pointer = n->right;
	} else {
		Node** pointer_to_subs = &n->left;
		Node* subs = findSubstitute (n, pointer_to_subs);

		*pointer_to_subs = subs->left;

		subs->left = n->left;
		subs->right = n->right;

		*pointer = subs;
	}
	delete n;
}

void printTree(Node* t) {
	if (t != NULL) {
		printTree(t->left);
		cout << t->key << endl;
		printTree(t->right);
	}
}

int main() {
	Node* grumpy = new Node;
	grumpy->key = "Grumpy";
	Node* doc = new Node;
	doc->key = "Doc";
	Node* sleepy = new Node;
	sleepy->key = "Sleepy";
	Node* bashful = new Node;
	bashful->key = "Bashful";
	Node* dopey = new Node;
	dopey->key = "Dopey";
	Node* happy = new Node;
	happy->key = "Happy";
	Node* sneezy = new Node;
	sneezy->key = "Sneezy";

	grumpy->left = doc;
	grumpy->right = sleepy;

	doc->left = bashful;
	doc->right = dopey;

	sleepy->left = happy;
	sleepy->right = sneezy;

	bashful->left = NULL;
	bashful->right = NULL;

	dopey->left = NULL;
	dopey->right = NULL;

	happy->left = NULL;
	happy->right = NULL;

	sneezy->left = NULL;
	sneezy->right = NULL;

	Node* t = grumpy;

	printTree(t);
	cout << '\n';

	removeNodeBST(t, "Sneezy");

	printTree(t);
	cout << '\n';

	removeNodeBST(t, "Sleepy");
	
	printTree(t);
	cout << '\n';

	removeNodeBST(t, "Grumpy");
	
	printTree(t);
	cout << '\n';

	return 0;
}