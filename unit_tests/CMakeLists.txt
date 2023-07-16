cmake_minimum_required(VERSION 3.10)
project(UNIT)
find_package( Boost 1.7
	REQUIRED COMPONENTS unit_test_framework
)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS} )
	add_executable(unit_parser unit_parser.cpp ../inc/parser.hpp ../src/parser.cpp)
	target_link_libraries(unit_parser ${Boost_LIBRARIES})
	install( 
	 TARGETS unit_parser
	 RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}
	 )
endif()

