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
const int maxN=3;
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
void storeData(ifstream& file, Map<vector<string>,vector<string> >& data , int order){
	vector<string> words;
	string token;
	while(file>>token){
		order--;
		words.push_back(token);
		if(order==0)break;
	}
	while(file>>token){
			data[words].push_back(token);
			words.erase(words.begin());
			words.push_back(token);
	}
}
//returns initial word based on stored map of data 
vector<string> findInitialWord(Map<vector<string>,vector<string> > data){
	vector<string>  mostProbable;
	foreach(vector<string> word in data){
		if(data[word].size()> data[mostProbable].size()){
			mostProbable=word;
		}
	}
	return mostProbable;
}
// prints random text 
void printOut(Map<vector<string>,vector<string> >& data ){
	int size = textSize;
	srand(int(time(NULL)));
	vector<string> lengths = findInitialWord(data);
	for(int i = 0 ; i < lengths.size() ;i++){
		cout<<lengths[i]<<" ";
		size--;
	}
	while(size>0){
		string nextChar = data[lengths][rand() % data[lengths].size()];	
		lengths.erase(lengths.begin());
		lengths.push_back(nextChar);
		size--;
		cout<<nextChar<<" ";
	}
}
// stores data and prints random text
void randomize(ifstream& file, int& order){
	Map<vector<string> ,vector<string> > data;
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
