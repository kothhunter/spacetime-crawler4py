// Google Test file: test_lab.cpp

#include <gtest/gtest.h>
#include <chrono>
#include "SinglyLinkedList.hpp"
#include "ArrayList.hpp"
#include "BalancedList.hpp"

// Test SinglyLinkedList<T>::removeLast
TEST(SinglyLinkedListTest, RemoveLastFromSingleElementList) {
    SinglyLinkedList<int> list;
    list.add(10);
    EXPECT_EQ(list.removeLast(), 10);
    EXPECT_TRUE(list.isEmpty());
}

TEST(SinglyLinkedListTest, RemoveLastFromMultipleElementList) {
    SinglyLinkedList<int> list;
    list.add(10);
    list.add(20);
    list.add(30);
    EXPECT_EQ(list.removeLast(), 10);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), 30);
    EXPECT_EQ(list.get(1), 20);
}

TEST(SinglyLinkedListTest, RemoveLastFromEmptyList) {
    SinglyLinkedList<int> list;
    EXPECT_THROW(list.removeLast(), std::out_of_range);
}

// Test SinglyLinkedList<T>::addLast
TEST(SinglyLinkedListTest, AddLastToEmptyList) {
    SinglyLinkedList<int> list;
    list.addLast(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), 10);
}

TEST(SinglyLinkedListTest, AddLastToNonEmptyList) {
    SinglyLinkedList<int> list;
    list.add(20);
    list.addLast(10);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(1), 10);
}

// Test ArrayList<T>::add and remove at index
TEST(ArrayListTest, AddAtIndex) {
    ArrayList<int> list(2, 2);
    list.add(10);
    list.add(20);
    list.add(1, 15);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(1), 15);
}

TEST(ArrayListTest, RemoveAtIndex) {
    ArrayList<int> list(2, 2);
    list.add(10);
    list.add(20);
    EXPECT_EQ(list.remove(0), 10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), 20);
}

// Test ArrayList<T>::expand and shrink
TEST(ArrayListTest, Expand) {
    ArrayList<int> list(2, 2);
    list.add(10);
    list.add(20);
    list.add(30); // Should trigger expand
    EXPECT_EQ(list.getCapacity(), 4);
    EXPECT_EQ(list.size(), 3);
}

TEST(ArrayListTest, Shrink) {
    ArrayList<int> list(4, 2);
    list.add(10);
    list.add(20);
    list.remove();
    list.remove(); // Should trigger shrink
    EXPECT_EQ(list.getCapacity(), 2);
    EXPECT_EQ(list.size(), 0);
}

// Test BalancedList<T>::get
TEST(BalancedListTest, GetElement) {
    BalancedList<int> list(2);
    list.add(10);
    list.add(20);
    EXPECT_EQ(list.get(0), 20);
    EXPECT_EQ(list.get(1), 10);
}

// Test BalancedList<T>::add and remove at index
TEST(BalancedListTest, AddAtIndex) {
    BalancedList<int> list(2);
    list.add(10);
    list.add(20);
    list.add(1, 15);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(1), 15);
}

TEST(BalancedListTest, RemoveAtIndex) {
    BalancedList<int> list(2);
    list.add(10);
    list.add(20);
    EXPECT_EQ(list.remove(0), 20);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), 10);
}

// TODO: add additional tests
TEST(ArrayListTest, AddAtBeginningAndEnd) {
    ArrayList<int> list(2, 2);
    list.add(0, 10);
    list.add(1, 20);
    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 20);
    EXPECT_EQ(list.size(), 2);
}

TEST(ArrayListTest, AddAtInvalidIndexThrows) {
    ArrayList<int> list(2, 2);
    list.add(10);
    EXPECT_THROW(list.add(5, 100), std::out_of_range);
}