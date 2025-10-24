#pragma once

#include <chrono>

class Stopwatch {
public:
    Stopwatch() = default;

    // Starts or restarts the stopwatch
    void start();

    // Returns elapsed time in seconds since last start.
    // If start() hasn't been called, returns 0 and prints a warning to stderr.
    double elapsedTime() const;

private:
    using clock = std::chrono::steady_clock;
    clock::time_point start_time_{};
    bool started_ = false;
};