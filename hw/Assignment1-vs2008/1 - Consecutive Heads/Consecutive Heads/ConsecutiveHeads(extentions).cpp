/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */
#include <iostream>
#include "console.h"
#include <stdlib.h>   
#include <time.h> 
using namespace std;
 
// checks if inputted string is correct
bool isNotCorrectSequence(string sequence){
	for(int i = 0 ; i < sequence.length() ; i++){
		if(sequence[i]!='H' && sequence[i]!='T' && sequence[i]!='h' && sequence[i]!='t') {
			return true;
		}
	}
	return false ; 
}

//returns correct inputted string 
string inputSequence() {
	string sequence;
	cout<<"Input sequence of 'H' and 'T' , which you want to observe : ";
	cin >> sequence ;
	while(isNotCorrectSequence(sequence)){
		cout<<"Input CORRECT sequence : ";
		cin >> sequence ;
	}
	return sequence;
} 
void tailIsTossed(int& countFlips , string& sequence , int& index ){
	cout<<"tails"<<endl;
	countFlips++;
	if(sequence[index]== 'T' || sequence[index]== 't') {
		index++;
	}else{
		index=0;
	}
}
void headIsTossed(int& countFlips , string& sequence , int& index ){
	cout<<"heads"<<endl;
	countFlips++;
	if(sequence[index]== 'H' || sequence[index]== 'h') {
		index++;
	}else{
		index=0;
	}
}

int main() {
	string sequence = inputSequence();
	srand(int(time(NULL)));
	int countFlips = 0 ;
	int countHeadsInRow = 0;
	int index = 0 ; 
	while(true){
		int randomNumber = rand()%2;
		if(randomNumber==0){
			tailIsTossed(countFlips ,sequence , index );
		}else {
			headIsTossed(countFlips ,sequence , index );
		}
		if(index == sequence.length()){
				cout<<"It took " << countFlips<<" flips to get " << sequence << " sequence "<< endl; 
				return 0;
			}
	}
}