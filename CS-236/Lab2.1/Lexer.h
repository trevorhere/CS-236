
//Trevor Lane
 //#pragma once
#include "Token.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class lexer
{
private:

public:
	lexer(string fileName);
	virtual ~lexer();

	void readFile(string fileName);

	// read file functions
	int countNewLines(string fileName);

	// INT lineNumber: Keeps track of number of new lines in file. 
	int lineNumber;
	int index;

	int numberOfTokensCreated;
	void readWordToken(string s);

	bool checkLines();

	void checkCarrageReturn(string s);

	//BOOL checkForNewLine: checks if char at current index == '\n'
	void checkForNewLine(string s);

	//VOID isSpaceFunction: checks if char at current index == ' '; 
	void isSpaceFunction(string s);
	void checkForTab(string s);

	// create tokens

	//VOID readString logic dicating type of current char.,
	void readString(string s);

	//VOID createToken: creates and stores a new token with its respective
	// Type, Value, and line number.
	int createToken(string Type, string Value, int lineNum);

	// store tokens
	void storePuncToken(string s);

	//INT storeString: parses string from current char, then creates a new
	// string token. 
	// Returns current index
	void storeString(string s);

	//INT storeWordToken: parses word from current char, then creates a
	// new word token.
	// Returns current index
	void storeWordToken(string t);

	//INT storeLineComment: parses comments from current char
	// Returns current index
	void storeLineComment(string s);

	//INT storeBlockComment: parses block comments from current char
	// Returns current Index
	void storeBlockComment(string s);

	//INT createUndefinedToken: parses undefined tokens from current 
	// char
	// Returns current index
	void createUndefinedToken(string s);

	//VECTOR: stores tokens
	vector <token> tokenVector;

	// print tokens

	//VOID printTokens: prints tokens
	void printTokens(vector<token> myTokenVector);

	//VOID printNumberOfLines: prints number of lines
	void printNumberOfLines(int numLines);

	vector<token> returnTokens();

};