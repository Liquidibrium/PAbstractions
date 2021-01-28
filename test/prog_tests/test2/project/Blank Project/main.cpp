#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "lexicon.h"
#include "scrabble.h"

using namespace std;

void solution(Lexicon &lex, string soFar, string rest, int curScore, string &res, int &resScore) {
	if (!lex.containsPrefix(soFar)) {
		return;
	}
	
	if (lex.contains(soFar) && resScore < curScore) {
		res = soFar;
		resScore = curScore;
	}

	for (int i=0; i<rest.size(); i++) {
		if (rest[i] == '?') {
			for (char c='a'; c<='z'; c++) {
				solution(lex, soFar + c, rest.substr(0, i) + rest.substr(i+1), curScore, res, resScore);				
			}
		} else {
			solution(lex, soFar + rest[i], rest.substr(0, i) + rest.substr(i+1), curScore+getSymbScore(rest[i]) ,res, resScore);	
		}
	}
}
/*
string findMaxScoreWord(Lexicon &lex, string cards) {
	string res = "";
	int score;
	time_t beginTime = time(NULL);
	solution(lex, "", cards, 0, res, score);
	time_t endTime = time(NULL);

	cout << "Word with highest score: " << res << ", score is: " << score <<endl;
	cout << "Time: " << endTime-beginTime << " seconds" << endl;
	return res;
}
*/

int main() {
	Lexicon lex("EnglishWords.dat");
	string res = findMaxScoreWord(lex, "moonzuiq");
	return 0;
}
