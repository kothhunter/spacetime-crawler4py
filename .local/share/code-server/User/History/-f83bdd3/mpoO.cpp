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
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncat) {
    EXPECT_TRUE(false);
}

TEST(StringFunction, strcmp) {
    EXPECT_TRUE(false);
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
