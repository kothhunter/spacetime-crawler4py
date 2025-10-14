#include <gtest/gtest.h>

#include "string.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("boo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "boo"), result);
    EXPECT_STREQ(result, "boo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
    char result[10] = "initial";
    EXPECT_EQ(String::strncpy(result, "boo", 3), result); 
    EXPECT_STREQ(result, "boo");

    EXPECT_EQ(String::strncpy(result, "bar", 2), result); 
    EXPECT_STREQ(result, "ba");

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");

    EXPECT_EQ(String::strncpy(result, "overflow", 5), result);
    EXPECT_STREQ(result, "overf");
}

TEST(StringFunction, strcat) {
    char result[10] = "foo";
    EXPECT_EQ(String::strcat(result, "bar"), result);
    EXPECT_STREQ(result, "foobar");

    EXPECT_EQ(String::strcat(result, ""), result); 
    EXPECT_STREQ(result, "foobar");

    char result2[10] = "";
    EXPECT_EQ(String::strcat(result2, "hello"), result2);
    EXPECT_STREQ(result2, "hello");
}

TEST(StringFunction, strncat) {
    char result[10] = "foo";
    EXPECT_EQ(String::strncat(result, "bar", 3), result);
    EXPECT_STREQ(result, "foobar");

    EXPECT_EQ(String::strncat(result, "xyz", 0), result); 
    EXPECT_STREQ(result, "foobar");

    char result2[10] = "";
    EXPECT_EQ(String::strncat(result2, "hello", 2), result2); 
    EXPECT_STREQ(result2, "he");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("", ""), 0); 
    EXPECT_EQ(String::strcmp("foo", "foo"), 0); 
    EXPECT_LT(String::strcmp("foo", "foobar"), 0); 
    EXPECT_GT(String::strcmp("foobar", "foo"), 0); 
    EXPECT_LT(String::strcmp("apple", "banana"), 0); 
    EXPECT_GT(String::strcmp("banana", "apple"), 0); 
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("", "", 1), 0);
    EXPECT_EQ(String::strncmp("foo", "foo", 3), 0);
    EXPECT_EQ(String::strncmp("foo", "foobar", 3), 0);
    EXPECT_LT(String::strncmp("apple", "banana", 5), 0); 
    EXPECT_GT(String::strncmp("banana", "apple", 5), 0); 
    EXPECT_EQ(String::strncmp("foo", "bar", 0), 0); 
}

TEST(StringFunction, reverse_cpy) {
    char result[10];
    String::reverse_cpy(result, "foo"); 
    EXPECT_STREQ(result, "oof");

    String::reverse_cpy(result, "");
    EXPECT_STREQ(result, "");

    String::reverse_cpy(result, "hello");
    EXPECT_STREQ(result, "olleh");
}

TEST(StringFunction, strchr) {
    EXPECT_EQ(String::strchr("foo", 'f'), "foo");
    EXPECT_EQ(String::strchr("foo", 'o'), "oo"); 
    EXPECT_EQ(String::strchr("foo", 'x'), nullptr); 
    EXPECT_EQ(String::strchr("", 'x'), nullptr);
}

TEST(StringFunction, strstr) {
    EXPECT_EQ(String::strchr("foobar", "foo"), "foobar");
    EXPECT_EQ(String::strchr("foobar", "bar"), "bar"); 
    EXPECT_EQ(String::strchr("foobar", "oba"), "obar");
    EXPECT_EQ(String::strchr("foobar", "xyz"), nullptr); 
    EXPECT_EQ(String::strchr("", "foo"), nullptr); 
}
