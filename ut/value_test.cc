#include <limits>

#include <cppunit/extensions/HelperMacros.h>

#include "json_st.hh"

class ValueTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ValueTest);

    CPPUNIT_TEST(test_long_long_int);
    CPPUNIT_TEST(test_long_int);
    CPPUNIT_TEST(test_int);

    CPPUNIT_TEST(test_integer_range_min);
    CPPUNIT_TEST(test_integer_range_max);

    CPPUNIT_TEST(test_long_double);
    CPPUNIT_TEST(test_double);

    CPPUNIT_TEST(test_floating_range_min);
    CPPUNIT_TEST(test_floating_range_max);

    CPPUNIT_TEST(test_bool_true);
    CPPUNIT_TEST(test_bool_false);

    CPPUNIT_TEST(test_string_from_character_array);
    CPPUNIT_TEST(test_string_from_stl);

    CPPUNIT_TEST_SUITE_END();

    void test_long_long_int();
    void test_long_int();
    void test_int();

    void test_integer_range_min();
    void test_integer_range_max();

    void test_long_double();
    void test_double();

    void test_floating_range_min();
    void test_floating_range_max();

    void test_bool_true();
    void test_bool_false();

    void test_string_from_character_array();
    void test_string_from_stl();
    
};

CPPUNIT_TEST_SUITE_REGISTRATION(ValueTest);

void ValueTest::test_long_long_int()
{
    constexpr long long content { 1ll };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_int());
    CPPUNIT_ASSERT_EQUAL(content, static_cast<long long>(v));
}

void ValueTest::test_long_int()
{
    constexpr long content { 1l };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), v.as_int());
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), static_cast<long long>(v));
}

void ValueTest::test_int()
{
    constexpr int content { 1 };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), v.as_int());
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), static_cast<long long>(v));
}

void ValueTest::test_integer_range_min()
{
    constexpr long long content { std::numeric_limits<long long>::min() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_int());
}

void ValueTest::test_integer_range_max()
{
    constexpr long long content { std::numeric_limits<long long>::max() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_int());
}

void ValueTest::test_long_double()
{
    constexpr long double content { 0.333333333333333333l };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_float());
    CPPUNIT_ASSERT_EQUAL(content, static_cast<long double>(v));
}

void ValueTest::test_double()
{
    constexpr double content { -0.3 };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(static_cast<long double>(content), v.as_float());
    CPPUNIT_ASSERT_EQUAL(static_cast<long double>(content), static_cast<long double>(v));
}

void ValueTest::test_floating_range_min()
{
    constexpr long double content { std::numeric_limits<long double>::min() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_float());
}

void ValueTest::test_floating_range_max()
{
    constexpr long double content { std::numeric_limits<long double>::max() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_float());
}

void ValueTest::test_bool_true()
{
    const JSON::Value v { true };
    CPPUNIT_ASSERT(v);
    CPPUNIT_ASSERT(v.as_bool());
}

void ValueTest::test_bool_false()
{
    const JSON::Value v { false };
    CPPUNIT_ASSERT(not v);
    CPPUNIT_ASSERT(not v.as_bool());
}

void ValueTest::test_string_from_character_array()
{
    const char* content { "json++" };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(std::string{content}, v.as_string());
}

void ValueTest::test_string_from_stl()
{
    const std::string content { "json++" };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_string());
}

