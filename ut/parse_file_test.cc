#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "json.hh"
#include "json_st.hh"

class ParseFileTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(ParseFileTest);

    CPPUNIT_TEST(test_string);
	CPPUNIT_TEST(test_number);
    CPPUNIT_TEST(test_bool);
    CPPUNIT_TEST(test_null);

	CPPUNIT_TEST_SUITE_END();
    
    void test_string();
    void test_number();
    void test_bool();
    void test_null();

};

CPPUNIT_TEST_SUITE_REGISTRATION(ParseFileTest);

void ParseFileTest::test_string()
{
    const std::string file_name { std::string{UT_JSON_PATH} + "test_string.json" };

    const JSON::Value v { parse_file(file_name.c_str()) };

    CPPUNIT_ASSERT_EQUAL(std::string{}, v["empty"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{"c"}, v["one char"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{"a lot of characters"}, v["chars"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u00D6\u00F6"}, v["unicode"].as_string());
    CPPUNIT_ASSERT_EQUAL(
            std::string{u8"\"\\/\b\f\n\r\tmit sch\u00F6nen Gr\u00FC\u00DFen aus \u00D6sterreich"},
            v["all kinds of escapes"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\\u0065"}, v["unicode encoded backslash plus uXXXX"].as_string());
}

void ParseFileTest::test_number()
{
    const std::string file_name { std::string{UT_JSON_PATH} + "test_number.json" };

    const JSON::Value v { parse_file(file_name.c_str()) };

    // cf. grammar http://json.org

    CPPUNIT_ASSERT_EQUAL(3ll, v["int one digit"].as_int());
    CPPUNIT_ASSERT_EQUAL(123ll, v["int digits"].as_int());
    CPPUNIT_ASSERT_EQUAL(-9ll, v["int one digit negative"].as_int());
    CPPUNIT_ASSERT_EQUAL(-421ll, v["int digits negative"].as_int());

    CPPUNIT_ASSERT_DOUBLES_EQUAL(123.4l, v["int frac positive"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-456.789l, v["int frac negative"].as_float(), 1e-5);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e0l, v["int exp e"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e6l, v["int exp e+"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e-7l, v["int exp e-"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e8l, v["int exp E"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e9l, v["int exp E+"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e-1l, v["int exp E-"].as_float(), 1e-5);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(-123.4e-4l, v["int frac exp"].as_float(), 1e-5);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0l, v["number zero float"].as_float(), 1e-5);
    CPPUNIT_ASSERT_EQUAL(0ll, v["number zero integer"].as_int());

    CPPUNIT_ASSERT_EQUAL(9223372036854775807ll, v["long long max"].as_int());
    CPPUNIT_ASSERT_EQUAL(-9223372036854775807ll, v["long long min"].as_int());
}

void ParseFileTest::test_bool()
{
    const std::string file_name { std::string{UT_JSON_PATH} + "test_bool.json" };

    const JSON::Value v { parse_file(file_name.c_str()) };

    CPPUNIT_ASSERT(v["true"]);
    CPPUNIT_ASSERT(not v["false"]);
}

void ParseFileTest::test_null()
{
    const std::string file_name { std::string{UT_JSON_PATH} + "test_null.json" };

    const JSON::Value v { parse_file(file_name.c_str()) };

    CPPUNIT_ASSERT_EQUAL(JSON::NIL, v["null"].type());
}

