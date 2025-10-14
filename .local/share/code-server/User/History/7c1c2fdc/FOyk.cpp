#include <gtest/gtest.h>

#include "list.hpp"

using namespace std;
using list::Node;

TEST(ListTests, FromStringBasic) {
    Node* const foo_list_head = list::from_string("foo");
    Node* foo_list = foo_list_head;

    EXPECT_EQ(foo_list->data, 'f');
    // ASSERT instead of EXPECT means: end the test here if this fails, do not try to continue
    // running. This is useful to prevent early crashes.
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_NE(foo_list->next, nullptr);

    foo_list = foo_list->next;
    EXPECT_EQ(foo_list->data, 'o');
    ASSERT_EQ(foo_list->next, nullptr);

    list::free(foo_list_head);
}

TEST(ListTests, Length) {
    Node* const head = list::from_string("foo");
    EXPECT_EQ(list::length(head), 3);
    list::free(head);
}

// Add remaining tests below. All tests should follow
// the format of `TEST(ListTests, <TestName>){}`.

TEST(ListTests, Copy) {
    Node* og = list::from_string("bar");
    Node* copied = list::copy(og);

    EXPECT_NE(og, copied); 
    EXPECT_EQ(list::compare(og, copied), 0); 

    list::free(og);
    list::free(copied);
}

TEST(ListTests, CompareDiffLength) {
    Node* a = list::from_string("abc");
    Node* b = list::from_string("abcd");

    EXPECT_LT(list::compare(a, b), 0);  // "abc" < "abcd"
    EXPECT_GT(list::compare(b, a), 0);  // "abcd" > "abc"

    list::free(a);
    list::free(b);
}