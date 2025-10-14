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
#include <iostream>
#include <string>
#include "letter_count.hpp"

using namespace std;

constexpr int N_CHARS = ('Z' - 'A' + 1); // will be 26

int main()
{
    int letterCounts[N_CHARS] = {0}; 
    string line;

    while (getline(cin, line)) {
        count(line, letterCounts); 
    }

    print_counts(letterCounts, N_CHARS);

    return 0;
}