#ifndef Palindromic_Included
#define Palindromic_Included

#include "console.h"
using namespace std;

struct TreeNode {
	int v;
	int weight;
	TreeNode * left;
	TreeNode * right;
};

int pseudoPalindromicPaths (TreeNode * root);

#endif;
