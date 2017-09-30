#pragma once
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <set>
#include <string>
using namespace std;

class DatalogProgram
{
public:
	DatalogProgram();
	~DatalogProgram();

	vector<Predicate> schemes;
	void pushScheme(Predicate Scheme);
	string SchemeString();

	vector<Predicate> facts;
	void pushFacts(Predicate Facts);
	string FactString();

	vector<Rule> rules;
	void pushRule(Rule Rule);
	string RuleString();

	vector<Predicate> queries;
	void pushQueries(Predicate Query);
	string QueryString();

	set<string> domains;
	void pushDomain(vector<Parameter> pList);
	string DomainString();

	string toString();

};

