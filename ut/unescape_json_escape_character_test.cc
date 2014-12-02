#include <cppunit/extensions/HelperMacros.h>

#include "unescape.hh"

using JSON::HELPER::unescape;

class UnescapeJsonEscapeCharacterTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(UnescapeJsonEscapeCharacterTest);

    CPPUNIT_TEST(test_quotation_mark);
    CPPUNIT_TEST(test_reverse_solidus);
    CPPUNIT_TEST(test_solidus);
    CPPUNIT_TEST(test_backspace);
    CPPUNIT_TEST(test_formfeed);
    CPPUNIT_TEST(test_newline);
    CPPUNIT_TEST(test_carriage_return);
    CPPUNIT_TEST(test_horizontal_tab);

    CPPUNIT_TEST(test_replacement_is_part_of_another_escape);
    CPPUNIT_TEST(test_replacement_is_part_of_another_escape2);

    CPPUNIT_TEST_SUITE_END();
    
    void test_quotation_mark();
    void test_reverse_solidus();
    void test_solidus();
    void test_backspace();
    void test_formfeed();
    void test_newline();
    void test_carriage_return();
    void test_horizontal_tab();

    void test_replacement_is_part_of_another_escape();
    void test_replacement_is_part_of_another_escape2();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnescapeJsonEscapeCharacterTest);

// cf. http://www.ecma-international.org/publications/files/ecma-st/ECMA-262.pdf, 15.12.1.1

void UnescapeJsonEscapeCharacterTest::test_quotation_mark()
{
    std::string s { R"(\")" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\"'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_reverse_solidus()
{
    std::string s { R"(\\)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\\'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_solidus()
{
    std::string s { R"(\/)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'/'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_backspace()
{
    std::string s { R"(\b)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\b'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_formfeed()
{
    std::string s { R"(\f)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\f'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_newline()
{
    std::string s { R"(\n)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\n'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_carriage_return()
{
    std::string s { R"(\r)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\r'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_horizontal_tab()
{
    std::string s { R"(\t)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\t'}, s);
}

void UnescapeJsonEscapeCharacterTest::test_replacement_is_part_of_another_escape()
{
    std::string s { R"(\\\/)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"\\/"}, s);
}

void UnescapeJsonEscapeCharacterTest::test_replacement_is_part_of_another_escape2()
{
    std::string s { R"(\\\\t)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"\\\\t"}, s);
}

