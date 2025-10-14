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
    EXPECT_EQ(word_counts["dog"], 0);

    EXPECT_EQ(word_counts.count("the"), 0);
    EXPECT_EQ(word_counts.count("over"), 0);
    EXPECT_EQ(word_counts.count("slow"), 0);
}

TEST(WordCount, OutputWordCounts) {
    map<string, int> word_counts = {
        {"quick", 1},
        {"fox", 2},
        {"jumps", 1},
        {"fat", 1},
        {"dog", 1}
    };

    stringstream output;
    output_word_counts(word_counts, output);

    string expected_output = "quick 1\ndog 1\nfox 2\njumps 1\nfat 1\nquick 1\n";
    
    EXPECT_EQ(output.str(), expected_output);
}