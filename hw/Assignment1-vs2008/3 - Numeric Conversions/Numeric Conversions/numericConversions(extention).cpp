/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include <sstream>
using namespace std;

/* Function prototypes */
int hexToDec( string str);
string textToMorse( string str , string morse[]); 
string morseToText( string str , string morse[]);
bool isLetter(char ch ) ;
/* Main program */

int main() {
	string morse[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
	cout<<"Chooese 1 to convert hexadecimal number to decimal  "<<endl;
	cout<<"Chooese 2 to convert english text to morse code "<<endl;
	cout<<"Chooese 3 to convert morse code to text  "<<endl;
	int input = getInteger(" write number : " ) ;
	while (input<1 && input>3){
		input = getInteger(" chose number between 1 and 3 " ) ;
	} 
	if(input==1){
		cout<<" input hexadecimal number to convert into decimal " << endl ; 
		string str = getLine(">>") ;
		cout<<"<< "<< hexToDec(str)<<endl;
	}else if(input == 2){
		cout<<" input	text  to convert with morse code " << endl ; 
		string str = getLine(">>") ;
		cout<<"<< "<<textToMorse(str,morse)<<endl ;
	}else {
		cout<<" input morse code  to convert into text " << endl ; 
		string str = getLine(">>") ;
		cout<<"<< "<<morseToText(str,morse)<<endl ;
	}
    return 0;
}

// Converts hexadecimal string to decimal int 
int hexToDec( string str){
	int bits = 16 ;
	int sign = 1 ; 
	if(str[0]=='-'){ 
		str=str.substr(1,str.length()-1);
		sign = -1;
	}
	if(str.length()==1)return (str[0]>='0' && str[0]<='9') ? sign*(str[0] - '0'): sign*(str[0] - 'A'+10) ;
	char ch = str[str.length()-1];
	int last = (ch>='0' && ch<='9') ? sign*(ch - '0'): sign*(ch - 'A'+10) ;
	return sign*(hexToDec(str.substr(0,str.length()-1))*bits+ last);
}
bool isLowwerCase(char ch ) {
	return (ch>='a' && ch<='z');
}
bool isUpperCase(char ch ) {
	return (ch>='A' && ch<='Z');
}
// convert english text in Morse  code  
string textToMorse( string str , string morse[]){
	string s = "" ; 
	for(int i =0 ; i < str.length() ; i++){
		int index ;
		char ch = str[i];
		if(isLowwerCase(ch)){
			index=ch-'a';
		} else if(isUpperCase(ch)){
			index = ch - 'A';
		}else continue;
		s+=morse[index]+" " ;
	}
	return s;
}
string morseToText(string str , string morse[]){
	string s = "" ; 
	istringstream ss(str) ; 
	string morseChar;
	while(ss>>morseChar){
		for(int  index = 0 ; index < 26 ; index++){
			if(morse[index]==morseChar){
				s+=index+'A';
			}
		}
	}
	return s;
}
