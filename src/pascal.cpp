#include "pascal.h"

void pascal::parser(const char *fpath)
{
    std::ifstream in;
    in.open(fpath);
    if(!in.is_open()) throw parser_error::file_error;

    std::string s;
    std::list<std::string> l;

    s = std::move(get_string_no_comment(in));
    s = get_string_skip_space(s);
    l = get_list(s);
    LOG_OUT("File parse success.", l);
    

    in.close();
}

std::string  pascal::get_string_no_comment(std::ifstream & in)
{
    std::string str;
    enum e{def, start_c1, start_c2, end_c1, start_l, end_l}e;
    char c;
    while(!in.eof())
    {
        in.get(c);
        switch(e)
        {
        case def:
            if(c == '(') e = start_c1;
            else if(c == '/') e = start_l;
            else str += c;
            break;
        case start_c1:
            if(c == '*') e = start_c2;
            else
            {
                e = def;
                str += '(';
                str += c;
            }
            break;
        case start_c2:
            if (c == '*') e = end_l;
            break;
        case end_c1:
            if (c == ')') e = def;
            break;
        case start_l:
            if(c == '/') e = end_l;
            else 
            {
                e = def;
                str += '/';
                str += c; 
            }
            break;
        case end_l:
            if(c == '\n') 
            {
                e = def;
                str += c;
            }
            break;
        }
    }
    return str;
}

std::string pascal::get_string_skip_space(const std::string & src)
{
    enum e {def, skip, s}e = def;
    std::string str;
    for(auto c : src)
    {
        switch (e)
        {
        case def:
            if(c == '\'')
            {
                
                e = s;
                str += c;
            }
            else if(c == ' ' || c == '\t' || c == '\n')
            {
                
                e = skip;
                str += ' ';            
            }
            else str += c;
            break;

        case skip:
            if(!(c == ' ' || c == '\t' || c == '\n'))
            {
                e = def;
                str += c;
            }
            break;

        case s:
            if(c == '\'') e = def;
            str += c;
            break;
        }
    }
    return str;
}

std::list<std::string> pascal::get_list(const std::string & src)
{
    auto __cmp = [](const char * src, const std::list<std::string> &l)->const char*{
        for(const std::string & s : l) 
            for(auto pt1 = src, pt2 = s.c_str(); *pt1 != '\0'; pt1++, pt2++) 
                if(*pt2 == '\0') return s.c_str();
                else if(*pt1 != *pt2) break;;
        return NULL;
    };
    std::list<std::string> ret;
    std::list<std::string> _SKIP = {" "};
    std::list<std::string> _SEP = {
        "[", "]", "(", ")", ":", ";", ",",
        ":=", "+=", "-=", "*=", "/=",
        "+", "-", "*", "/"
    };
    _SEP.sort([](const std::string & a, const std::string & b){return a.length() > b.length();});  

    std::string buf;
    const char *tmp_pt;
    const char *pt = src.c_str();
    while(*pt != '\0')
    {
        if(*pt == '\'') 
        {
            if(!buf.empty()) ret.push_back(buf);
            buf.clear();
            buf += *pt;
            while (*++pt!='\'') buf += *pt;
            buf += *pt;
            pt++;
        }
        else if((tmp_pt = __cmp(pt, _SEP)) != NULL)
        {
            if(!buf.empty()) ret.push_back(buf);
            buf.clear();  
            ret.push_back(tmp_pt);
            pt += ret.back().length();
        }
        else if (*pt == ' ')
        {
            if(!buf.empty()) ret.push_back(buf);
            buf.clear(); 
            pt++;
        }
        else buf += *pt++; 
    }
    if(!buf.empty()) ret.push_back(buf);    
    
    return ret;
}

void pascal::LOG_OUT(const char * msg, std::list<std::string>& l)
{
    std::cout << msg << std::endl;
    for(auto & str : l) std::cout << str << " ";
    std::cout << std::endl;
}