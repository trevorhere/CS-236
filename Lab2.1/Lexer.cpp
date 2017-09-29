//Trevor Lane
//increment inde in main function...


#include "Lexer.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <ctype.h>


using namespace std;

lexer::lexer(string fileName) {

	lineNumber = 1;
	numberOfTokensCreated = 0;
	index = 0;
	readFile(fileName);
}

lexer::~lexer() {}

int numberOfNewLines = 0;


void lexer::readFile(string fileName)
{

	ifstream inputFile;
	inputFile.open(fileName);
	int counter = 0;
	string inputFileString = "";
	numberOfNewLines = countNewLines(fileName);
	//cout << "Number of New lines in file: " << numberOfNewLines << endl;

	if (inputFile)
	{
		while (!inputFile.eof())
		{
			char c = inputFile.get();
			inputFileString += c;
			//counter++;
		}
		inputFile.close();

		string formattedString = inputFileString.substr(0, inputFileString.size() - 1);
		readString(formattedString);
		//printTokens(tokenVector);

	}
	else
	{
		cout << "Failed to open file";
	}
		
}

void lexer::readString(string s)
{
	while (index <= s.length() - 1 && s.length() > 0)
	{
		//CHECK FOR CARRIAGE RETURN ##############################################

		checkForTab(s);
		if (index  > s.length() - 1)
			break;

		checkCarrageReturn(s);

		// CHECK FOR NEW LINES ###################################################
		checkForNewLine(s);
		if (index  > s.length() - 1)
			break;
		
		//WHITESPACE #############################################################
		isSpaceFunction(s);
		if (index  > s.length() - 1)
			break;

		//CHECK WORD TYPES #######################################################
		if (isalpha(s[index]))
			readWordToken(s);

		if (index  > s.length() - 1)
			break;

		//CHECK FOR PUNCTUATION, STRINGS, AND COMMENTS     #######################
		else
		storePuncToken(s);

	}

	createToken("EOF", "", lineNumber);

}

//bool lexer::checkLines()
//{
//	if ((numberOfNewLines + 1) == lineNumber)
//		return true;
//
//	else 
//		return false;
//}

void lexer::checkCarrageReturn(string s)
{
	while (s[index] == '\r')
		index++;

}

void lexer::createUndefinedToken(string s)
{

	string undefinedToken = "";
	undefinedToken += s[index];
	createToken("UNDEFINED", undefinedToken, lineNumber);
	index++;
	return;
}

void lexer::storeString(string s)
{
	int startingLineNumber = lineNumber;
	string stringContents = "\'";
	index++;

	bool finalQuoteFound = false;
	bool undefinedTokenPushed = false;

	while (!finalQuoteFound && !undefinedTokenPushed)
	{
		stringContents += s[index];
		if (s[index] == '\n')
		{
			lineNumber++;
		}
		if (s[index] == '\'') //CHECK FOR QUOTE
		{
			if (s[index + 1] != '\'') // CHECK FOR DOUBLE QUOTE
			{
				//IF ONLY ONE QUOTE FOUND -> END OF STRING
				index++;
				break;
			}
			else
			{
				//IF DOUBLE QUOTE FOUND -> APOS FOUND
				index++;
			    stringContents += s[index];
			}
		}

		index++;
		//IF STRING ENDS BEFORE FINAL APOS IS DETECTED
		if (index >= s.length())
		{
			createToken("UNDEFINED", stringContents, startingLineNumber);
			undefinedTokenPushed = true;
		}

	}

	if (undefinedTokenPushed == false)
	{
		createToken("STRING", stringContents, startingLineNumber);
	}
	return;
}

void lexer::storeBlockComment(string s)
{ // test this if possible
	int commentStartLine = lineNumber;

	string commsConts = "#|";
	index++;

	bool endFound = false;
	bool undefinedTokenPushed = false;
	while (!endFound)
	{
		index++;
		commsConts += s[index];

		if (s[index] == '|')
		{
			if (s[index + 1] == '#')
			{
				index++;
				commsConts += s[index];
				break;
			}
		}
		else if (index >= s.length() - 1)
		{
			createToken("UNDEFINED", commsConts, commentStartLine);
			undefinedTokenPushed = true;
			endFound = true;
		}

		if (s[index] == '\n')
		{
			lineNumber++;
		}
	}

	if (!undefinedTokenPushed)
	{

		createToken("COMMENT", commsConts, commentStartLine);
	}

	index++;
	return;
}

