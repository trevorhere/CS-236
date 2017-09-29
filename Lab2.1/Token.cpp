//trevorlane

#include "Token.h"


using namespace std;

token::token(string Type, string Value, int LineNumber)
{
	type = Type;
	value = Value;
	lineNumber = LineNumber;
}