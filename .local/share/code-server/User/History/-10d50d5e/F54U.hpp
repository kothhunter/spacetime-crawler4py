#include <iostream>
#include <string>
#include <cctype>
using namespace std;

constexpr int N_CHARS = ('Z' - 'A' + 1); 

int char_to_index(char ch) {
    if (isalpha(ch)) {
        return toupper(ch) - 'A';
    }
    return -1; 
}

char index_to_char(int i) {
    return 'A' + i;
}

void count(const string s, int counts[]) {
    for (char ch : s) {
        int index = char_to_index(ch);
        if (index != -1) {
            counts[index]++;
        }
    }
}

void print_counts(int counts[], int len) {
    for (int i = 0; i < len; ++i) {
        cout << index_to_char(i) << " " << counts[i] << endl;
    }
}