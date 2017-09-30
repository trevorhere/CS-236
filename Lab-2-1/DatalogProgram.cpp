#include "DatalogProgram.h"
#include <sstream>

using namespace std;



DatalogProgram::DatalogProgram()
{
	schemes = vector<Predicate>();
	facts = vector <Predicate>();
	rules = vector<Rule>();
	queries = vector<Predicate>();
	domains = set<string>();
}


DatalogProgram::~DatalogProgram() {}

void DatalogProgram::pushScheme(Predicate Scheme)
{
	schemes.push_back(Scheme);
}

string DatalogProgram::SchemeString()
{
	stringstream ss;
	ss << "Schemes(" << schemes.size() << "):";
	for (int i = 0; i < schemes.size(); i++)
	{
		ss << "\n  " << schemes[i].toString();
	}
	return ss.str();
}

void DatalogProgram::pushFacts(Predicate Facts)
{
	facts.push_back(Facts);
	pushDomain(Facts.getParameterVec());
}

string DatalogProgram::FactString()
{
	stringstream ss;
	ss << "Facts(" << schemes.size() << "):";
	for (int i = 0; i < facts.size(); i++)
	{
		ss << "\n  " << facts[i].toString() << ".";
	}
	return ss.str();
}

void DatalogProgram::pushRule(Rule rule)
{
	rules.push_back(rule);
	pushDomain(rule.getPredicate().getParameterVec());
}

string DatalogProgram::RuleString()
{
	stringstream ss;
	ss << "Rules(" << rules.size() << "):";
	for (int i = 0; i < rules.size(); i++)
	{
		ss << "\n  " << rules[i].toString();
	}
	return ss.str();
}

void DatalogProgram::pushQueries(Predicate Query)
{
	queries.push_back(Query);
}

string DatalogProgram::QueryString()
{
	stringstream ss;
	ss << "Queries(" << queries.size() << "):";
	for (int i = 0; i < queries.size(); i++)
	{
		ss << "\n  " << queries[i].toString() << "?";
	}
	return ss.str();

}

void DatalogProgram::pushDomain(vector<Parameter> pList)
{
	for (int i = 0; i < pList.size(); i++)
	{
		if (pList[i].getType() == "STRING")
		{
			domains.insert(pList[i].getValue());
		}
	}
}

string DatalogProgram::DomainString()
{

	stringstream ss;
	ss << "Domain(" << domains.size() << "):";
	set<string>::iterator myIt;
	for(myIt = domains.begin();

		myIt != domains.end();

		myIt++)

		ss << "\n  " << (*myIt);

	return ss.str();
}

string DatalogProgram::toString()
{
	stringstream ss;
	ss << "Success!" << endl;
	// ss << SchemeString() << endl;
	// ss << FactString() << endl;
	// ss << RuleString() << endl;
	// ss << QueryString() << endl;
	// ss << DomainString();
	return ss.str();
}