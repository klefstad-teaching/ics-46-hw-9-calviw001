#include "ladder.h"


void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " (" << word1 << " , " << word2 << ")" << endl;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int length1 = str1.size() + 1;
    int length2 = str2.size() + 1;
    int MED[length1][length2];

    for (int i = 0; i < length1; ++i) {
        MED[i][0] = i;
    }
    for (int j = 0; j < length2; ++j) {
        MED[0][j] = j;
    }

    for (int i = 1; i < length1; ++i) {
        for (int j = 1; j < length2; ++j) {
            if (str1[i-1] == str2[j-1]) {
                MED[i][j] = MED[i-1][j-1];
            } else {
                MED[i][j] = 1 + min({MED[i][j-1], MED[i-1][j-1], MED[i-1][j]});
            }
        }
    }

    return MED[str1.size()][str2.size()] <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) {
        return true;
    }
    return edit_distance_within(word1, word2, 1);
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    vector<string> result;
    return result;
}


void load_words(set<string> & word_list, const string& file_name) {
    ifstream inFile;  
    inFile.open(file_name);
    if (!(inFile.is_open())) {
        error("", "", "Cannot open file!");
        return;
    }
    string word;
    while (getline(inFile, word)) {
        word_list.insert(word);
    }
    inFile.close();
}


void print_word_ladder(const vector<string>& ladder) {

}


void verify_word_ladder() {

}
