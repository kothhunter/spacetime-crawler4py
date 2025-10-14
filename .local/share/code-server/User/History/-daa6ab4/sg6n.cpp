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
    Node* original = list::from_string("bar");
    Node* copy_list = list::copy(original);

    ASSERT_NE(original, copy_list);
    EXPECT_EQ(list::compare(original, copy_list), 0);

    list::free(original);
    list::free(copy_list);
}

TEST(ListTests, Compare) {
    Node* list1 = list::from_string("abc");
    Node* list2 = list::from_string("abc");
    Node* list3 = list::from_string("abd");

    EXPECT_EQ(list::compare(list1, list2), 0);
    EXPECT_LT(list::compare(list1, list3), 0);
    EXPECT_GT(list::compare(list3, list1), 0); 

    list::free(list1);
    list::free(list2);
    list::free(list3);
}

TEST(ListTests, Append) {
    Node* list1 = list::from_string("Hello");
    Node* list2 = list::from_string("World");
    Node* combined = list::append(list1, list2);

    EXPECT_EQ(list::length(combined), 10);
    EXPECT_EQ(list::compare(combined, list::from_string("HelloWorld")), 0);

    list::free(list1);
    list::free(list2);
    list::free(combined);
}

TEST(ListTests, FindChar) {
    Node* list = list::from_string("abcdef");
    
    Node* found = list::find_char(list, 'c');
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->data, 'c');

    Node* not_found = list::find_char(list, 'z');
    EXPECT_EQ(not_found, nullptr);

    list::free(list);
}

TEST(ListTests, FindList) {
    Node* haystack = list::from_string("abcdef");
    Node* needle = list::from_string("cde");

    Node* found = list::find_list(haystack, needle);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->data, 'c');

    Node* not_found = list::find_list(haystack, list::from_string("xyz"));
    EXPECT_EQ(not_found, nullptr);

    list::free(haystack);
    list::free(needle);
}

TEST(ListTests, Reverse) {
    Node* list = list::from_string("hello");
    Node* reversed = list::reverse(list);

    EXPECT_EQ(list::compare(reversed, list::from_string("olleh")), 0);

    list::free(list);
    list::free(reversed);
}

TEST(ListTests, Nth) {
    Node* list = list::from_string("hello");

    EXPECT_EQ(list::nth(list, 0)->data, 'h');
    EXPECT_EQ(list::nth(list, 1)->data, 'e');
    EXPECT_EQ(list::nth(list, 4)->data, 'o');
    EXPECT_EQ(list::nth(list, 5), nullptr);

    list::free(list);
}

TEST(ListTests, Last) {
    Node* list = list::from_string("hello");

    Node* last_node = list::last(list);
    ASSERT_NE(last_node, nullptr);
    EXPECT_EQ(last_node->data, 'o');

    list::free(list);
}