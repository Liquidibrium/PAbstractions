
#ifndef MY_PQUEUE_H_
#define MY_PQUEUE_H_

#define START_ALOCATED_SIZE 1

class MyPQueue {

	public:

		MyPQueue();
		~MyPQueue();
		int size();
		bool isEmpty();
		void enqueue(int value);
		int peek();
		int dequeueMin();

	private:

		int* data;
		int logSize;
		int alocSize;

		void checkAlocSize();
		void swap(int i, int j);
		int getLessSonIndex(int parent);

};

#endif
