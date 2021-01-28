/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;

 int c(int n, int k){ 
	if( n== k || k == 0 ) return 1 ; 
	return c(n-1,k)+c(n-1,k-1);
}

int main() {
	int n , k ;
	cout<< "Input n and k ,to compute c(n,k) " << endl;
	cin>> n >> k ;
	while(k>n){
		cout<< "Input correct n and k " << endl;
		cin>> n >> k ;
	}
	cout<<"c("<<n<<","<<k<<") = "<<c(n,k)<<endl;
    return 0;
}
