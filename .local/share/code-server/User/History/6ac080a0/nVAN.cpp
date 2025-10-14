#include <map>
#include <iosfwd>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>

#include "word_count.hpp"

void to_lowercase(std::string& str){
    for(int i = 0 ; i < int(str.size()); i++){
        str[i] = tolower(str[i]);
    }
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopword_set;
    std::string word;
    while (stopwords >> word) {
        to_lowercase(word); 
        stopword_set.insert(word);
    }
    return stopword_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords){
    std::map<string,int> word_counts;
    string word;
    while (document >> word){
        to_lowercase(word);
        if (stopwords.find(word) == stopwords.end()){
            word_counts[word] += 1;
        }
    }
    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << "\n";
    }
}
