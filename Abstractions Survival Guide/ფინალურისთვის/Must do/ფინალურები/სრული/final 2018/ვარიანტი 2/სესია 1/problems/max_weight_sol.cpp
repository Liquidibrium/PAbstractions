#include "max_weight_sol.h"


bool canWeigh(Vector<int> &items, int weight, int indx) {
	if (weight == 0) {
		return true;
	}

	if (indx >= items.size()) {
		return false;
	}

	return	canWeigh(items, weight, indx+1) || 
			canWeigh(items, weight+items[indx], indx+1) || 
			canWeigh(items, weight-items[indx], indx+1);
}

int maxWeightSol(Vector<int> &weights, Vector<int> &items) {
	int max = 0;
	for (int i=0; i<items.size(); i++) {
		for (int j=i+1; j<items.size(); j++) {
			bool can1 = canWeigh(weights, items[i], 0);
			bool can2 = canWeigh(weights, items[j], 0);
			if (!can1 && !can2) {//2,3,4,5,6,8;
				continue;
			}

			if (!can1) {
				weights += items[j];
				can1 = canWeigh(weights, items[i], 0);
				weights.remove(weights.size()-1);
			} else if (!can2) {			
				weights += items[i];
				can2 = canWeigh(weights, items[j], 0);
				weights.remove(weights.size()-1);
			}
			if (!can1 || !can2) {
				continue;
			}
			if (max < items[i] + items[j]) {
				max = items[i] + items[j];
			}
		}
	}
	return max;
}