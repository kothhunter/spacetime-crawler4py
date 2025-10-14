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

    std::string word3 = "MiXeDbAnaNa123CaSe!";
    to_lowercase(word3);
    EXPECT_EQ(word3, "mixedbanana123case!");

    std::string word4 = "";
    to_lowercase(word4);
    EXPECT_EQ(word4, "");

    std::string word5 = "ALL-CAPS";
    to_lowercase(word5);
    EXPECT_EQ(word5, "all-caps");
}

TEST(WordCount, LoadStopWords) {
    std::istringstream stopwords_input("the\nand\nis");
    auto stopwords = load_stopwords(stopwords_input);
    EXPECT_TRUE(stopwords.find("the") != stopwords.end());
    EXPECT_TRUE(stopwords.find("and") != stopwords.end());
    EXPECT_TRUE(stopwords.find("is") != stopwords.end());
    
    std::istringstream empty_stopwords_input("");
    auto empty_stopwords = load_stopwords(empty_stopwords_input);
    EXPECT_TRUE(empty_stopwords.empty());

    std::istringstream spaced_stopwords_input("  \n   and\n\n \nIS ");
    auto spaced_stopwords = load_stopwords(spaced_stopwords_input);
    EXPECT_EQ(spaced_stopwords.size(), 2);
    EXPECT_TRUE(spaced_stopwords.find("and") != spaced_stopwords.end());
    EXPECT_TRUE(spaced_stopwords.find("is") != spaced_stopwords.end());
}

TEST(WordCount, CountWords) {
    std::istringstream empty_document("");
    std::set<std::string> stopwords = {"is", "a"};
    auto empty_word_counts = count_words(empty_document, stopwords);
    EXPECT_TRUE(empty_word_counts.empty());

    std::istringstream special_characters_document("!@#$%^&*()<>?");
    auto special_characters_word_counts = count_words(special_characters_document, stopwords);
    EXPECT_TRUE(special_characters_word_counts.empty());

    std::istringstream mixed_input_document("apple APPLE aPpLe123 apple-APPLE");
    auto mixed_input_word_counts = count_words(mixed_input_document, stopwords);
    EXPECT_EQ(mixed_input_word_counts["apple"], 1);
    EXPECT_EQ(mixed_input_word_counts["apple123"], 1);
    EXPECT_EQ(mixed_input_word_counts["apple-apple"], 1);

    std::istringstream multiline_document("Line one\nLine two\nLine three.");
    auto multiline_word_counts = count_words(multiline_document, stopwords);
    EXPECT_EQ(multiline_word_counts["line"], 3);
    EXPECT_EQ(multiline_word_counts["one"], 1);
    EXPECT_EQ(multiline_word_counts["two"], 1);
    EXPECT_EQ(multiline_word_counts["three."], 1);
}

TEST(WordCount, OutputWordCounts) {
    std::map<std::string, int> empty_word_counts;
    std::ostringstream empty_output;
    output_word_counts(empty_word_counts, empty_output);
    EXPECT_EQ(empty_output.str(), "");

    std::map<std::string, int> one_word_count = {{"apple", 5}};
    std::ostringstream one_word_output;
    output_word_counts(one_word_count, one_word_output);
    EXPECT_EQ(one_word_output.str(), "apple 5\n");

    std::map<std::string, int> special_word_counts = {{"123", 1}, {"apple-apple", 2}, {"!@#$%", 3}};
    std::ostringstream special_output;
    output_word_counts(special_word_counts, special_output);
    EXPECT_EQ(special_output.str(), "123 1\napple-apple 2\n!@#$% 3\n");
}