void lexer::storeLineComment(string s)
{

	bool newlineFound = false;
	int startingLineNumber = lineNumber;
	string commsConts = "#";


	bool endFound = false;
	while (s[index] != '\n' || (lineNumber <= numberOfNewLines + 1))
	{
		if (index >= s.length() - 1)
		{
			commsConts += s[index];
			index++;
			break;
		}
		
		if (s[index + 1] != '\n')
		{
			index++;
			commsConts += s[index];
		}
		else
		{
			index++;
			break;

		}

		if (lineNumber > numberOfNewLines + 1)
			break;
	}


	createToken("COMMENT", commsConts, startingLineNumber);
	return;

}

void lexer::checkForTab(string s)
{
	while (s[index] == '\t')
		index++;
	

}
void lexer::isSpaceFunction(string s)
{
	while (s[index] == ' ' && s[index] != '\n')
		index++;
}

void lexer::checkForNewLine(string s)
{
	while (s[index] == '\n')
	{
		index++;
		lineNumber++;
	}

}

void lexer::readWordToken(string s)
{
	string tokenType = "";

	while (isalnum(s[index]))
	{
		if (s[index] == '\n')
			break;
		// id with a line break next to it
		//test this somehow
			

		tokenType += s[index];
		index++;
	}

	storeWordToken(tokenType);
}

void lexer::storeWordToken(string t)
{
	string Type;

	if (t == "Schemes")
	{
		Type = "SCHEMES";
	}
	else if (t == "Facts")
	{
		Type = "FACTS";
	}
	else if (t == "Rules")
	{
		Type = "RULES";
	}
	else if (t == "Queries")
	{
		Type = "QUERIES";
	}
	else
	{
		Type = "ID";
	}

	createToken(Type, t , lineNumber);
	return;
	// test this too
}

void lexer::storePuncToken(string s)
{
	switch (s[index])
	{
	case'\t':
		index++;
		break;

	case'\r':
		index++;
		break;
	case' ':
		break;
	case'\n':
		break;
		//COMMA ##########################################################
	case ',':
		createToken("COMMA", ",", lineNumber);
		index++;
		break;

		//PERIOD #########################################################	
	case '.':
		createToken("PERIOD", ".", lineNumber);
		index++;
		break;

		//Q_MARK #########################################################	
	case '?':
		createToken("Q_MARK", "?", lineNumber);
		index++;
		break;

		//LEFT_PAREN #####################################################
	case '(':
		createToken("LEFT_PAREN", "(", lineNumber);
		index++;
		break;

		//RIGHT__PAREN ###################################################
	case ')':
		createToken("RIGHT_PAREN", ")", lineNumber);
		index++;
		break;

		//COLON_DASH #####################################################
	case ':':
	{
		if (s[index + 1] == '-')
		{
			createToken("COLON_DASH", ":-", lineNumber);
			index++;
		}
		else //COLON #################################################
		{
			createToken("COLON", ":", lineNumber);
		}

		index++;
		break;
	}
	//MULTIPLY #######################################################
	case '*':

		createToken("MULTIPLY", "*", lineNumber);
		index++;
		break;

		//ADD ############################################################
	case '+':
		createToken("ADD", "+", lineNumber);
		index++;
		break;

		//COMMENT ########################################################
	case '#':   //piece of trash function is storing two tokens	
	{
		if (s[index + 1] == '|') // BLOCK COMMENT
		{
			 storeBlockComment(s);
		}

		else  // LINE COMMENT #xxxxx ends with /n or EOF
		{     //	-	goes until \n or EOF
			 storeLineComment(s);
		}
		break;
	}
	//STRING #########################################################
	case '\'':
		storeString(s);
		break;

		//UNDEFINED #########################################################    	
	default:
	{
		if (s[index] != '\n')
		{
			createUndefinedToken(s);
		}
		break;
	}

	}

}

void lexer::printTokens(vector<token> tokenVector)
{

	//cout << "Printing Token Vector: " << endl;
	for (int i = 0; i < tokenVector.size(); i++)
	{
		cout << "("
			<< tokenVector[i].type
			<< ","
			<< "\""
			<< tokenVector[i].value
			<< "\""
			<< ","
			<< tokenVector[i].lineNumber
			<< ")"
			<< endl;
	}
	cout << "Total Tokens = " << numberOfTokensCreated << endl;
}

void lexer::printNumberOfLines(int lineNum)
{
	cout << "Number of Lines: " << lineNum << endl;
}

int lexer::createToken(string Type, string Value, int lineNum)
{
	tokenVector.push_back(token(Type, Value, lineNum));
	numberOfTokensCreated++;
	return numberOfTokensCreated;
}

int lexer::countNewLines(string fileName)
{
	char tempChar;
	int tempNum = 0;
	ifstream tempInputFile;
	tempInputFile.open(fileName);
	while (tempInputFile.good())
	{
		tempChar = tempInputFile.get();

		if (tempChar == '\n')
			tempNum++;
	}

	tempInputFile.close();
	return tempNum;
}

vector<token> lexer::returnTokens()
{
	return tokenVector;
}

