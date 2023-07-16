#include<iostream>
#include "../inc/parser.hpp"
#include "../inc/error.hpp"

void test(){ std::cout<<"Test3\n"; }

Parser::Parser(std::string file_path):c('@'), delimiter(false), not_double_delim(false)
{
	if((fp = fopen(file_path.c_str(), "r")) == nullptr) std::cout << ERR_FILE_NOT_FOUND;
}
Parser::~Parser()
{
	if(fp != nullptr) { fclose(fp); fp = nullptr; }
}

char * Parser::getWord()
{
	if (c == EOF ) return nullptr;
	int i = 0;
	if(delimiter) {
		delimiter = false;
		return buff2;
	}
	if(not_double_delim){
		not_double_delim = false;
		goto SKIP_GET_CHAR;
	}
	while ((c = getc(fp)) != EOF)
	{
SKIP_GET_CHAR:
		if(is_delim(c)) { 
			delimiter = true;
			break;
		}
		else {
			buff[i++] = c;
		}
	}
	buff[i] = '\0';
	return i==0?getWord():buff; 
}
bool Parser::is_delim(char) { return false; }
bool Parser::is_open() { return fp==nullptr?false:true; }

Pascal_Parser::Pascal_Parser(std::string file_path):Parser(file_path) { }
bool Pascal_Parser::is_delim(char ch)
{
#define ELSE_IF_DOUBLE_DELIM(first, second) \
	else if (first) {\
		delimiter = true;\
		buff2[0] = ch;\
		c = getc(fp); \
			if (second) { \
				buff2[1] = c; \
				buff2[2] = '\0';\
			}\
			else { \
				not_double_delim = true; \
				buff2[1] = '\0';\
			}\
		return true;\
	}
	
	if (ch == ';' || ch == ' ' || ch == '\n' || ch == '\t' || ch == '\0' || ch == '=' || 
		ch == '\'') {
		delimiter = true;
		buff2[0] = ch; buff2[1] = '\0';
		return true;
	}
	ELSE_IF_DOUBLE_DELIM(ch == ':' || ch == '+' || ch == '-' || ch == '>', c == '=')
	ELSE_IF_DOUBLE_DELIM(ch == '*', c == '=' || c == ')')
	ELSE_IF_DOUBLE_DELIM(ch == '/', c == '=' || c == '/')
	ELSE_IF_DOUBLE_DELIM(ch == '<', c == '=' || c == '>')
	ELSE_IF_DOUBLE_DELIM(ch == '(', c == '*')
	else
		return false;
#undef ELSE_IF_DOUBLE_DELIM
}
