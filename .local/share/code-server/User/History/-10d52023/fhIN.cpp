#include <iostream>
#include <string>
#include "letter_count.hpp"

using namespace std;

constexpr int N_CHARS = ('Z' - 'A' + 1);

int main()
{
    int count_letter[N_CHARS] = {0}; 
    string line;

    while (getline(cin, line)) {
        count(line, count_letter); 
    }

    print_counts(count_letter, N_CHARS);

    return 0;
}