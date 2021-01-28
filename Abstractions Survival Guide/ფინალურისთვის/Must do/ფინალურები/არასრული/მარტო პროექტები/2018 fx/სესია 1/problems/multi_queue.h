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

};