#pragma once
#include "Predicate.h"
#include <vector>
class Rule
{
public:
	Rule();
	Rule(Predicate p);
	Rule(Predicate p, vector<Predicate> PredicateList);
	~Rule();

	Predicate predicate;
	vector<Predicate> predicateList;
	void pushPredicate(Predicate ppush);
	vector<Predicate> getPredicateList();
	Predicate getPredicate();
	string toString();
};

