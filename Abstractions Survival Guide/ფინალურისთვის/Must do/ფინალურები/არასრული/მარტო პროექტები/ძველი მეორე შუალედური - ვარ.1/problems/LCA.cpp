#include "LCA.h"
#include "strlib.h"

bool contains (Node* root, Node* a) {
	if (root == NULL) return false;
	return contains(root->left, a) || contains(root->right, a) || root == a;
}

Node* LCA(Node* root, Node* a, Node* b) {
	
}
