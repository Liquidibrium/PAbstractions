
#ifndef MY_PQUEUE__H_
#define MY_PQUEUE__H_

class MyPQueue_ {

	public:

		MyPQueue_();
		~MyPQueue_();

		int size();
		bool isEmpty();

		void enqueue(int value);

		int peekMin();
		int peekMax();

		int dequeueMin();
		int dequeueMax();

	private:

		struct Node {
			Node* prev;
			Node* next;
			int value;
		};

		Node* head;
		Node* tail;

		int curSize;

};

#endif
