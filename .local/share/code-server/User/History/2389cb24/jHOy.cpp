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
    EXPECT_EQ(word_counts.count("is"), 0);
}

TEST(WordCount, OutputWordCounts) {
    stringstream output0;
    map<string, int> expect = {{"is",2},{"a",1},{"test",1}};
    output_word_counts(expect,output0);
    EXPECT_STREQ(output0.str().c_str(), "a 1\nis 2\ntest 1\n");

    stringstream output1;
    map<string, int> expect1 = {};
    output_word_counts(expect1,output1);
    EXPECT_STREQ(output1.str().c_str(),"");