
#ifndef MY_HASH_MAP_H_
#define MY_HASH_MAP_H_

class MyHashMap {
		
	public:
		
		MyHashMap();
		~MyHashMap();
		bool containsKey(int key);
		int get(int key);
		bool isEmpty();
		void put(int key, int value);
		void remove(int key);
		int size();
		
	private:
		
		struct Node {
			int key;
			int value;
			Node* next;
		};

		Node** arr;

		int curSize;
		int numBuckets;

		Node* findNode(int key);
		void rehash();	

};

#endif
