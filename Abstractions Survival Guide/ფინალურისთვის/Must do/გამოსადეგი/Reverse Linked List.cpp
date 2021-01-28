#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Cell {
	string value;
	Cell* next;
};

void recReverseList(Cell* list) {
	if (list->next == NULL) return;
	recReverseList(list->next);
	list->next->next = list;
}

void reverseList(Cell*& list) {
	Cell* last = list;
	while (last->next != NULL)
		last = last->next;
	recReverseList(list);
	list->next = NULL;
	list = last;
}

void printList(Cell* list) {
	while (list != NULL) {
		cout << list->value;
		list = list->next;
	}
	cout << '\n';
}

int main() {
	Cell* a = new Cell;
	a->value = "a";

	Cell* b = new Cell;
	b->value = "b";

	Cell* c = new Cell;
	c->value = "c";

	Cell* d = new Cell;
	d->value = "d";

	Cell* e = new Cell;
	e->value = "e";

	Cell* list = a;
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = NULL;

	printList(list);
	reverseList(list);
	printList(list);

	delete a;
	delete b;
	delete c;
	delete d;
	delete e;

	return 0;
}