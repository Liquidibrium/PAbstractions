 
#include <iostream>
#include "simpio.h"
#include "console.h"
#include <string>
#include "strlib.h"
using namespace std;

// computes c(n,k) with n and k integers 
int c(int n, int k){
	if( n== k || k == 0 ) return 1 ; 
	return c(n-1,k)+c(n-1,k-1);
}
// get n and k from console
void getInput(int& n , int& k){
	cout<< "Input n and k ,to compute c(n,k) " << endl;
	n = getInteger("n :");
	k = getInteger("k :");
	while (k>n || k<0 || n<0){
		cout<<"input correct n or k "<< endl;
		n = getInteger("n :");
		k = getInteger("k :");
	}
}
// Creates empty string with length=n ; 
string emptyspaces(int n ) {
	string emptyString = "" ;
	for(int i = 0 ; i < n; i++){
		emptyString=emptyString+" ";
	}
	return emptyString;
}
// draws Pascal's triangle 
void PascalTriangle(int n){ 
	for(int i = 0 ; i <= n; i++){
		string s = emptyspaces(n-i);
		for(int j =0 ; j <= i ; j++){
			s+=integerToString(c(i,j))+ " ";
		}
		cout<<s<<endl;
	}
}
int main() {
	int n , k ;
	getInput(n,k);
	cout<<"c("<<n<<","<<k<<") = "<<c(n,k)<<endl;
	PascalTriangle(n);
	return 0;
}
