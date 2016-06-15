include_directories(${PROJECT_INCLUDE_DIR})

find_package(BISON 2.7 REQUIRED)
if(BISON_FOUND)
	set(BISON_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/json.tab.cc)
	set(BISON_DEFINES ${PROJECT_INCLUDE_DIR}/json/json.tab.hh)
	add_custom_command(
		OUTPUT ${BISON_OUTPUT}
		COMMAND ${BISON_EXECUTABLE}
			--defines=${BISON_DEFINES}
			--output=${BISON_OUTPUT}
			${CMAKE_CURRENT_SOURCE_DIR}/json.y
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/json.y
		COMMENT "Generating json.tab.hh, json.tab.cc (parser)"
	)
endif(BISON_FOUND)

find_package(FLEX 2.5 REQUIRED)
if(FLEX_FOUND)
	set(FLEX_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.cc)
	add_custom_command(
		OUTPUT ${FLEX_OUTPUT}
		COMMAND ${FLEX_EXECUTABLE}
			--outfile=${FLEX_OUTPUT}
			${CMAKE_CURRENT_SOURCE_DIR}/json.l
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/json.l
		COMMENT "Generating lex.yy.cc (lexer)"
	)
endif(FLEX_FOUND)

add_library(json json_st.cc ${BISON_OUTPUT} ${FLEX_OUTPUT})

add_subdirectory(test)
