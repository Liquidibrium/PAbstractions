#include "vector.h"

struct item {
	int price;
	int weight;
};
struct bag {
	int price;
	int cap;
};


int findBestComb(Vector<item> &items, Vector<bag> &bags, int money);
