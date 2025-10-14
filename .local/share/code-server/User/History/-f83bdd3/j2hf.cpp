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
    EXPECT_TRUE(false);
}

TEST(StringFunction, strncpy) {
    //last hw
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
    //last hw
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
    //last hw
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
    //last hw
    EXPECT_EQ(String::strcmp("", ""), 0); 
    EXPECT_EQ(String::strcmp("boo", "boo"), 0); 
    EXPECT_LT(String::strcmp("boo", "boocar"), 0); 
    EXPECT_GT(String::strcmp("boocar", "boo"), 0); 
    EXPECT_LT(String::strcmp("apple", "banana"), 0); 
    EXPECT_GT(String::strcmp("banana", "apple"), 0); 
}

TEST(StringFunction, strncmp) {
    //last hw
    EXPECT_EQ(String::strncmp("", "", 1), 0);
    EXPECT_EQ(String::strncmp("boo", "boo", 3), 0);
    EXPECT_EQ(String::strncmp("boo", "boocar", 3), 0);
    EXPECT_LT(String::strncmp("apple", "banana", 5), 0); 
    EXPECT_GT(String::strncmp("banana", "apple", 5), 0); 
    EXPECT_EQ(String::strncmp("boo", "car", 0), 0); 
}

TEST(StringFunction, reverse_cpy) {
    char result[10];
    String::reverse_cpy(result, "boo"); 
    EXPECT_STREQ(result, "oob");

    String::reverse_cpy(result, "");
    EXPECT_STREQ(result, "");

    String::reverse_cpy(result, "hello");
    EXPECT_STREQ(result, "olleh");
}

TEST(StringFunction, strchr) {
    const char* result1 = String::strchr("planet", 'a');
    EXPECT_EQ(result1, "planet" + 2);

    const char* result2 = String::strchr("code", 'e');
    EXPECT_EQ(result2, "code" + 3); 

    const char* result3 = String::strchr("tree", 't');
    EXPECT_EQ(result3, "tree"); 

    const char* result4 = String::strchr("hello", 'z');
    EXPECT_EQ(result4, nullptr);  
}

TEST(StringFunction, strstr) {
    const char *hs = "loocar";
    EXPECT_EQ(String::strstr(hs, "loo"), hs);
    EXPECT_EQ(String::strstr(hs, "car"), hs + 3);
    EXPECT_EQ(String::strstr(hs, "oca"), hs + 2); 
    EXPECT_EQ(String::strstr(hs, "xyz"), nullptr); 
    EXPECT_EQ(String::strstr(hs, ""), hs);
}
