
#include <iostream>
#include <string>
#include "../inc/parser.hpp"
#include "../inc/error.hpp"

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <vector>

//____________________________________________________________________________//
BOOST_AUTO_TEST_SUITE( Pascal_parser )

BOOST_AUTO_TEST_CASE( simple_test1 )
{
   	Pascal_Parser pp("data/test1.txt");
    char * word = nullptr; 
    int i = 0;
    std::vector<std::string> v1, v2({"this"," ","is"," ","simple"," ","test",";","\n"}); // this is simple test;\n
    BOOST_REQUIRE( true == pp.is_open() );
  	while((word = pp.getWord())!= nullptr) v1.push_back(word); 
  	BOOST_CHECK( v1 == v2 );
}

BOOST_AUTO_TEST_CASE( simple_test2 )
{
    Pascal_Parser pp("data/test2.txt");
    char * word = nullptr; 
    int i = 0;
    std::vector<std::string> v1, v2({"=","=","+=","+","+","/","*","+","*)","//","\n"}); // ==+=++/*+*)//\n
    BOOST_REQUIRE( true == pp.is_open() );
  	while((word = pp.getWord())!= nullptr) v1.push_back(word); 
  	BOOST_CHECK( v1 == v2 );
  	if(v1 != v2) {
  		for(auto a1 = v1.begin(), a2 = v2.begin(); a1 != v1.end(); a1++,a2++)
  			std::cout<< *a1 << " | "<<*a2<<std::endl;
  	}
}
BOOST_AUTO_TEST_CASE( simple_test3 )
{
    Pascal_Parser pp("data/test3.txt");
    char * word = nullptr; 
    int i = 0;
    std::vector<std::string> v1, v2({"(*", " ", "*", "*)", "/", "\'", "<>", "<","<=", ":", ":=","\n"}); //(* **)/'<><<=::=\n
    BOOST_REQUIRE( true == pp.is_open() );
  	while((word = pp.getWord())!= nullptr) v1.push_back(word); 
  	BOOST_CHECK( v1 == v2 );
  	if(v1 != v2) {
  		for(auto a1 = v1.begin(), a2 = v2.begin(); a1 != v1.end(); a1++,a2++)
  			std::cout<< *a1 << " | "<<*a2<<std::endl;
  	}
}

BOOST_AUTO_TEST_SUITE_END()
//____________________________________________________________________________//


