/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include "map.h"
#include <vector>
#include <stdlib.h>   
#include <time.h> 
using namespace std;
//output text length
const int textSize = 2000;
const int minN=1;
const int maxN=10;
// reads correct file
void openFile(ifstream& file,int& order){
	cout<<"enter file name: " ;
	string fileName;
	cin>>fileName;
	while(true){
		file.open(fileName.c_str());
		if(file.fail()){
			cout<<"input coorect file name : " << endl ;
			cin>>fileName;
			file.clear();
		}else {break;}
	}
	while(order<minN || order>maxN){
		cout<<"enter order number ["<<minN<<"-"<<maxN<<"] : " ;
		cin>>order;
	}
	cout<<"Processing file..."<<endl;
}
// stores data in map based on file and order 
void storeData(ifstream& file, Map<string,vector<char> >& data , int& order){
	string word = "" ;
	char ch;
	file.get(ch);
	while (file.good()) {
		if(word.length()<order){
			word+=ch;
		}
		file.get(ch);
		if(word.length() == order){
			data[word].push_back(ch);
			word=word.substr(1)+ch;
		}
	}
}
//returns initial word based on stored map of data 
string findInitialWord(Map<string,vector<char> > data){
	string  maxLengthString;
	foreach(string word in data){
		if(data[word].size()> data[maxLengthString].size()){
			maxLengthString=word;
		}
	}
	return maxLengthString;
}
// prints random text 
void printOut(Map<string,vector<char> >& data ){
	int size=textSize;
	srand(int(time(NULL)));
	string currentWord = findInitialWord(data);
	cout<<currentWord;
	size-=currentWord.length();
	char nextChar;
	while(size>0){
		int length=data[currentWord].size();
		if(length==0)return;
		nextChar = data[currentWord][rand() % length];
		currentWord=currentWord.substr(1)+nextChar;
		size--;
		cout<<nextChar;
	}
}
// stores data and prints random text
void randomize(ifstream& file, int& order){
	Map<string,vector<char> > data;
	storeData(file, data , order);
	printOut(data);
}
int main() {
	ifstream file;
	int order;
	openFile(file,order);
	randomize(file,order);
	file.close();
    return 0;
}
