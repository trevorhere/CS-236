//Trevor Lane
#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include "DatalogParser.h"

using namespace std;

int main(int argv, char* args[])
{
	
if(argv < 2)
{
	//cout << "Array is bad";
	return 0;
}

string fileName = args[1];

bool errorCaught = false;


lexer Lexer(fileName);

vector<token> tempVector = Lexer.returnTokens();
vector<token> parseThisVector;


for (int i = 0; i < tempVector.size(); i++)
{
	if (tempVector[i].type != "COMMENT")
		parseThisVector.push_back(tempVector[i]);
}

try
{
	DatalogParser dlp(parseThisVector);
}
catch (token t)
{


	cout << "Failure!\n";
	cout << "  " 
		<< "("
		<< t.type
		<< ","
		<< "\""
		<< t.value
		<< "\""
		<< ","
		<< t.lineNumber
		<< ")"
		<< endl;
	errorCaught = true;
}

if (!errorCaught)
cout << "Success!\n";



//system("PAUSE");
return 0;
}

