#include "Rule.h"

#include <sstream>

Rule::Rule(){}

Rule::Rule(Predicate p)
{
	predicate = p;
	predicateList = vector<Predicate>();
}

Rule::Rule(Predicate p, vector<Predicate> PredicateList)
{
	predicate = p;
	predicateList = PredicateList;

}

Rule::~Rule(){}

void Rule::pushPredicate(Predicate p)
{
	predicateList.push_back(p);
}

vector<Predicate>  Rule::getPredicateList()
{
	return predicateList;
}

Predicate  Rule::getPredicate()
{
	return predicate;
}

string Rule::toString()
{
	stringstream ss;
	ss << predicate.toString() << " :- ";
	for (int i = 0; i < predicateList.size(); i++)
	{
		if (i < 1)
		{
			ss << predicateList[i].toString();
		}
		else
		{
			ss << "," + predicateList[i].toString();
		}
	}

	ss << ".";
	return ss.str();
}