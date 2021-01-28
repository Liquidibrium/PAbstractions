#ifndef _flattenlist_
#define _flattenlist_

#include "console.h"
#include "grid.h"
using namespace std;

struct ListNode {
	int value;
	ListNode* down;
	ListNode* next;
};


ListNode * flattenList(ListNode * head);

#endif