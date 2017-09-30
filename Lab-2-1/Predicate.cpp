#include "Predicate.h"
#include<string>
#include<sstream>

Predicate::Predicate(){}

Predicate::Predicate(string Identifier)
{
	identifier = Identifier;
	parameterVec = vector<Parameter>();
}

Predicate::Predicate(string Identifier, vector<Parameter> ParameterVec)
{
	identifier = Identifier;
	parameterVec = ParameterVec;
}

Predicate::~Predicate()
{
}

vector<Parameter> Predicate::getParameterVec()
{
	return parameterVec;
}

string Predicate::getID()
{
	return identifier;
}

void Predicate::pushParameter(Parameter parameter)
{
	parameterVec.push_back(parameter);
}

string Predicate::toString()
{
	stringstream ss;
	ss << identifier << '(';
	for (int i = 0; i < parameterVec.size(); i++)
	{
		if (i < 1)
		{
			ss << parameterVec[i].getValue();
		}
		else
		{
			ss << ',' << parameterVec[i].getValue();
		}
	}
	ss << ')';
	return ss.str();
}