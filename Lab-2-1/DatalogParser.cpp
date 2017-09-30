#include "DatalogParser.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>



DatalogParser::DatalogParser(std::vector<token> tokenVector)
{
	
	index = 0;
	tV = tokenVector;
	
	datalogProgram = DatalogProgram();
	
	pred = Predicate();
	rul = Rule();
	parseTokens();


}

DatalogParser::~DatalogParser(){}

void DatalogParser::parseTokens()
{
	if (tV.size() == 0)
		throw("empty array");
 
	checkLineOne();
	checkLineTwo();
	checkLineThree();
	checkLineFour();

}

void  DatalogParser::checkLineOne()
{

	// check for SCHEMES match
	if (tV[index].type == "SCHEMES")
		index++;
	else
		throw tV[index];

	// check for COLON match
	if (tV[index].type == "COLON")
		index++;
	else
		throw tV[index];

	// check for scheme match
	scheme();

	// check for schemeList match
	schemeList();

}

void  DatalogParser::scheme()
{

	 pred = Predicate(tV[index].value);
	
	if (tV[index].type == "ID")
	{
		index++;

		if (tV[index].type == "LEFT_PAREN")
		{ 
			index++;

			if (tV[index].type == "ID")
			{
				pred.pushParameter(Parameter(tV[index].type, tV[index].value));
				index++;
		
				if (tV[index].type == "COMMA")
				{
					 idList();
				}
				
					if (tV[index].type == "RIGHT_PAREN")
					{

						index++;
					}
					else
					{
						throw tV[index];
					}
			}
			else
			{
				throw tV[index];
			}

		}
		else
		{
			throw tV[index];
		}
	}
	else 
	{
		throw tV[index];
	}

	datalogProgram.pushScheme(pred);
}

