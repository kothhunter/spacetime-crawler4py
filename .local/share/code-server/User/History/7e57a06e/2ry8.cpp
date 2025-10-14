#include <fstream>
#include <iostream>

#include "process_numbers.hpp"

//given

int main() {
    std::ifstream input{"rand_numbers.txt"};
    std::ofstream odds{"odds.txt"};
    std::ofstream evens{"evens.txt"};
    split_odd_even(input, odds, evens);
}