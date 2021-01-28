#ifndef COMMON_INCL
#define COMMON_INCL
#include <string>
struct Node {
	int id;
	Node * left;
	Node * right;
};

struct Arc {
	int dist;
	int from;
	int to;
};

#endif