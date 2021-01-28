
#ifndef MY_PRIORITY_DEQUE_H_
#define MY_PRIORITY_DEQUE_H_

class MyPDeque {

	public:

		MyPDeque();
		~MyPDeque();
		int size();
		bool isEmpty();
		void enqueue(int value);
		int peekMin();
		int peekMax();
		int dequeueMin();
		int dequeueMax();

	private:

		struct Node {
			Node* left;
			Node* right;
			int value;
		};

		Node* root;

		int curSize;

		void freeTree(Node* r);

		Node** findNode(int value);
		Node** recFindNode(Node** ptr, int value);

		Node** findSmallest();
		Node** findBiggest();

};

#endif
