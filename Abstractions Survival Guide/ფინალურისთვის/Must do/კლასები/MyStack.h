
#ifndef MY_STACK_H_
#define MY_STACK_H_

class MyStack {

	public:

		MyStack();
		~MyStack();
		void clear();
		bool isEmpty();
		int peek();
		int pop();
		void push(int value);
		int size();

	private:

		struct Node {
			int value;
			Node* next;
		};

		Node* head;

		int curSize;

};

#endif
