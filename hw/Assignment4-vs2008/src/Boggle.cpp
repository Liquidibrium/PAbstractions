/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "set.h"
#include "map.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};
/* Function prototypes */

void welcome();
void giveInstructions();



/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}


// transforms row and col into linar index
int toIndex(int& row, int& col,int boardSize){
	return row * boardSize + col;
}
// lets player to choose boggle size 
int chooseGridSize(){
	string input = getLine("You can choose standard Boggle (4x4 grid)\nor Big Boggle (5x5).\nWould you like Big Boggle? ");
	while(true){
		if(input == "yes" || input == "YES")return 5;
		if(input == "no" || input == "NO")return 4;
		input = getLine("Please answer yes or no.\nWould you like Big Boggle? ");
	}
}
// get sequence of chars from player 
void getCustomCubes(Grid<char>& board){
	int area = board.numCols() * board.numRows();
	string customInput = getLine("Enter the string: ");
	while(customInput.length() < area){
		customInput = getLine("Try to input longer string: ");
	}
	customInput = toUpperCase(customInput);
	int i = 0;
	for(int row = 0 ; row < board.numRows(); row++){
		for(int col = 0; col < board.numCols(); col++){
			char currChar = customInput[i++];
			board[row][col] = currChar;
			labelCube(row, col, currChar);
		}
	}
}
// fill board with random default cubes
void randomizeBoard(Grid<char>& board, Vector<string>& cubes){
	int cubeSides = 6;
	for(int row = 0; row < board.numRows(); row++){
		for(int col = 0; col < board.numCols(); col++){
			int randomCubeNumb = randomInteger(0,cubes.size()-1);
			string randomCube = cubes[randomCubeNumb];
			char randomChar = randomCube[randomInteger(0,cubeSides-1)];
			cubes.remove(randomCubeNumb);
			board[row][col] = randomChar;
			labelCube(row, col, randomChar);
		}
	}
}
// copy array to vector
void getDefaultCubes(Grid<char>& board){
	Vector<string> cubes;
	int numberOfCubes = board.numCols() * board.numRows();
	if(numberOfCubes == 16){
		for(int i = 0; i < numberOfCubes; i++)
			cubes.add(STANDARD_CUBES[i]);
	}else{
		for(int i = 0; i < numberOfCubes; i++)
			cubes.add(BIG_BOGGLE_CUBES[i]);
	}
	randomizeBoard(board, cubes);
}
//lets player to choose board size and cubes 
void getCubes(Grid<char>& board){
	int boardSize = chooseGridSize();
	board.resize(boardSize, boardSize);
	drawBoard(boardSize, boardSize);
	string input = getLine("Do you want to force the board configuration? ");
	while(true){
		if(input == "yes" || input == "YES"){
			getCustomCubes(board);
			break;
		}
		if(input == "no" || input == "NO"){
			getDefaultCubes(board);
			break;
		}
		input = getLine("Please answer yes or no. \nWould you like Big Boggle? ");
	}
}
// checks if index is in bounds 
bool isValidIndex(int& row, int& col,int boardSize){
	if(row < 0 || col < 0 || row >= boardSize || col >= boardSize)return false;
	return true;
}
// checks if vector conteins index 
bool contains(int& index , Vector<int>& used){
	for(int i = 0 ; i < used.size() ; i++){
		if(used[i] == index)return true;
	}
	return false;
}
//Saves all the words if can be made from the row and col
void isWord(Grid<char>& board,int& row, int& col, Map<string,Vector<int> >& possible, Lexicon &lex, Vector<int>& usedIndex, string str){
	if(str.size() >= 4 ){
		if(lex.contains(str)) possible[str]=usedIndex;
	}
	for(int i = -1; i <= 1; i++){
		int currRow = row + i;
		for(int j = -1; j <= 1; j++){
			int currCol = col + j;
			int index = toIndex(currRow, currCol, board.numRows());
			if(isValidIndex(currRow,currCol,board.numRows()) && !contains(index,usedIndex)){
				char ch = 'a' - 'A' + board[currRow][currCol];		
				string nextStr = str + ch;
				if(!lex.containsPrefix(nextStr))continue;
				usedIndex.add(index);
				isWord(board,currRow,currCol,possible,lex,usedIndex,nextStr);
				usedIndex.remove(usedIndex.size()-1);
			}
		}
	}	
}
// finds and  saves all words tha can be found in board 
void getAllPossibleWords(Map<string, Vector<int> >& AllPossibleWords, Grid<char>& board, Lexicon& lex){	
	for(int row = 0; row < board.numRows(); row++){
		int	currRow = row;
		for(int col = 0; col < board.numCols(); col++){
			int currCol = col;	
			char ch = 'a' + board[row][col] - 'A';
			string str;
			str = ch;
			Vector<int> usedIndex;
			usedIndex.add(toIndex(row,col,board.numRows()));
			isWord(board, row, col, AllPossibleWords, lex, usedIndex, str);
		}
	}

}
// if flag is true highliths cubes 
void highlightCubes(Vector<int> sequence, int boardSize, bool flag){
	for(int i = 0; i < sequence.size(); i++)
		highlightCube(sequence[i] / boardSize, sequence[i] % boardSize, flag);
}
// saves players correct guessed words into the set and highlights cubes 
void playersTurn(Grid<char>& board, Map<string,Vector<int> >& AllPossibleWords, Set<string>& guessed){
	while(true){
		string word = getLine("Input word or enter to finish ");
		if(word.size() == 0) break;
		word = toLowerCase(word);
		if(AllPossibleWords.containsKey(word)) {
			if(!guessed.contains(word)){
				guessed.add(word);
				recordWordForPlayer(word, HUMAN);
				Vector<int> sequence = AllPossibleWords[word];
				highlightCubes(sequence, board.numRows(), true);
				pause(500);
				highlightCubes(sequence, board.numRows(), false);
				if(AllPossibleWords.size() == guessed.size()){
					cout<<"Congrats you found all possible the words"<<endl;
					return;
				}
			}else cout<<"Already guessed"<<endl;
		}
		else cout<<"Wrong word"<<endl;
	}
}
// adds rest of words into computers list 
void computersTurn(Map<string,Vector<int> >AllPossibleWords,Set<string> guessed){
	foreach(string word in AllPossibleWords){
		if(!guessed.contains(word))
			recordWordForPlayer(word,COMPUTER);
	}
}
//plays one time
void play(){
	Grid<char> board;
	getCubes(board);
	Lexicon lex("EnglishWords.dat");
	Map<string,Vector<int> > AllPossibleWords;
	getAllPossibleWords(AllPossibleWords,board,lex);
	Set<string> guessed;
	playersTurn(board, AllPossibleWords, guessed);
	computersTurn(AllPossibleWords, guessed);
}

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions(); 
	while(true){
		play();
		if(getLine("Wanna play again? ") != "yes")return 0;
	}
    return 0;
}