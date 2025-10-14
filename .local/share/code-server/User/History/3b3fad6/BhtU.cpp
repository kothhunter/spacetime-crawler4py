#include "mapset.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <cctype>

std::string to_lowercase(const std::string& str) {
    std::string lower;
    lower.reserve(str.size());
    std::transform(str.begin(), str.end(), std::back_inserter(lower), [](unsigned char c) {
        return std::tolower(static_cast<unsigned char>(c));
    });
    return lower;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::istream_iterator<std::string> start(stopwords), end;
    std::set<std::string> stopwords_set{start, end};

    std::set<std::string> lower_stopwords;
    std::transform(stopwords_set.begin(), stopwords_set.end(), 
                   std::inserter(lower_stopwords, lower_stopwords.begin()), 
                   [](const std::string& word) { return to_lowercase(word); });

    return lower_stopwords;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::vector<std::string> words{std::istream_iterator<std::string>(document), std::istream_iterator<std::string>()};

    std::for_each(words.begin(), words.end(), [&](std::string& word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
            return std::ispunct(static_cast<unsigned char>(c));
        }), word.end());

        word = to_lowercase(word);

        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            ++word_counts[word];
        }
    });

    return word_counts;
}

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    std::for_each(word_counts.begin(), word_counts.end(), [&](const auto& pair) {
        output << pair.first << " " << pair.second << endl;
    });
}
