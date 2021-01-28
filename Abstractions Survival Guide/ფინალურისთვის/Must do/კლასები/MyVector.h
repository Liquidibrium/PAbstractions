
#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#define START_ALOCATED_SIZE 50

class MyVector {

	public:
		
		MyVector();
		~MyVector();
		void add(int value);
		int get(int index);
		void insert(int index, int value);
		void remove(int index);
		int size();
		bool isEmpty();
		void clear();

	private:
		
		int logSize;
		int alocSize;
		int* data;

		void checkAlocSize();

};

#endif