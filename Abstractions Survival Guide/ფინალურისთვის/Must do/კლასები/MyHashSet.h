
#ifndef MY_HASH_SET_H_
#define MY_HASH_SET_H_

class MyHashSet {

	public:

		MyHashSet();
		~MyHashSet();
		void add (int key);
		void remove (int key);
		bool contains (int key);
		bool isEmpty ();
		int size ();

	private:

		struct Node {
			int key;
			Node* next;
		};

		Node** data;
		int numBuckets;

		int curSize;

		Node* findNode(int key);
		void rehash();

};

#endif
