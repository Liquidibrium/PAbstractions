#include <string>
#include "vector.h"

using namespace std;
struct nodeT {
	int v;
	int weight;//ignore this field!!
	nodeT * left;
	nodeT * right;
};

Vector<nodeT *> leftView(nodeT * root);