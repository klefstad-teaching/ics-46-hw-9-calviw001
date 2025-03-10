#include "ladder.h"


void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " (" << word1 << " , " << word2 << ")" << endl;
}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int length1 = str1.size() + 1;
    int length2 = str2.size() + 1;

    int** MED = new int*[length1];
    for (int i = 0; i < length1; i++) {
        MED[i] = new int[length2];
    }

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

    bool verdict = MED[str1.size()][str2.size()] <= d;

    for (int i = 0; i < length1; i++) {
        delete[] MED[i];
    }
    delete[] MED;

    return verdict;
}


bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) {
        return true;
    }
    int length_diff = word1.size() - word2.size();
    if (length_diff == 0) {
        int num_diffs = 0;
        for (int i = 0; i < word1.size(); i++) {
            if (word1[i] != word2[i]) {
                num_diffs += 1;
            }
            if (num_diffs > 1) {
                return false;
            }
        }
        return num_diffs <= 1;
    }
    else if (length_diff <= 1 && length_diff >= -1) {
        int num_diffs = 0;
        string longer_word;
        string shorter_word;
        if (length_diff == 1) {
            longer_word = word1;
            shorter_word = word2;
        }
        else {
            longer_word = word2;
            shorter_word = word1;
        }
        for (int i = 0, j = 0; i < shorter_word.size(); i++, j++) {
            if (shorter_word[i] != longer_word[j]) {
                num_diffs += 1;
                --i;
            }
            if (num_diffs > 1) {
                return false;
            }
        }
        return num_diffs <= 1;
    }
    else {
        return false;
    }
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "The begin word and end word cannot be the same!");
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size()-1];
        for(auto word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
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
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    }
    else {
        cout << "Word ladder found: ";
        for (auto word : ladder) {
            cout << word << " ";
        }
        cout << endl;
    }
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
