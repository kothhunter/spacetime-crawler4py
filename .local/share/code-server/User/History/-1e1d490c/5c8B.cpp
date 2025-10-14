#include "process_numbers.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    std::vector<int> values{std::istream_iterator<int>{numbers}, std::istream_iterator<int>{}};
    
    std::ranges::sort(values);
    

    std::copy_if(values.begin(), values.end(), std::ostream_iterator<int>(odds, " "), [](int num) {
        return num % 2 != 0;
    });
    
    odds << '\n';
    
    std::copy_if(values.begin(), values.end(), std::ostream_iterator<int>(evens, "\n"), [](int num) {
        return num % 2 == 0;
    });
}
