#include <gtest/gtest.h>

#include <sstream>
#include "word_count.hpp"

using namespace std;

TEST (WordCount, ToLowerCase) {
    string input = "Hello, WORLD! How ARE You?";
    to_lowercase(input);
    EXPECT_EQ(input, "hello, world! how are you?");

    string input2 = "already lowercase yay";
    to_lowercase(input2);
    EXPECT_EQ(input2, "already lowercase yay");

    string input3 = "135 TEST @jobs! FIRE";
    to_lowercase(input3);
    EXPECT_EQ(input3, "135 test @jobs! fire");

    string input4 = "";
    to_lowercase(input4);
    EXPECT_EQ(input4, "");
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