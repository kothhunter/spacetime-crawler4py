#include <iostream>
#include <string>
#include "letter_count.hpp"

using namespace std;

int main() {
    int counts[N_CHARS] = {0}; 
    string ln;

    while (getline(cin, ln)) {
        count(ln, counts); 
    }

    print_counts(counts, N_CHARS);

    return 0;
}