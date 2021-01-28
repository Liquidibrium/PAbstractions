/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>e

#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "queue.h"
#include <vector>
using namespace std;

void inputWords(string& starting , string& ending){
	cout<<"Enter the STARTING word (or 0 to quite): " ;
	cin>>starting;
	if(starting=="0"){
			cout<<"Bye"<<endl;
			return ;
	}
	cout<<"Enter the ENDING word : " ;
	cin>>ending;
	cout<<"Searching ... "<<endl;
}
bool firstCheck(string& starting,string& ending,Lexicon& english){
	if(starting.length()!=ending.length()) return false;
	if(!english.contains(starting))return false;
	if(!english.contains(ending))return false;
	return true;
}
// adds words in lexicon those are one letter different from word
void findWords(string word,Lexicon& oneLetterDiff,Lexicon& english){
	int length = word.length();
	for(int i = 0;i < length ; i++){
		char letter = word[i];
		for(char ch = 'a' ; ch<='z' ; ch++){
			string tmp = word;
			if(letter!=ch){
				tmp[i]=ch;
				if(english.contains(tmp)&& !oneLetterDiff.contains(tmp)){
					oneLetterDiff.add(tmp);
				}
			}
		}	
	}
}
// returns shortest ladder as vector of strings 
vector<string> findLadder(string& starting,string& ending,Lexicon& english){
	Lexicon usedWords;
	Queue<vector<string> > ladders;
	vector<string> firstLadder;
	firstLadder.push_back(starting);
	usedWords.add(starting);
	ladders.enqueue(firstLadder);
	while(!ladders.isEmpty()){
		vector<string> topLadder = ladders.dequeue();
		string lastWord = topLadder[topLadder.size()-1];
		if(lastWord==ending){
			return topLadder;
		}
		Lexicon oneLetterDiff; 
		findWords(lastWord,oneLetterDiff,english);
		foreach(string word in oneLetterDiff){
			if(!usedWords.contains(word)){
				usedWords.add(word);
				vector<string> tmp = topLadder;
				tmp.push_back(word);
				ladders.enqueue(tmp);
			}
		}
	}
	vector<string> empty;
	return empty;
}
void printOut(vector<string>& ladder){
	if(ladder.size()!=0){
		cout<<"Ladder found: ";
		for(int i = 0 ; i < ladder.size()-1 ; i++){
			cout<< ladder[i]<< " --> " ;
		}
		cout<< ladder[ladder.size()-1]<< endl ;
	}else {
		cout<<"No word ladder could be found"<<endl;
	}
}

void searchForLadder(string& starting , string& ending , Lexicon& english){
	if(firstCheck(starting,ending,english)){
		vector<string> ladder = findLadder(starting,ending,english);
		printOut(ladder);
	}else{
		cout<<"No word ladder could be found"<<endl;
	}
}

int main() {
	Lexicon english("EnglishWords.dat");
	string starting , ending ;
	while(true){
		inputWords(starting,ending);
		if(starting=="0")return 0;
		searchForLadder(starting,ending,english);
	}
	return 0;
}
