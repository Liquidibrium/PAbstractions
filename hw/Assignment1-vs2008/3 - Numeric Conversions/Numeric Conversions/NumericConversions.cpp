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
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
    cout<<intToString(-0)<<endl;
	cout<<stringToInt("-00000")<<endl;
    return 0;
}
string intToString(int n){
	string s = ""; 
	if(n<0){
		s = "-";
		n=n*(-1);
	}
	if(n/10 == 0) return s+char(n+'0');
	return s+intToString(n/10)+char(n%10 +'0');
}
int stringToInt(string str){
	int sign = 1 ; 
	if(str[0]=='-'){ 
		str=str.substr(1,str.length()-1);
		sign = -1;
	}
		if(str.length()==1)return sign*(str[0] - '0');
		return sign*(stringToInt(str.substr(0,str.length()-1))*10+(str[str.length()-1] - '0'));
}
