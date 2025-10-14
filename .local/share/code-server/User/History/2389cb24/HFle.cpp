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
    stringstream input("the\nand\nfor\nof");
    set<string> stopwords = load_stopwords(input);
    
    EXPECT_EQ(stopwords.size(), 4);
    EXPECT_TRUE(stopwords.count("the") > 0);
    EXPECT_TRUE(stopwords.count("and") > 0);
    EXPECT_TRUE(stopwords.count("for") > 0);
    EXPECT_TRUE(stopwords.count("of") > 0);

    stringstream empty_input;
    set<string> empty_stopwords = load_stopwords(empty_input);
    EXPECT_EQ(empty_stopwords.size(), 0);

    stringstream mixed_case_input("The\nA\nAn\nOf");
    set<string> mixed_case_stopwords = load_stopwords(mixed_case_input);
    EXPECT_EQ(mixed_case_stopwords.size(), 4);
}

TEST(WordCount, CountWords) {
    stringstream doc("The quick fox jumps over the fat dog. The fox is fast.");

    set<string> stopwords = {"the", "over", "is"};
    map<string, int> word_counts = count_words(doc, stopwords);

    EXPECT_EQ(word_counts["quick"], 1);
    EXPECT_EQ(word_counts["fox"], 2); 
    EXPECT_EQ(word_counts["jumps"], 1);
    EXPECT_EQ(word_counts["fat"], 1);
    EXPECT_EQ(word_counts["dog"], 1);

    EXPECT_EQ(word_counts.count("the"), 0);
    EXPECT_EQ(word_counts.count("over"), 0);
    EXPECT_EQ(word_counts.count("slow"), 0);
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