#include "mapset.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <cctype>

std::string to_lowercase(const std::string& str) {
    std::string lower_str;
    lower_str.reserve(str.size()); // Optimize memory allocation
    std::transform(str.begin(), str.end(), std::back_inserter(lower_str), [](unsigned char c) {
        return std::tolower(static_cast<unsigned char>(c));
    });
    return lower_str;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopwords_set;
    std::string word;
    while (stopwords >> word) {
        word = to_lowercase(word);
        stopwords_set.insert(word);
    }
    return stopwords_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;
    while (document >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
            return std::ispunct(static_cast<unsigned char>(c));
        }), word.end());

        word = to_lowercase(word);

        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            word_counts[word]++;
        }
    }
    return word_counts;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;
    while (document >> word) {
        // Remove punctuation
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
            return std::ispunct(static_cast<unsigned char>(c));
        }), word.end());

        // Convert to lowercase
        word = to_lowercase(word);

        // Ensure word is not empty and is not a stopword
        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            ++word_counts[word];
        }
    }
    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& pair : word_counts) {
        output << pair.first << " " << pair.second << "\n";
    }
}
