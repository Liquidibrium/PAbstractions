
#ifndef MY_RESIZABLE_ARRAY_H_
#define MY_RESIZABLE_ARRAY_H_

class MyResizableArray
{
	public:

		MyResizableArray(int size = 10);
		~MyResizableArray();
		void resize(int newSize);
		double getAt(int index);
		void setAt(int index, double value);
		int size();	private:				double* data;		int curSize;
};

#endif

