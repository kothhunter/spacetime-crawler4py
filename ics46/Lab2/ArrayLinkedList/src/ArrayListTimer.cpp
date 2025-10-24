#include "ArrayListTimer.hpp"
#include "ArrayList.hpp"
#include "SinglyLinkedList.hpp"
#include "BalancedList.hpp"
#include "Stopwatch.hpp"

#include <vector>
#include <string>
#include <random> // For random number generation

namespace arraylist {

std::vector<double> ArrayListTimer::trial(int size) {
    std::vector<double> results;

    ArrayList<int> arrayList(10); // Ensure initial capacity is sufficient
    SinglyLinkedList<int> singlyList;
    BalancedList<int> balancedList(10);

    Stopwatch stopwatch;

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Time ArrayList (add at random index)
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = (arrayList.size() == 0) ? 0 : std::uniform_int_distribution<>(0, arrayList.size() - 1)(gen);
        arrayList.add(randomIndex, i);
    }
    results.push_back(stopwatch.elapsedTime());

    // Time SinglyLinkedList (add at random index)
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = (singlyList.size() == 0) ? 0 : std::uniform_int_distribution<>(0, singlyList.size() - 1)(gen);
        singlyList.add(randomIndex, i);
    }
    results.push_back(stopwatch.elapsedTime());

    // Time BalancedList (add at random index)
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = (balancedList.size() == 0) ? 0 : std::uniform_int_distribution<>(0, balancedList.size() - 1)(gen);
        balancedList.add(randomIndex, i);
    }
    results.push_back(stopwatch.elapsedTime());

    // Measure time for getting data from random indices
    std::vector<double> getResults;

    // Time ArrayList (get random index)
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = std::uniform_int_distribution<>(0, arrayList.size() - 1)(gen);
        arrayList.get(randomIndex);
    }
    getResults.push_back(stopwatch.elapsedTime());

    // Time SinglyLinkedList (get random index)
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = std::uniform_int_distribution<>(0, singlyList.size() - 1)(gen);
        singlyList.get(randomIndex);
    }
    getResults.push_back(stopwatch.elapsedTime());

    // Time BalancedList (get random index)
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = std::uniform_int_distribution<>(0, balancedList.size() - 1)(gen);
        balancedList.get(randomIndex);
    }
    getResults.push_back(stopwatch.elapsedTime());

    // Append getResults to results
    results.insert(results.end(), getResults.begin(), getResults.end());

    // Measure time for adding elements to the end
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        arrayList.add(i);
    }
    results.push_back(stopwatch.elapsedTime());

    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        singlyList.add(i);
    }
    results.push_back(stopwatch.elapsedTime());

    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        balancedList.add(i);
    }
    results.push_back(stopwatch.elapsedTime());

    // Measure time for removing elements from the end
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        arrayList.remove();
    }
    results.push_back(stopwatch.elapsedTime());

    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        singlyList.remove();
    }
    results.push_back(stopwatch.elapsedTime());

    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        balancedList.remove();
    }
    results.push_back(stopwatch.elapsedTime());

    // Measure time for removing elements at random indices
    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = std::uniform_int_distribution<>(0, arrayList.size() - 1)(gen);
        arrayList.remove(randomIndex);
    }
    results.push_back(stopwatch.elapsedTime());

    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = std::uniform_int_distribution<>(0, singlyList.size() - 1)(gen);
        singlyList.remove(randomIndex);
    }
    results.push_back(stopwatch.elapsedTime());

    stopwatch.start();
    for (int i = 0; i < size; ++i) {
        int randomIndex = std::uniform_int_distribution<>(0, balancedList.size() - 1)(gen);
        balancedList.remove(randomIndex);
    }
    results.push_back(stopwatch.elapsedTime());

    return results;
}

} // namespace arraylist