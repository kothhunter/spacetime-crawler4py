#include <iostream>
#include <string>
#include "letter_count.hpp"
using namespace std;

int main() {
    int counts[N_CHARS] = {0}; 
    string line;

    cout << "Enter text (Ctrl+D to end input):" << endl;

    while (getline(cin, line)) {
        count(line, counts);
    }

    print_counts(counts, N_CHARS);

    return 0;
}
