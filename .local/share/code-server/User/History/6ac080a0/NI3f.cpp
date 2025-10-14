#include "word_count.hpp"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <sstream>
#include <regex>

void to_lowercase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}

std::string clean_word(const std::string& word) {
    auto start = std::find_if(word.begin(), word.end(), ::isalpha);
    auto end = std::find_if(word.rbegin(), word.rend(), ::isalpha).base();

    if (start >= end) return "";

    std::string cleaned(start, end);
    cleaned.erase(std::remove_if(cleaned.begin(), cleaned.end(), [](char c) {
        return !std::isalpha(c) && c != '-';
    }), cleaned.end());

    return cleaned;
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

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;

    while (document >> word) {
        word = clean_word(word);
        to_lowercase(word);

        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            word_counts[word]++;
        }
    }

    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << "\n";
    }
}
