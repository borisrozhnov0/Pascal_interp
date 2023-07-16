cmake_minimum_required(VERSION 3.10)
project(Compil)
add_library(parser inc/parser.hpp src/parser.cpp)

add_executable(start main.cpp )
target_link_libraries(start parser)
install( 
	 TARGETS start 
	 RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
	 )
install(
	TARGETS parser
	DESTINATION ${CMAKE_SOURCE_DIR}/lib
	)
