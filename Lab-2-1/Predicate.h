#pragma once
#include "Parameter.h"
#include <vector>
using namespace std;

class Predicate
{
public:
	Predicate();
	Predicate(string identifier);
	Predicate(string Identifier, vector<Parameter> ParameterVec);
	~Predicate();

	string identifier;
	vector<Parameter> parameterVec;
	vector<Parameter> getParameterVec();
	string getID();
	void pushParameter(Parameter parameter);
	string toString();

};

