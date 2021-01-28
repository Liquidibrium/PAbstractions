#ifndef TreeWidth_Included
#define TreeWidth_Included

#include "console.h"
using namespace std;

struct TreeNode {
	int v;//node value
	int weight;//ignore this field
	TreeNode * left;
	TreeNode * right;
};

int treeMaxWidth (TreeNode * root);

#endif;
