#pragma once
#include <cstdio>

class Parser
{
	friend class Pascal_Parser;
	int c;
	char buff[128];
	char buff2[4];
	bool delimiter;
	bool not_double_delim;
	FILE *fp;

private:	
	virtual bool is_delim(char);
	
public:
	Parser(std::string);
	char * getWord();
	bool is_open();
	~Parser();
};

class Pascal_Parser : public Parser
{
private:
	bool is_delim(char);
public:
	Pascal_Parser(std::string);
};
