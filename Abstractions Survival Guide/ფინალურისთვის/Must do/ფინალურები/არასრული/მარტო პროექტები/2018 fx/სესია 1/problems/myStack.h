
#ifndef MYStack
#define MYStack

class myStack {
public:
	myStack();
	~myStack();
	void push(int value);
	int peek();
	bool isEmpty();
	int size();
	int pop();

private:
	int  numElements;
	int* elems;
	int  allocated;
	void grow();
};


#endif
