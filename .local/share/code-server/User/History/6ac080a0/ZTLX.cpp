#include "word_count.hpp"
#include <algorithm>
#include <cctype>
#include <iterator>
#include <sstream>

void to_lowercase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
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
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
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
