//trevor lane
#pragma once
#include <string>

using namespace std;

class token
{

public:
	

	string type;
	string value;
	int lineNumber;

	token(string type, string value, int lineNumber);

};