#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <functional>

enum class parser_error
{
    file_error
};

class pascal
{
public:
    pascal() = default;
    ~pascal() = default;
    void parser(const char *fpath);
protected:
    std::string get_string_no_comment(std::ifstream & in);
    std::string get_string_skip_space(const std::string & src); 
    std::list<std::string> get_list(const std::string & src);
private:
    void LOG_OUT(const char * msg, std::list<std::string>& l);
};