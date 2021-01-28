
#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <string>
using namespace std;

class MyString {

	public:

		MyString(string other = "");
		MyString(MyString& other);
		~MyString();
		string toString();
		MyString concat(MyString& other);

	private:
		
		struct Node {
			char ch;
			Node* next;
		};

		Node* head;

		Node* copyOther(MyString& other);

};

#endif
