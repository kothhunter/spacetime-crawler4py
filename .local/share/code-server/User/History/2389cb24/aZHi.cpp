#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

using namespace std;

TEST (WordCount, ToLowerCase) {
    std::string word = "Apple";
    to_lowercase(word);
    EXPECT_EQ(word, "apple");

    std::string word1 = "ALREADYlowercase";
    to_lowercase(word1);
    EXPECT_EQ(word1, "alreadylowercase");

    std::string word2 = "12345";
    to_lowercase(word2);
    EXPECT_EQ(word2, "12345");

    std::string word3 = "MiXeD123CaSe!";
    to_lowercase(word3);
    EXPECT_EQ(word3, "mixed123case!");

    std::string word4 = ""; // Empty string
    to_lowercase(word4);
    EXPECT_EQ(word4, "");

    std::string word5 = "ALL-CAPS";
    to_lowercase(word5);
    EXPECT_EQ(word5, "all-caps");
}
}

TEST(WordCount, LoadStopWords) {
    std::istringstream stopwords_input("the\nand\nis");
    auto stopwords = load_stopwords(stopwords_input);
    EXPECT_TRUE(stopwords.find("the") != stopwords.end());
    EXPECT_TRUE(stopwords.find("and") != stopwords.end());
    EXPECT_TRUE(stopwords.find("is") != stopwords.end());
}

TEST(WordCount, CountWords) {
    std::istringstream document("Apple apple! Is this a test?");
    std::set<std::string> stopwords = {"is", "a"};
    auto word_counts = count_words(document, stopwords);
    EXPECT_EQ(word_counts["apple"], 1);
    EXPECT_EQ(word_counts["this"], 1);
    // EXPECT_EQ(word_counts["test"], 1);
}

TEST(WordCount, OutputWordCounts) {
    std::map<std::string, int> word_counts = {{"apple", 2}, {"banana", 3}};
    std::ostringstream output;
    output_word_counts(word_counts, output);
    EXPECT_EQ(output.str(), "apple 2\nbanana 3\n");
}