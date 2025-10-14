#include "mapset.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <cctype>

std::string to_lowercase(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return lower_str;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopwords_set;
    std::string word;
    while (stopwords >> word) {
        stopwords_set.insert(to_lowercase(word));
    }
    return stopwords_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;
    while (document >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
            return std::ispunct(c);
        }), word.end());
        
        word = to_lowercase(word);
        
        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            ++word_counts[word];
        }
    }
    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << "\n";
    }
}
