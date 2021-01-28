/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include "simpio.h"
#include "tokenscanner.h"
using namespace std;

const double c0 = -15.59;
const double c1 = 0.39;
const double c2 = 11.8;

// Function  prototypes 
void openFile(ifstream &file, int& sentences,int& syllables , int& words );
void analiseFile(ifstream &file, int& sentences , int &words , int &syllables);
bool isSentence(string word);
bool isSyllable(char ch);
int countSyllables(string word);
bool isWord(string str);

// Main program 
int main() {
	int sentences = 0 ;
	int words =0;
	int syllables = 0 ; 
	ifstream file;
	openFile(file,sentences, syllables , words);
	if(sentences==0){sentences++;}
	if(word==0){word++;}
	cout << "sentences : "<< sentences <<" words : "<< words << " syllables : " << syllables << endl;
	cout<< " Grade " << c0 + c1 * words / sentences + c2 * syllables / words<<endl ; 
    return 0;
}
// open correct file 
void openFile(ifstream &file, int& sentences,int& syllables , int& words ){
	string fileName ;
	cin>>fileName;
	string token ; 
	while(true){
		file.open(fileName.c_str(),ifstream::in);
		if(file.good()){break;}
		else {	
			cout<<"input coorect file name : " << endl ;
			cin>>fileName;
			file.clear();
		}
	}
	analiseFile(file,sentences,words,syllables);
	file.close();
}
// counts sentences , words and syllables in file 
void analiseFile(ifstream &file, int& sentences , int &words , int &syllables){
	TokenScanner scanner ;
	scanner.setInput(file);
	scanner.addWordCharacters("'");
	while(scanner.hasMoreTokens()){
		string token = scanner.nextToken();
		if(isSentence(token)){ sentences++;}
		else if(isWord(token)){
			words++;
			syllables += countSyllables(token);
		//	cout << token << " Sylables :" << countSyllables(token)<<endl;
		}
	}
}

bool isSentence(string word){
	char first = word[0] ; 
	return first=='.'||first=='?' || first=='!' ; 
}
bool isWord(string str){
	char first = str[0];
	return (first >= 'a' && first <='z')||(first >= 'A' && first <='Z');
}

// return number of syllables in word 
int countSyllables(string word){
	int count = 0 ; 
	if(isSyllable(word[0])){count++;}//Checks first character 
	for(int i = 1; i < word.length(); i++){
		if( i==word.length()-1 &&( word[i] == 'e' || word[i] == 'E')){ break;}
		if(isSyllable(word[i]) && !isSyllable(word[i-1])){count++;}
	}
	return (count==0) ? 1 : count ; // if count is 0 , returns 1 
}
// checks if character is syllable 
bool isSyllable(char ch){	
		string syllables = "aeiouyAEIOUY";
			for(int i = 0 ; i < syllables.length(); i++){
				if(ch==syllables[i])return true;
			}
		 	return false ; 
}