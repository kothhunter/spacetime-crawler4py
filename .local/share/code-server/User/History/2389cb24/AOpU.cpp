#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

using namespace std;

TEST (WordCount, ToLowerCase) {
    std::string word = "Apple";
    to_lowercase(word);
    EXPECT_EQ(word, "apple");
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
    EXPECT_EQ(word_counts["test"], 1);
}

TEST(WordCount, OutputWordCounts) {
    std::map<std::string, int> word_counts = {{"apple", 2}, {"banana", 3}};
    std::ostringstream output;
    output_word_counts(word_counts, output);
    EXPECT_EQ(output.str(), "apple 2\nbanana 3\n");
}