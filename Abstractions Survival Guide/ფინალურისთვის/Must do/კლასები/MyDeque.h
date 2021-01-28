
#ifndef MY_DEQUE_H_
#define MY_DEQUE_H_

class MyDeque {

	public:

		MyDeque();
		~MyDeque();

		bool isEmpty();

		void pushFront(int value);
		void pushBack(int value);

		int popFront();
		int popBack();

	private:

		struct Node {
			int value;
			Node* next;
			Node* prev;
		};

		Node* head;
		Node* tail;

		int curSize;

};

#endif