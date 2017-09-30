//Trevor Lane
#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include "DatalogParser.h"

using namespace std;





// int main(int argv, char* args[])
// {
//
//
//
//
// if(argv < 2)
// {
// 	//cout << "Array is bad";
// 	return 0;
// }

int runProgram(string fileName){


bool errorCaught = false;
//string fileName = args[1];

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
	DatalogParser dlparser(parseThisVector);
	DatalogProgram dlprogram = dlparser.getData();


	stringstream ss;
	ss << dlprogram.toString();
	cout << ss.str();

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

//system("PAUSE");
return 0;
}

int main(){

	vector<string> fileNames = {
	"./testCases/testCase1.txt",
	"./testCases/testCase2.txt",
	"./testCases/testCase3.txt",
	"./testCases/testCase4.txt",
	"./testCases/testCase5.txt",
	"./testCases/testCase6.txt",
	"./testCases/testCase7.txt",
	"./testCases/testCase8.txt",
	"./testCases/testCase9.txt",
	"./testCases/testCase1.txt",
};

	for(int i = 0; i < fileNames.size(); i++)
	{
		   cout << "-------------------------\n\n";
			 cout << "TEST CASE: " << (i+1) << endl;
			runProgram(fileNames[i]);
			cout << "\n\n";
	}

cout << "-------------------------\n";
	return 0;
}

