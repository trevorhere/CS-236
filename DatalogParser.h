#pragma once
#include <vector>
#include "Token.h"

using namespace std;

class DatalogParser
{
public:
	DatalogParser(std::vector<token> tokenVector);
	virtual ~DatalogParser();

	int index;
	vector<token> tV;

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
	void expression();
	bool checkOperator(string vectorType);
	void checkLineFour();
	void query();
	void queryList();
	bool checkMatch(string vectorType, string Type);
	//void throwExceptionFunction(token t);
};

