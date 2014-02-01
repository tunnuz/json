cmake_minimum_required(VERSION 2.8)

project(json)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

find_package(BISON REQUIRED)
set(BISON_OUTPUT json.tab.cc)
set(BISON_DEFINES json.tab.hh)
if(BISON_FOUND)
	add_custom_command(
		OUTPUT ${BISON_OUTPUT}
		COMMAND ${BISON_EXECUTABLE} 
			--defines=${BISON_DEFINES}
			--output=${BISON_OUTPUT}
			json.y
		COMMENT "Generating json.tab.hh, json.tab.cc (parser)"
	)
endif(BISON_FOUND)

find_package(FLEX REQUIRED)
set(FLEX_OUTPUT lex.yy.cc)
if(FLEX_FOUND)
	add_custom_command(
		OUTPUT ${FLEX_OUTPUT}
		COMMAND ${FLEX_EXECUTABLE}
			--outfile=${FLEX_OUTPUT}
			json.l
		COMMENT "Generating lex.yy.cc (lexer)"
	)
endif(FLEX_FOUND)

add_library(json json_st.cc json.tab.cc lex.yy.cc)
add_executable(test test.cc)
target_link_libraries(test json) 



