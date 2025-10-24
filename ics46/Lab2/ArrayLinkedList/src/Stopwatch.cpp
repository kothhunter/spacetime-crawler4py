#include "Stopwatch.hpp"

#include <chrono>
#include <cstdio>

void Stopwatch::start() {
    started_ = true;
    start_time_ = clock::now();
}

double Stopwatch::elapsedTime() const {
    if (!started_) {
        std::fputs("Warning: elapsedTime called without starting stopwatch\n", stderr);
        return 0.0;
    }
    auto now = clock::now();
    std::chrono::duration<double> diff = now - start_time_;
    return diff.count();
}