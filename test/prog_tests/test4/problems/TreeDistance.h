#ifndef Distance_Included
#define Distance_Included


#include "Set.h"

struct Node {
	int value;
	Node * left, *right;
};

Set<int> kDistance(Node * root, int k); 


#endif;