#include "ladder.h"
#include <cctype>
#include <algorithm>

void error(string word1, string word2, string msg) {
    cout << word1 << " " << word2 << " " << msg << endl;
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        error("error:", "could not open ", file_name);
        return;
    }
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.size(), len2 = word2.size();
    if (abs(len1 - len2) > 1) return false;
    
    int diff = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++diff > 1) return false;
            if (len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else { ++i; ++j; }
        } else {
            ++i; ++j;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word};
    if (word_list.find(end_word) == word_list.end()) {
        error(begin_word, end_word, "End word is not in the dictionary.");
        return {};
    }
    
    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && !visited.count(word)) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        error("Empty", "Vector:", "No word found.");
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << (i + 1 < ladder.size() ? " -> " : "\n");
    }
}
