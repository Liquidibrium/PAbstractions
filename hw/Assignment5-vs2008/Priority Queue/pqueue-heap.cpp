/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include "iostream"

HeapPriorityQueue::HeapPriorityQueue() {
	actualSize = 0;
	arrSize =1;
	arr = new string[1];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] arr;
}

int HeapPriorityQueue::size() {
	return actualSize;
}

bool HeapPriorityQueue::isEmpty() {
	return actualSize==0;
}

void HeapPriorityQueue::enqueue(string value) {
	if(actualSize==arrSize){
		resize(arrSize*2+1);
	}
	arr[actualSize] = value;
	bubbleUp();
	actualSize++;
}
void HeapPriorityQueue::bubbleUp(){
	int n = actualSize;
	while(n>0 && (arr[(n+1)/2-1]).compare(arr[n])==1){
		swap(arr[n],arr[(n+1)/2-1]);
		n=(n+1)/2-1;
	}
}

string HeapPriorityQueue::peek() {
	if(isEmpty()) error(" fafu");
	return arr[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(isEmpty()) error(" fafu");
	swap(arr[0],arr[actualSize-1]);
	actualSize--;
	bubbleDown();
	//if (actualSize*4 < arrSize){
		//resize(arrSize/2);
	//}
	return arr[actualSize];
}

void HeapPriorityQueue::bubbleDown(){
	int i = 0 ;
	while((2*i+1<actualSize && arr[i].compare(arr[2*i+1])==1)|| (2*i+2<actualSize && arr[i].compare(arr[2*i+2])==1)){
		if(2*i+2<actualSize && arr[2*i+2].compare(arr[2*i+1])==-1){
			swap(arr[2*i+2],arr[i]);
			i=i*2+2;
		}else{
			swap(arr[2*i+1],arr[i]);
			i=i*2+1;
		}
	}
}
void HeapPriorityQueue::resize(int size){
	arrSize = size ;
	string* tmp = new string[arrSize];
	for(int i = 0; i <actualSize; i++){
		*(tmp+i) = *(arr+i);
	}
	delete[] arr;
	arr = tmp;
}