void DatalogParser::idList()
{

	if (tV[index].type == "COMMA")
	{
		index++;

		if (tV[index].type == "ID")
		{
			pred.pushParameter(Parameter(tV[index].type, tV[index].value));
			index++;

			if (tV[index].type == "COMMA")
			{
				idList();
			}
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{ 
		throw tV[index];
	}

}

void  DatalogParser::schemeList()
{
    // check for scheme and schemelist 
	
	if (tV[index].type == "ID")
	{
		scheme();
		schemeList();
	} 


	//or lambda

}

void  DatalogParser::checkLineTwo()
{
	// check for FACTS
	if (tV[index].type == "FACTS")
		index++;
	else
		throw tV[index];

	//check for COLON
	if (tV[index].type == "COLON")
		index++;
	else
		throw tV[index];

	//check for factlist
	factList();
}

void  DatalogParser::factList()
{
	if (tV[index].type == "ID")
	{
		fact();
		factList();
	}

}

void DatalogParser::fact()
{
	pred = Predicate(tV[index].value);

	if (tV[index].type == "ID")
	{
		index++;

		if (tV[index].type == "LEFT_PAREN")
		{
			index++;

			if (tV[index].type == "STRING")
			{
				Domains.push_back(tV[index].value);
				pred.pushParameter(Parameter(tV[index].type, tV[index].value));
				index++;

				if (tV[index].type == "COMMA")
				{
					stringList();
				}

				if (tV[index].type == "RIGHT_PAREN")
				{
					index++;
				}
				else
				{
					throw tV[index];
				}
					if (tV[index].type == "PERIOD")
					{
					index++;
					}
					else
					{
						throw tV[index];
					}
			}
			else
			{
				throw tV[index];
			}

		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}

	datalogProgram.pushFacts(pred);
}

void  DatalogParser::stringList()
{
	if (tV[index].type == "COMMA")
	{
		index++;

		if (tV[index].type == "STRING")
		{
			pred.pushParameter(Parameter(tV[index].type, tV[index].value));
			index++;
			if (tV[index].type == "COMMA")
			{
				stringList();
			}
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}
}

void DatalogParser::checkLineThree()
{
	// check for FACTS
	if (tV[index].type == "RULES")
		index++;
	else
		throw tV[index];

	//check for COLON
	if (tV[index].type == "COLON")
		index++;
	else
		throw tV[index];

	//check for factlist
	ruleList();
}

void DatalogParser::ruleList()
{
	if (tV[index].type == "ID")
	{
		rule();
		ruleList();
	}
}

void DatalogParser::rule()
{
	if (tV[index].type == "ID")
	{
		headPredicate();

		rul = Rule(pred);

		if (tV[index].type == "COLON_DASH")
		{
			index++;

			if (tV[index].type == "ID")
			{
				predicate();

				if (tV[index].type == "COMMA")
				{
					predicateList();
				}
				if (tV[index].type == "PERIOD")
				{
					index++;
				}
				else
				{
					throw tV[index];
				}
			}
			else
			{
				throw tV[index];
			}
			
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}

	datalogProgram.pushRule(rul);
}

void  DatalogParser::headPredicate()
{
	if (tV[index].type == "ID")
	{
		pred = Predicate(tV[index].value);
		index++;

		if (tV[index].type == "LEFT_PAREN")
		{
			index++;
			if (tV[index].type == "ID")
			{
				pred.pushParameter(Parameter(tV[index].type, tV[index].value));
				index++;
				if (tV[index].type == "COMMA")
				{
					idList();
				}
				if (tV[index].type == "RIGHT_PAREN")
				{
					index++;
				}
				else
				{
					throw tV[index];
				}
			}
			else
			{
				throw tV[index];
			}
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}

}

void  DatalogParser::predicate() 
{
	if (tV[index].type == "ID")
	{
		pred = Predicate(tV[index].value);
		index++;
		if (tV[index].type == "LEFT_PAREN")
		{
			index++;
			if (tV[index].type == "STRING" || tV[index].type == "ID" || tV[index].type == "LEFT_PAREN")
			{
				parameter();

				if (tV[index].type == "COMMA")
				{
					parameterList();
				}
				if (tV[index].type == "RIGHT_PAREN")
				{
					index++;
				}
				else
				{
					throw tV[index];
				}
			}
			else
			{
				throw tV[index];
			}
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}
	rul.pushPredicate(pred);
}

void  DatalogParser::predicateList()
{
	if (tV[index].type == "COMMA")
	{
		index++;

		if (tV[index].type == "ID")
		{
			predicate();

			if (tV[index].type == "COMMA")
			{
				predicateList();
			}
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}
}

void DatalogParser::parameter()
{
	if (tV[index].type == "STRING")
	{
		pred.pushParameter(Parameter(tV[index].type, tV[index].value));
		index++;	
	}
	else if(tV[index].type == "ID")
	{
		pred.pushParameter(Parameter(tV[index].type, tV[index].value));
		index++;
	}
	else
	{
		expression();
	}
}

void DatalogParser::parameterList()
{
	if (tV[index].type == "COMMA")
	{
		index++;

		if (tV[index].type == "ID" || tV[index].type == "STRING" || tV[index].type == "LEFT_PAREN")
		{
			parameter();

			if (tV[index].type == "COMMA")
			{
				parameterList();
			}
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}
}

void DatalogParser::expression()
{
	checkMatch(tV[index].type, "LEFT_PAREN");
	
		index++;

		if (tV[index].type == "LEFT_PAREN" || tV[index].type == "STRING" || tV[index].type == "ID" )
		{
			parameter();

			checkOperator(tV[index].type);
			
				if (tV[index].type == "LEFT_PAREN" || tV[index].type == "STRING" || tV[index].type == "ID")
				{
					parameter();
				}
				else
				{
					throw tV[index];
				}
		}
		else
		{
			throw tV[index];
		}

}

bool DatalogParser::checkOperator(string vectorType)
{
	if (tV[index].type == "ADD" || tV[index].type == "MULTIPLY")
	{
		index++;
		return true;
	}
	else
	{
		throw tV[index];
		return false;
	}
}

void DatalogParser::checkLineFour()
{

	// check for SCHEMES match
	if (tV[index].type == "QUERIES")
		index++;
	else
		throw tV[index];

	// check for COLON match
	if (tV[index].type == "COLON")
		index++;
	else
		throw tV[index];

	// check for scheme match
	if (tV[index].type == "ID")
	{
		query();
	}
	else
	{
		throw tV[index];
	}
	

	// check for schemeList match
	queryList();
}

void DatalogParser::query()
{
	if (tV[index].type == "ID")
	{
		pred = Predicate(tV[index].value);
		predicate();
		if (tV[index].type == "Q_MARK")
		{
			index++;
		}
		else
		{
			throw tV[index];
		}
	}
	else
	{
		throw tV[index];
	}

	datalogProgram.pushQueries(pred);
}

void DatalogParser::queryList()
{
	if (tV[index].type == "ID")
	{
		query();
		queryList();
	}

}

bool DatalogParser::checkMatch(string vectorType, string Type)
{
	if (vectorType == Type)
		return true;
	else
	{
		throw tV[index];
	}

	return false;
}



DatalogProgram DatalogParser::getData()
{
	return datalogProgram;
}

string DatalogParser::getDomains()
{
	stringstream ss;
	ss << "Domains(" << Domains.size() << ")" << endl;
	for (int i = 0; i < Domains.size(); i++)
	{
		ss << "  " << Domains[i] << endl;
	}

	return ss.str();
}


//./lab2 info.txt ouput.txt ....diff out.txt. expected.txt