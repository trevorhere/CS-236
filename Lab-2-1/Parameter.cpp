#include "Parameter.h"



Parameter::Parameter(string Type, string Value)
{
	type = Type;
	value = Value;

}


Parameter::~Parameter()
{
}


string Parameter::getValue()
{
	return value;
}


string Parameter::getType()
{
	return type;
}

