
#ifndef MY_STACK__H_
#define MY_STACK__H_

#define START_ALOCATED_SIZE_ 7

class MyStack_ {

	public:

		MyStack_();
		~MyStack_();
		void clear();
		bool isEmpty();
		int peek();
		int pop();
		void push(int value);
		int size();

	private:

		int logSize;
		int alocSize;
		int* data;

		void checkAlocSize();

};

#endif
