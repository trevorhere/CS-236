#pragma once
#include <string>

using namespace std;
class Parameter
{
public:
	Parameter(string Type, string Value);
	~Parameter();

	string type;
	string value;
	string getType();
	string getValue();

};

