#include "simpio.h"


class MultiQueue {
	public:
		MultiQueue();
		void addQueue();
		int size(int qPos);
		int numQueues();
		void enqueue(int qPos, int v);
		int dequeue(int qPos);
		void removeQueue(int qPos);

	private:
		struct Node {
			int v;
			Node * next;
		};
		struct Queue {
			int size;
			Node * list;
			Node * tail;
		};
		Queue * queues;
		int logLen;
		int allocLen;
		void doubleSpace();
};