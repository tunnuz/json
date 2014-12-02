find_path(CPPUNIT_INCLUDE_DIR cppunit/TestRunner.h)
find_library(CPPUNIT_LIBRARY cppunit)

set (TEST_SOURCES
	unescape_escape_character_test.cc
	unescape_json_escape_character_test.cc
	unescape_unicode_escape_sequence_test.cc
	value_test.cc
	parse_file_test.cc
)

# check if we can build the tests for our own UCS-16 to UTF-8 conversion
include(CheckCXXSourceCompiles)
CHECK_CXX_SOURCE_COMPILES(
	"#include <codecvt>\n #include <locale>\n
	int main() { std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> multi_byte_converter; }"
	HAS_CODECVT_UTF8)

if (HAS_CODECVT_UTF8)
	set (TEST_SOURCES ${TEST_SOURCES} code_point_to_utf8_test.cc)
else()
	message(STATUS "Not building test for UCS-16 to UTF-8 conversion")
endif()

add_executable(ut.json ${TEST_SOURCES} test_main.cc)
include_directories(${CPPUNIT_INCLUDE_DIR})
target_link_libraries(ut.json json ${CPPUNIT_LIBRARY})

set(ut_json_path ${CMAKE_SOURCE_DIR}/ut/testdata/)
add_definitions(-DUT_JSON_PATH=\"${ut_json_path}\")
