#include <cppunit/extensions/HelperMacros.h>

#include "unescape.hh"

using JSON::HELPER::unescape;

class UnescapeUnicodeEscapeSequenceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(UnescapeUnicodeEscapeSequenceTest);

    CPPUNIT_TEST(test_basic_latin);
    CPPUNIT_TEST(test_latin_1_supplement);
    CPPUNIT_TEST(test_latin_extended_a);
    CPPUNIT_TEST(test_myanmar);
    CPPUNIT_TEST(test_phonetic_extensions);
    CPPUNIT_TEST(test_greek_extended);
    CPPUNIT_TEST(test_hiragana);
    CPPUNIT_TEST(test_cjk);

    CPPUNIT_TEST(test_is_part_of_unescape);

    CPPUNIT_TEST_SUITE_END();

    void test_basic_latin();
    void test_latin_1_supplement();
    void test_latin_extended_a();
    void test_myanmar();
    void test_phonetic_extensions();
    void test_greek_extended();
    void test_hiragana();
    void test_cjk();

    void test_is_part_of_unescape();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnescapeUnicodeEscapeSequenceTest);

// cf. http://www.ecma-international.org/publications/files/ecma-st/ECMA-262.pdf, 15.12.1.1

void UnescapeUnicodeEscapeSequenceTest::test_basic_latin()
{
    std::string s { u8R"(\u0041\u0042\u0043)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"ABC"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_latin_1_supplement()
{
    std::string s { u8R"(\u00A5\u00A3)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u00A5\u00A3"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_latin_extended_a()
{
    std::string s { u8R"(\u0160\u0161)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u0160\u0161"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_myanmar()
{
    std::string s { u8R"(\u1042\u1043)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u1042\u1043"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_phonetic_extensions()
{
    std::string s { u8R"(\u1D19\u1D1A)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u1D19\u1D1A"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_greek_extended()
{
    std::string s { u8R"(\u1f63\u1f64)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u1f63\u1f64"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_hiragana()
{
    std::string s { u8R"(\u3042\u3044\u3046\u3048\u304A)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u3042\u3044\u3046\u3048\u304A"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_cjk()
{
    std::string s { u8R"(\u4E0A\u4E0B)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u4E0A\u4E0B"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::test_is_part_of_unescape()
{
    std::string s { u8R"(Why do we fall, \u00A5\u00A3?)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"Why do we fall, \u00A5\u00A3?"}, s);
}

