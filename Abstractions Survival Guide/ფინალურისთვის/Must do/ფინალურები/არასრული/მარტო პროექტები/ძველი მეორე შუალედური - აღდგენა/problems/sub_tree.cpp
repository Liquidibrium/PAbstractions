#include "sub_tree.h"




int maxSubTree(Node * r1, Node * r2) {
	if(contains(r1, r2)) {
		int sum = 0;
		size(r2, sum);
		return sum;
	}
	int left = maxSubTree(r1, r2->left);
	int right =  maxSubTree(r1, r2->right);
	if( left > right) {
		return left;
	} else {
		return right;
	}
}