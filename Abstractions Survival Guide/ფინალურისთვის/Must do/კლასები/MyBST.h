
#ifndef MY_BST_H_
#define MY_BST_H_

class MyBST {

	public:

		MyBST();
		~MyBST();

		void add(int value);
		bool contains(int value);

		void remove(int value);

		bool isSubtreeOf(MyBST& other);

		int smallest();
		bool isEmpty();
		int size();

	private:
		
		struct Node {
			int value;
			Node* left;
			Node* right;
		};

		Node* root;

		int curSize;

		Node* findNode(int value, Node* r, Node**& pointer);
		Node* findSubstitute(Node* r, Node**& pointer);
		bool recIsSubtreeOf(Node* r);
		bool equals(Node* r1, Node* r2);
		void freeTree(Node* r);

};

#endif