#include <cppunit/extensions/HelperMacros.h>

#include "unescape.hh"

using JSON::HELPER::unescape;

class UnescapeEscapeCharacterTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(UnescapeEscapeCharacterTest);

    CPPUNIT_TEST(test_empty_input);
    CPPUNIT_TEST(test_input_with_no_occurrances);
    CPPUNIT_TEST(test_occurrance_at_begin);
    CPPUNIT_TEST(test_occurrance_middle);
    CPPUNIT_TEST(test_occurrance_at_end);
    CPPUNIT_TEST(test_multiple_occurrances_contiguous);
    CPPUNIT_TEST(test_multiple_occurrances_spaced);
    CPPUNIT_TEST(test_with_partial_match);

    CPPUNIT_TEST_SUITE_END();
    
    void test_empty_input();
    void test_input_with_no_occurrances();
    void test_occurrance_at_begin();
    void test_occurrance_middle();
    void test_occurrance_at_end();
    void test_multiple_occurrances_contiguous();
    void test_multiple_occurrances_spaced();
    void test_with_partial_match();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnescapeEscapeCharacterTest);

void UnescapeEscapeCharacterTest::test_empty_input()
{
    std::string s { R"()" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{""}, s);
}

void UnescapeEscapeCharacterTest::test_input_with_no_occurrances()
{
    std::string s { R"(nothing to replace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"nothing to replace"}, s);
}

void UnescapeEscapeCharacterTest::test_occurrance_at_begin()
{
    std::string s { R"(\tto replace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"\tto replace"}, s);
}

void UnescapeEscapeCharacterTest::test_occurrance_middle()
{
    std::string s { R"(to \treplace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to \treplace"}, s);
}

void UnescapeEscapeCharacterTest::test_occurrance_at_end()
{
    std::string s { R"(to replace\t)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to replace\t"}, s);
}

void UnescapeEscapeCharacterTest::test_multiple_occurrances_contiguous()
{
    std::string s { R"(to \t\treplace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to \t\treplace"}, s);
}

void UnescapeEscapeCharacterTest::test_multiple_occurrances_spaced()
{
    std::string s { R"(to \tre\tplace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to \tre\tplace"}, s);
}

void UnescapeEscapeCharacterTest::test_with_partial_match()
{
    std::string s { R"(to \eplace)" };
    CPPUNIT_ASSERT_THROW(unescape(s), std::runtime_error);
}

