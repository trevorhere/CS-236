#pragma once
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Rule.h"

using namespace std;

class DatalogParser
{
public:
	DatalogParser(std::vector<token> tokenVector);
	virtual ~DatalogParser();

	int index;
	vector<token> tV;
	vector<string> Domains;

	DatalogProgram datalogProgram;

	Predicate pred;
	Rule rul;

	string getDomains();
	void parseTokens();
	void checkLineOne();
	void scheme();
	void idList();
	void schemeList();
	void checkLineTwo();
	void factList();
	void fact();
	void stringList();
	void checkLineThree();
	void ruleList();
	void rule();
	void headPredicate();
	void predicate();
	void predicateList();
	void parameter();
	void parameterList();
	void expression();
	bool checkOperator(string vectorType);
	void checkLineFour();
	void query();
	void queryList();
	bool checkMatch(string vectorType, string Type); 
	DatalogProgram getData();
};

