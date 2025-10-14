#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

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

TEST(StringFunction, strdup) {
    char *duplicated = String::strdup("test");
    EXPECT_STREQ(duplicated, "test");
    delete[] duplicated;

    duplicated = String::strdup("");
    EXPECT_STREQ(duplicated, "");
    delete[] duplicated;
}

TEST(StringFunction, strncpy) {
    char result[10] = {'\0'};
    EXPECT_EQ(String::strncpy(result, "abcdef", 3), result);
    EXPECT_STREQ(result, "abc");

    EXPECT_EQ(String::strncpy(result, "xyz", 10), result);
    EXPECT_STREQ(result, "xyz");

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strcat) {
    char result[20] = "Hello";
    EXPECT_EQ(String::strcat(result, " World"), result);
    EXPECT_STREQ(result, "Hello World");
}

TEST(StringFunction, strncat) {
    char result[20] = "Hello";
    EXPECT_EQ(String::strncat(result, " World", 3), result);
    EXPECT_STREQ(result, "Hello Wo");

    EXPECT_EQ(String::strncat(result, "!", 10), result);
    EXPECT_STREQ(result, "Hello Wo!");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("abc", "abc"), 0);
    EXPECT_GT(String::strcmp("bcd", "abc"), 0);
    EXPECT_LT(String::strcmp("abc", "bcd"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("abcdef", "abcxyz", 3), 0);
    EXPECT_GT(String::strncmp("hello", "hella", 5), 0);
    EXPECT_LT(String::strncmp("hell", "hello", 5), 0);
}

TEST(StringFunction, reverse_cpy) {
    char result[10];
    String::reverse_cpy(result, "abcd");
    EXPECT_STREQ(result, "dcba");

    String::reverse_cpy(result, "racecar");
    EXPECT_STREQ(result, "racecar");

    String::reverse_cpy(result, "");
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strchr) {
    EXPECT_EQ(String::strchr("hello", 'e'), &"hello"[1]);
    EXPECT_EQ(String::strchr("world", 'd'), &"world"[4]);
    EXPECT_EQ(String::strchr("test", 'x'), nullptr);
}

TEST(StringFunction, strstr) {
    EXPECT_EQ(String::strstr("hello world", "world"), &"hello world"[6]);
    EXPECT_EQ(String::strstr("abcdef", "bc"), &"abcdef"[1]);
    EXPECT_EQ(String::strstr("abcdef", "xyz"), nullptr);
}
