#ifndef ARRAYLISTTIMER_HPP
#define ARRAYLISTTIMER_HPP

#include <vector>
#include <string>
#include "Stopwatch.hpp"

namespace arraylist {

class ArrayListTimer {
public:
    // Runs the timing experiment for a specific data structure and returns the elapsed time
    template <typename ListType>
    static double run(int maxSize) {
        ListType testlist;
        Stopwatch timer;

        // Simulate garbage collection-like behavior
        std::vector<char> tmp(1);
        (void)tmp;

        timer.start();
        for (int i = 0; i < maxSize; ++i) {
            testlist.add(i, "new string"); // Add at index i
        }

        return timer.elapsedTime();
    }

    // Runs the timing experiment for all three data structures and returns the results
    static std::vector<double> trial(int maxSize);
};

} // namespace arraylist

#endif // ARRAYLISTTIMER_HPP