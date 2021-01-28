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

const int numberOfConsequtiveHeads = 3 ; 
int main() {
    srand(int(time(NULL)));
	int countFlips = 0 ;
	int countHeadsInRow = 0;
	while(true){
		int randomNumber = rand()%2;
		if(randomNumber==0){
			cout<<"tails"<<endl;
			countFlips++;
			countHeadsInRow = 0 ;
		}else {
			cout<<"heads"<<endl;
			countFlips++;
			countHeadsInRow++;
			if(countHeadsInRow == numberOfConsequtiveHeads){
				cout<<"It took " << countFlips<<" flips to get " << numberOfConsequtiveHeads << " consequtive heads. "<< endl; 
				return 0;
			}
		}
	}
}
