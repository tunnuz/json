#include <codecvt>
#include <locale>
#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "code_point_to_utf8.hh"

using JSON::HELPER::code_point_to_utf8;

class CodePoint2Utf8Test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CodePoint2Utf8Test);

    CPPUNIT_TEST(test_conversion);

	CPPUNIT_TEST_SUITE_END();
    
    void test_conversion()
    {
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> std_multi_byte_converter;

        for (char16_t code_point { 0x0000 }; code_point <= 0xD7FF; ++code_point) {
            CPPUNIT_ASSERT_EQUAL(
                    std_multi_byte_converter.to_bytes(code_point), code_point_to_utf8(code_point));
        }

        // skipping surrogates

        for (char16_t code_point { 0xE000 }; code_point <= 0xFFFFu; ++code_point) {
            CPPUNIT_ASSERT_EQUAL(
                    std_multi_byte_converter.to_bytes(code_point), code_point_to_utf8(code_point));
            if (code_point == 0xFFFF) break;
        }
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION(CodePoint2Utf8Test);

