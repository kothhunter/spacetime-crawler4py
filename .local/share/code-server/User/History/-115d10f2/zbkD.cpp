#include <gtest/gtest.h>

#include "string.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strncpy) {
    char result[10] = "initial";
    EXPECT_EQ(String::strncpy(result, "boo", 3), result); 
    EXPECT_STREQ(result, "boo");

    EXPECT_EQ(String::strncpy(result, "car", 2), result); 
    EXPECT_STREQ(result, "ca");

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");

    EXPECT_EQ(String::strncpy(result, "overflow", 5), result);
    EXPECT_STREQ(result, "overf");
}

TEST(StringFunction, strcat) {
    char result[10] = "boo";
    EXPECT_EQ(String::strcat(result, "car"), result);
    EXPECT_STREQ(result, "boocar");

    EXPECT_EQ(String::strcat(result, ""), result); 
    EXPECT_STREQ(result, "boocar");

    char result2[10] = "";
    EXPECT_EQ(String::strcat(result2, "hello"), result2);
    EXPECT_STREQ(result2, "hello");
}

TEST(StringFunction, strncat) {
    char result[10] = "boo";
    EXPECT_EQ(String::strncat(result, "car", 3), result);
    EXPECT_STREQ(result, "boocar");

    EXPECT_EQ(String::strncat(result, "xyz", 0), result); 
    EXPECT_STREQ(result, "boocar");

    char result2[10] = "";
    EXPECT_EQ(String::strncat(result2, "hello", 2), result2); 
    EXPECT_STREQ(result2, "he");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("", ""), 0); 
    EXPECT_EQ(String::strcmp("boo", "boo"), 0); 
    EXPECT_LT(String::strcmp("boo", "boocar"), 0); 
    EXPECT_GT(String::strcmp("boocar", "boo"), 0); 
    EXPECT_LT(String::strcmp("apple", "banana"), 0); 
    EXPECT_GT(String::strcmp("banana", "apple"), 0); 
}

TEST(StringFunction, strncmp) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, reverse_cpy) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strchr) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strstr) {
    EXPECT_TRUE(false);
}
