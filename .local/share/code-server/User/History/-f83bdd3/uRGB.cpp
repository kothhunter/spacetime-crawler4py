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


TEST(StringFunction, strncpy) {
    char result[10];
    EXPECT_EQ(String::strncpy(result, "foolish", 3), result);
    EXPECT_STREQ(result, "foo");
}

TEST(StringFunction, strcat) {
    char result[15] = "Hello ";
    EXPECT_EQ(String::strcat(result, "World"), result);
    EXPECT_STREQ(result, "Hello World");
}

TEST(StringFunction, strncat)
{
    char result[15] = "Hello ";
    EXPECT_EQ(String::strncat(result, "World", 15), result);
    EXPECT_STREQ(result, "Hello World");
}

TEST(StringFunction, strcmp) {
    char result[15] = "Hello";
    char result1[15] = "Hello";
    EXPECT_EQ(String::strcmp(result, result1), 0);

    char result2[15] = "Hello";
    char result3[15] = "World";
    EXPECT_EQ(String::strcmp(result2, result3), -15);
}

TEST(StringFunction, strncmp) {
    char result[15] = "Hello";
    char result1[15] = "Hello";
    EXPECT_EQ(String::strncmp(result, result1, 5), 0);

    char result2[15] = "Hello";
    char result3[15] = "World";
    EXPECT_EQ(String::strncmp(result2, result3, 2), -15);

    char result4[15] = "";
    char result5[15] = "Hello World";
    EXPECT_EQ(String::strncmp(result4, result5, 11), -72);
}

TEST(StringFunction, reverse_cpy) 
{
    char result[15] = "Hello";
    char result1[15] = "Hello";
    String::reverse_cpy(result, result1);
    EXPECT_STREQ(result, "olleH");

    char result2[5] = "foo";
    char result3[5] = "foo";
    String::reverse_cpy(result2, result3);
    EXPECT_STREQ(result2, "oof");
}

TEST(StringFunction, strchr) 
{
    const char* str = "Hello World";
    EXPECT_EQ(String::strchr(str, 'o'), str + 4);
    EXPECT_EQ(String::strchr(str, 'q'), nullptr);
}

TEST(StringFunction, strstr) 
{
    const char* str = "Hello World";
    const char* str1 = "";
    const char* str2 = "321321";
    EXPECT_EQ(String::strstr(str, "o"), str + 4);
    EXPECT_EQ(String::strstr(str, "q"), nullptr);
    EXPECT_EQ(String::strstr(str1, ""), str1);
    EXPECT_EQ(String::strstr(str1, "\0"), str1);
    EXPECT_EQ(String::strstr(str2, "321321"), str2);
}

TEST(StringFunction, strdup)
{
    const char* str = "Hello World";
    char* a = String::strdup(str);
    EXPECT_EQ(strcmp(a, str), 0);
    delete[] a;
}
// TEST(StringFunction, strdup) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, strncpy) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, strcat) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, strncat) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, strcmp) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, strncmp) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, reverse_cpy) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, strchr) {
//     EXPECT_TRUE(false);
// }

// TEST(StringFunction, strstr) {
//     EXPECT_TRUE(false);
// }
