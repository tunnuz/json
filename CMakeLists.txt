cmake_minimum_required(VERSION 2.8)

project(json)

set(CMAKE_CXX_FLAGS "-O3")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(BISON REQUIRED)
set(BISON_OUTPUT ${json_BINARY_DIR}/json.tab.cc)
set(BISON_DEFINES ${json_BINARY_DIR}/json.tab.hh)
include_directories(${json_SOURCE_DIR} ${json_BINARY_DIR})
if(BISON_FOUND)
	add_custom_command(
		OUTPUT ${BISON_OUTPUT}
		COMMAND ${BISON_EXECUTABLE} 
			--defines=${BISON_DEFINES}
			--output=${BISON_OUTPUT}
			${json_SOURCE_DIR}/json.y
		DEPENDS ${json_SOURCE_DIR}/json.y
		COMMENT "Generating json.tab.hh, json.tab.cc (parser)"
	)
endif(BISON_FOUND)

find_package(FLEX REQUIRED)
set(FLEX_OUTPUT ${json_BINARY_DIR}/lex.yy.cc)
if(FLEX_FOUND)
	add_custom_command(
		OUTPUT ${FLEX_OUTPUT}
		COMMAND ${FLEX_EXECUTABLE}
			--outfile=${FLEX_OUTPUT}
			${json_SOURCE_DIR}/json.l
		DEPENDS ${json_SOURCE_DIR}/json.l
		COMMENT "Generating lex.yy.cc (lexer)"
	)
endif(FLEX_FOUND)

add_library(json json_st.cc ${BISON_OUTPUT} ${FLEX_OUTPUT})
add_executable(test test.cc)
target_link_libraries(test json) 



