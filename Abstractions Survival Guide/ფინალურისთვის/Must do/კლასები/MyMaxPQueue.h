
#ifndef MY_MAX_PQUEUE_H_
#define MY_MAX_PQUEUE_H_

#define START_ALOCATED_SIZE_ 1

class MyMaxPQueue {

	public:

		MyMaxPQueue();
		~MyMaxPQueue();
		int size();
		bool isEmpty();
		void enqueue(int value);
		int peek();
		int dequeueMax();

	private:

		int* data;
		int alocSize;
		int logSize;

		void checkAlocSize();
		int getBiggestSon(int parent);
		void swap(int i, int j);

};

#endif
