cmake_minimum_required(VERSION 2.8)

project(json)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++0x -O3")

find_package(BISON REQUIRED)
set(BISON_OUTPUT ${CMAKE_SOURCE_DIR}/json.tab.c)
if(BISON_FOUND)
	add_custom_command(
		OUTPUT ${BISON_OUTPUT}
		COMMAND ${BISON_EXECUTABLE} -d
			${CMAKE_SOURCE_DIR}/json.y
		COMMENT "Generating json.tab.h, json.tab.c (parser)"
	)
endif(BISON_FOUND)

find_package(FLEX REQUIRED)
set(FLEX_OUTPUT ${CMAKE_SOURCE_DIR}/lex.yy.c)
if(FLEX_FOUND)
	add_custom_command(
		OUTPUT ${FLEX_OUTPUT}
		COMMAND ${FLEX_EXECUTABLE}
			${CMAKE_SOURCE_DIR}/json.l
		COMMENT "Generating lex.yy.c (lexer)"
	)
endif(FLEX_FOUND)

add_library(json json_st.cc json.tab.c lex.yy.c)
add_executable(test test.cc)
target_link_libraries(test json) 



