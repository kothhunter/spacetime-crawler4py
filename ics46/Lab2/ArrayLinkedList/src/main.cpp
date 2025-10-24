#include <iostream>
#include "ArrayList.hpp"
#include "SinglyLinkedList.hpp"
#include "BalancedList.hpp"
#include "ArrayListTimer.hpp" // Include ArrayListTimer header file

// Helper function to print the contents of a list
template <typename ListType>
void printListContents(const ListType& list) {
    std::cout << "[ ";
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << "]\n";
}

int main() {
    // Test ArrayList
    std::cout << "Testing ArrayList:\n";
    ArrayList<int> arrayList(10);

    // Test add
    std::cout << "Adding elements to ArrayList:\n";
    arrayList.add(1);
    printListContents(arrayList);
    arrayList.add(2);
    printListContents(arrayList);

    // Test add at index
    std::cout << "Adding elements at specific indices in ArrayList:\n";
    arrayList.add(0, 3);
    printListContents(arrayList);
    arrayList.add(1, 4);
    printListContents(arrayList);

    // Test remove
    std::cout << "Removing elements from ArrayList:\n";
    arrayList.remove();
    printListContents(arrayList);
    arrayList.remove();
    printListContents(arrayList);

    // Test remove at index
    std::cout << "Removing elements at specific indices in ArrayList:\n";
    arrayList.add(5);
    arrayList.add(6);
    printListContents(arrayList);
    arrayList.remove(1);
    printListContents(arrayList);
    arrayList.remove(2);
    printListContents(arrayList);

    // Test SinglyLinkedList
    std::cout << "\nTesting SinglyLinkedList:\n";
    SinglyLinkedList<int> singlyList;

    // Test add
    std::cout << "Adding elements to SinglyLinkedList:\n";
    singlyList.add(1);
    printListContents(singlyList);
    singlyList.add(2);
    printListContents(singlyList);

    // Test add at index
    std::cout << "Adding elements at specific indices in SinglyLinkedList:\n";
    singlyList.add(0, 3);
    printListContents(singlyList);
    singlyList.add(1, 4);
    printListContents(singlyList);

    // Test remove
    std::cout << "Removing elements from SinglyLinkedList:\n";
    singlyList.remove();
    printListContents(singlyList);
    singlyList.remove();
    printListContents(singlyList);

    // Test remove at index
    std::cout << "Removing elements at specific indices in SinglyLinkedList:\n";
    singlyList.add(5);
    singlyList.add(6);
    printListContents(singlyList);
    singlyList.remove(1);
    printListContents(singlyList);
    singlyList.remove(2);
    printListContents(singlyList);

    // Test BalancedList
    std::cout << "\nTesting BalancedList:\n";
    BalancedList<int> balancedList(2);

    // Test add
    std::cout << "Adding elements to BalancedList:\n";
    balancedList.add(1);
    printListContents(balancedList);
    balancedList.add(2);
    printListContents(balancedList);

    // Test add at index
    std::cout << "Adding elements at specific indices in BalancedList:\n";
    balancedList.add(0, 3);
    printListContents(balancedList);
    balancedList.add(1, 4);
    printListContents(balancedList);
    balancedList.add(3, 9);
    printListContents(balancedList);

    // Test remove
    std::cout << "Removing elements from BalancedList:\n";
    balancedList.remove();
    printListContents(balancedList);
    balancedList.remove();
    printListContents(balancedList);

    // Test remove at index
    std::cout << "Removing elements at specific indices in BalancedList:\n";
    balancedList.add(5);
    balancedList.add(6);
    printListContents(balancedList);
    balancedList.remove(1);
    printListContents(balancedList);
    balancedList.remove(2);
    printListContents(balancedList);

    // Timing experiments
    const int MIN_SIZE = 1000;
    const int MAX_SIZE = 64001;
    // Table for add at random index
    std::puts("\nTiming for add at random index:");
    std::printf(" %8s | %12s | %12s | %12s\n", "size", "ArrayList", "SinglyList", "BalancedList");
    std::puts(" -------------------------------------------------------------");

    for (int size = MIN_SIZE; size < MAX_SIZE; size *= 2) {
        auto results = arraylist::ArrayListTimer::trial(size);
        std::printf(" %8d | %12f | %12f | %12f\n", size, results[0], results[1], results[2]);
    }

    // Table for get at random index
    std::puts("\nTiming for get at random index:");
    std::printf(" %8s | %12s | %12s | %12s\n", "size", "ArrayList", "SinglyList", "BalancedList");
    std::puts(" -------------------------------------------------------------");

    for (int size = MIN_SIZE; size < MAX_SIZE; size *= 2) {
        auto results = arraylist::ArrayListTimer::trial(size);
        std::printf(" %8d | %12f | %12f | %12f\n", size, results[3], results[4], results[5]);
    }

    // Table for add
    std::puts("\nTiming for add:");
    std::printf(" %8s | %12s | %12s | %12s\n", "size", "ArrayList", "SinglyList", "BalancedList");
    std::puts(" -------------------------------------------------------------");

    for (int size = MIN_SIZE; size < MAX_SIZE; size *= 2) {
        auto results = arraylist::ArrayListTimer::trial(size);
        std::printf(" %8d | %12f | %12f | %12f\n", size, results[6], results[7], results[8]);
    }

    // Table for remove
    std::puts("\nTiming for remove:");
    std::printf(" %8s | %12s | %12s | %12s\n", "size", "ArrayList", "SinglyList", "BalancedList");
    std::puts(" -------------------------------------------------------------");

    for (int size = MIN_SIZE; size < MAX_SIZE; size *= 2) {
        auto results = arraylist::ArrayListTimer::trial(size);
        std::printf(" %8d | %12f | %12f | %12f\n", size, results[9], results[10], results[11]);
    }

    // Table for remove at random index
    std::puts("\nTiming for remove at random index:");
    std::printf(" %8s | %12s | %12s | %12s\n", "size", "ArrayList", "SinglyList", "BalancedList");
    std::puts(" -------------------------------------------------------------");

    for (int size = MIN_SIZE; size < MAX_SIZE; size *= 2) {
        auto results = arraylist::ArrayListTimer::trial(size);
        std::printf(" %8d | %12f | %12f | %12f\n", size, results[12], results[13], results[14]);
    }

    return 0;
}