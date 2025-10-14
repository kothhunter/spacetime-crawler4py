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
    EXPECT_EQ(String::strncpy(result, "foo", 3), result); 
    EXPECT_STREQ(result, "foo");

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
    EXPECT_EQ(String::strcmp("", ""), 0); // Compare empty strings
    EXPECT_EQ(String::strcmp("foo", "foo"), 0); // Compare equal strings
    EXPECT_LT(String::strcmp("foo", "foobar"), 0); // Compare shorter string with longer string
    EXPECT_GT(String::strcmp("foobar", "foo"), 0); // Compare longer string with shorter string
    EXPECT_LT(String::strcmp("apple", "banana"), 0); // Compare lexicographically smaller string
    EXPECT_GT(String::strcmp("banana", "apple"), 0); // Compare lexicographically larger string
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
