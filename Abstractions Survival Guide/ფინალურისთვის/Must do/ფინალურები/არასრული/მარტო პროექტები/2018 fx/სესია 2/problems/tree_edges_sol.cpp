#include "tree_edges.h"
#include "strlib.h"

void rec(Cell * root, int currPos, int &left, int &right, int &leftPos, int &rightPos) {
	if (root == NULL) {
		return;
	}
	if (currPos < leftPos) {
		leftPos = currPos;
		left = root->v;
	}
	if (currPos > rightPos) {
		rightPos = currPos;
		right = root->v;
	}

	rec(root->left, currPos-1, left, right, leftPos, rightPos);
	rec(root->right, currPos+1, left, right, leftPos, rightPos);
}

void getTreeEdges(Cell * root, int &left, int &right) {
	int currPos = 0;
	int leftPos = 0;
	int rightPos = 0;
	left = root->v;
	right = root->v;
	rec(root, currPos, left, right, leftPos, rightPos);
}