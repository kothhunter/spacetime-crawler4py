#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>

#include "string.hpp"

using namespace std;

TEST(StringClass, Constructors) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);

    String empty;
    EXPECT_EQ(empty.size(), 0);

    String singleChar("a");
    EXPECT_EQ(singleChar.size(), 1);

    String t(s);
    EXPECT_EQ(t.size(), 5);
    EXPECT_EQ(s.size(), 5);
}

TEST(StringClass, Print) {
    String s("foo");
    stringstream out;
    s.print(out);
    EXPECT_STREQ(out.str().c_str(), "foo");

    stringstream out2;
    String().print(out2);
    EXPECT_STREQ(out2.str().c_str(), "");

    stringstream out3;
    out3 << s << s << String("bar");
    EXPECT_STREQ(out3.str().c_str(), "foofoobar");
}

TEST(StringClass, Comparisons) {
    EXPECT_LT(String("aaaa"), String("aaab"));
    EXPECT_LE(String("aaaa"), String("aaab"));
    EXPECT_EQ(String("foo"), String("foo"));
    EXPECT_NE(String("foo"), String("fooo"));

    EXPECT_GT(String("z"), String("a"));  
    EXPECT_GE(String("z"), String("z"));
    EXPECT_NE(String("abc"), String("xyz"));
}

TEST(StringClass, Assignment) {
    String s("test"), t("foo");

    s = t;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = s;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = String();
    EXPECT_EQ(s, String());
    EXPECT_EQ(s.size(), 0);
}

TEST(StringClass, Concatenation) {
    String a("Hello"), b(" World");
    String c = a + b;
    EXPECT_EQ(c, String("Hello World"));
    EXPECT_EQ(a.size(), 5); 
    EXPECT_EQ(b.size(), 6); 

    a += b;
    EXPECT_EQ(a, String("Hello World"));
    EXPECT_EQ(a.size(), 11);
}

TEST(StringClass, Subscript) {
    String s("hello");

    EXPECT_EQ(s[0], 'h');
    EXPECT_EQ(s[1], 'e');
    EXPECT_EQ(s[4], 'o');

    testing::internal::CaptureStderr();
    char out_of_bounds_char = s[10]; 
    std::string error_output = testing::internal::GetCapturedStderr();
    EXPECT_NE(error_output.find("ERROR"), std::string::npos)
        << "Expected 'ERROR' message, but got: " << error_output;
    EXPECT_EQ(out_of_bounds_char, '\0'); 
}

TEST(StringClass, IndexOfCharacter) {
    String s("hello world");

    EXPECT_EQ(s.indexOf('h'), 0);
    EXPECT_EQ(s.indexOf('o'), 4);
    EXPECT_EQ(s.indexOf('w'), 6);
    EXPECT_EQ(s.indexOf('z'), -1); 
}

TEST(StringClass, IndexOfString) {
    String s("hello world");

    EXPECT_EQ(s.indexOf(String("hello")), 0);
    EXPECT_EQ(s.indexOf(String("world")), 6);
    EXPECT_EQ(s.indexOf(String("lo w")), 3);
    EXPECT_EQ(s.indexOf(String("xyz")), -1); 

    // Edge case
    EXPECT_EQ(s.indexOf(String("")), 0);
    EXPECT_EQ(String("").indexOf(String("")), 0);
}

TEST(StringClass, Reverse) {
    String s("hello");
    String reversed = s.reverse();
    EXPECT_EQ(reversed, String("olleh"));
    EXPECT_EQ(s, String("hello")); 

    String empty;
    EXPECT_EQ(empty.reverse(), String(""));
}

TEST(StringClass, MinimumAllocations) {
    String s("abc");
    String t("def");
    
    tracking::AllocationTracker tracker;
    {
        tracking::Subtracker subtracker(tracker);
        s += t; 
        EXPECT_EQ(subtracker.get_num_allocations(), 3);
    }
}
