#include "parent.h"
#include "strlib.h"

bool contains (Node* root, Node* a) {
	if (root == NULL) return false;
	return root == a || contains(root->left, a) || contains(root->right, a);
}

Node* getParent(Node* root, Node* a, Node* b) {
	if (root == NULL) return root;
	if (contains(root->left, a) && contains(root->left, b)) return getParent(root->left, a, b);
	if (contains(root->right, a) && contains(root->right, b)) return getParent(root->right, a, b);
	return root;
}

//Node* getParent(Node* root, Node* a, Node* b) {
//	Node* result = new Node;
//	bool x = bla(root, a, b, result);
//	return result;
//}
//
//bool bla(Node* node, Node* a, Node* b, Node* &result){
//	if(node == NULL) return false;
//
//	bool left = bla(node->left, a, b, result);
//	bool right = bla(node->right, a, b, result);
//
//		if(!left && !right){
//			result = node;
//			return true;
//		}
//
//		return false;
//}