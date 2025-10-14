#include <fstream>

#include "mapset.hpp"

using namespace std;

int main(){
    ifstream stopwords_file{"stopwords.txt"}
    const auto stopwords = load_stopword(stopwords_file);

    ifstream document{"sample_doc.txt"}
}