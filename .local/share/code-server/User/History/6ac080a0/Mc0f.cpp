#include <map>
#include <iosfwd>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>

#include "word_count.hpp"

using namespace std;

void to_lowercase(std::string& str){
    for(int i = 0 ; i < int(str.size()); i++){
        str[i] = tolower(str[i]);
    }
}

set<string> load_stopwords(istream& stopwords){
    set<string> stopword_set;
    string word;
    while (stopwords >> word){
        to_lowercase(word);
        stopword_set.insert(word);
    }
    return stopword_set;
} 

// std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords){
//     std::map<string,int> myword_counts;
//     string word;
//     while (document >> word){
//         to_lowercase(word);
//         if (stopwords.find(word) == stopwords.end()){
//             myword_counts[word] += 1;
//         }
//     }
//     return myword_counts;
// }
std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<string, int> myword_counts;
    string word;
    while (document >> word) {
        to_lowercase(word);
        word.erase(std::remove_if(word.begin(), word.end(),
                                  [](unsigned char c) { return !std::isalnum(c); }),
                   word.end());
        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            myword_counts[word] += 1;
        }
    }
    return myword_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
//     for (const auto& [word, count] : word_counts) {
//         output << word << " " << count << "\n";
//     }
// }
std::vector<std::pair<std::string, int>> sorted_word_counts(word_counts.begin(), word_counts.end());
    std::sort(sorted_word_counts.begin(), sorted_word_counts.end());

    for (const auto& [word, count] : sorted_word_counts) {
        output << word << " " << count << "\n";
    }
}
