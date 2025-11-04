#include <gtest/gtest.h>

// #include "SinglyLinkedList.hpp"
// #include "Queue.hpp"

#include "QueueStack.hpp"
#include "Calculator.hpp"
#include "CircularArray.hpp"

#include <sstream>
#include <string>
#include <iostream>

#include <queue>
#include <chrono>
#include <random>


// Simple RAII redirector for std::cin/std::cout
class IORedirect {
public:
    IORedirect(const std::string& input)
        : cinbuf_(std::cin.rdbuf()), coutbuf_(std::cout.rdbuf())
    {
        in_.str(input);
        std::cin.rdbuf(in_.rdbuf());
        std::cout.rdbuf(out_.rdbuf());
    }
    ~IORedirect() {
        std::cin.rdbuf(cinbuf_);
        std::cout.rdbuf(coutbuf_);
    }
    std::string str() const { return out_.str(); }
private:
    std::stringstream in_;
    std::stringstream out_;
    std::streambuf* cinbuf_;
    std::streambuf* coutbuf_;
};

// --------------- CircularArray Tests ---------------
TEST(CircularArrayTests, EnqueueAndDequeue) {
    CircularArray<int> array(3); // Initial capacity of 3

    // Enqueue elements
    array.enqueue(10);
    array.enqueue(20);
    array.enqueue(30);

    EXPECT_EQ(array.dequeue(), 10); // Dequeue the first element
    EXPECT_EQ(array.dequeue(), 20); // Dequeue the second element
    EXPECT_EQ(array.dequeue(), 30); // Dequeue the third element

    // Test underflow error
    EXPECT_THROW(array.dequeue(), std::out_of_range);
}

TEST(CircularArrayTests, Peek) {
    CircularArray<int> array(3);

    array.enqueue(5);
    array.enqueue(15);

    EXPECT_EQ(array.peek(), 5); // Peek at the front element
    array.dequeue();            // Remove the front element
    EXPECT_EQ(array.peek(), 15); // Peek at the new front element

    // Test underflow error
    array.dequeue();
    EXPECT_THROW(array.peek(), std::out_of_range);
}

TEST(CircularArrayTests, IsEmpty) {
    CircularArray<int> array(3);

    EXPECT_TRUE(array.isEmpty()); // Initially empty

    array.enqueue(1);
    EXPECT_FALSE(array.isEmpty()); // Not empty after enqueue

    array.dequeue();
    EXPECT_TRUE(array.isEmpty()); // Empty after dequeue
}

TEST(CircularArrayTests, IsFull) {
    CircularArray<int> array(3);

    EXPECT_FALSE(array.isFull()); // Initially not full

    array.enqueue(1);
    array.enqueue(2);
    array.enqueue(3);
    EXPECT_TRUE(array.isFull()); // Full after reaching capacity

    array.dequeue();
    EXPECT_FALSE(array.isFull()); // Not full after dequeue
}

TEST(CircularArrayTests, Resize) {
    CircularArray<int> array(2); // Initial capacity of 2

    array.enqueue(1);
    array.enqueue(2);

    EXPECT_TRUE(array.isFull()); // Full before resize

    array.enqueue(3); // Triggers resize
    EXPECT_FALSE(array.isFull()); // Not full after resize

    EXPECT_EQ(array.dequeue(), 1); // Ensure elements are preserved
    EXPECT_EQ(array.dequeue(), 2);
    EXPECT_EQ(array.dequeue(), 3);
}

// mine
TEST(CircularArrayTests, FrontAndRearWrapAround) {
    CircularArray<int> array(3);

    // this is to fill and partially dequeue to force wraparound
    array.enqueue(1);
    array.enqueue(2);
    array.enqueue(3);
    EXPECT_TRUE(array.isFull());

    EXPECT_EQ(array.dequeue(), 1);
    EXPECT_EQ(array.dequeue(), 2);
    EXPECT_FALSE(array.isFull());

    // enqueue again, forcing wrap-around at rear
    array.enqueue(4);
    array.enqueue(5);

    //  queue should now hold [3, 4, 5] in correct order
    EXPECT_EQ(array.dequeue(), 3);
    EXPECT_EQ(array.dequeue(), 4);
    EXPECT_EQ(array.dequeue(), 5);
    EXPECT_TRUE(array.isEmpty());
}

TEST(CircularArrayTests, ResizeMaintainsCorrectCapacity) {
    CircularArray<int> array(2);
    array.enqueue(1);
    array.enqueue(2);
    array.enqueue(3);  // triggers resize to 4
    array.enqueue(4);
    array.enqueue(5);  // triggers resize to 8

    EXPECT_FALSE(array.isFull());

    EXPECT_EQ(array.dequeue(), 1);
    EXPECT_EQ(array.dequeue(), 2);
    EXPECT_EQ(array.dequeue(), 3);
    EXPECT_EQ(array.dequeue(), 4);
    EXPECT_EQ(array.dequeue(), 5);
    EXPECT_TRUE(array.isEmpty());
}

TEST(CircularArrayTests, TypeSupportWithStrings) {
    CircularArray<std::string> array(2);
    array.enqueue("hello");
    array.enqueue("world");

    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array.peek(), "hello");

    EXPECT_EQ(array.dequeue(), "hello");
    EXPECT_EQ(array.dequeue(), "world");
    EXPECT_TRUE(array.isEmpty());

    EXPECT_THROW(array.dequeue(), std::out_of_range);
}

// --------------- QueueStack Tests ---------------
TEST(QueueStackTests, Push) {
    QueueStack<int> stack;
    EXPECT_TRUE(stack.isEmpty());

    stack.push(10);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.peek(), 10); // Top of the stack should be 10

    stack.push(20);
    EXPECT_EQ(stack.peek(), 20); // Top of the stack should now be 20

    stack.push(30);
    EXPECT_EQ(stack.peek(), 30); // Top of the stack should now be 30
}


// --------------- Calculator Tests ---------------
// TEST(CalculatorTest, PerformOperationBasic) {
//     Calculator calc;
//     EXPECT_EQ(calc.performOperation('+', 2, 3), 5);
//     EXPECT_EQ(calc.performOperation('-', 10, 4), 6);
//     EXPECT_EQ(calc.performOperation('*', 3, 5), 15);
//     EXPECT_EQ(calc.performOperation('/', 12, 3), 4);
// }

// TEST(CalculatorTest, ProcessOperationAddsTopTwo) {
//     Calculator calc;
//     calc.memory.push(4);
//     calc.memory.push(6);
//     calc.processOperation("+");
//     EXPECT_EQ(calc.memory.peek(), 10);
// }