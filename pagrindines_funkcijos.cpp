#include "funkcijos.h"

using namespace std;

// Zodziu skaiciavimas
unordered_map<string, int> count_words(const string& text) {
    unordered_map<string, int> word_count;
    istringstream stream(text);
    string word;
    while (stream >> word) {
		// Tikrinama ar zodis sudarytas tik is raidziu
        bool isWord = true;
        for (char c : word) {
            if (!isalpha(c)) {
                isWord = false;
                break;
            }
        }
        if (isWord && !word.empty()) {
            ++word_count[word];
        }
    }
    return word_count;
}

// Cross-reference lenteles generavimas
unordered_map<string, vector<int>> generate_cross_reference(const string& text) {
    unordered_map<string, vector<int>> word_lines;
    istringstream stream(text);
    string line;
    int line_number = 0;
    while (getline(stream, line)) {
        ++line_number;
        istringstream line_stream(line);
        string word;
        while (line_stream >> word) {
            if (!word.empty()) {
                word_lines[word].push_back(line_number);
            }
        }
    }
    return word_lines;
}

// Zodziu skaiciavimo rezultatu irasymas i faila
void write_word_counts(const unordered_map<string, int>& word_count) {
    ofstream word_count_file("word_counts.txt");
    for (const auto& pair : word_count) {
        if (pair.second > 1) {
            word_count_file << pair.first << ": " << pair.second << endl;
        }
    }
    word_count_file.close();
}


// Cross-reference lenteles irasymas i faila
void write_cross_reference(const unordered_map<string, vector<int>>& word_lines) {
    ofstream cross_reference_file("cross_reference.txt");
    for (const auto& pair : word_lines) {
        if (pair.second.size() > 1) {
            cross_reference_file << pair.first << ": ";
            for (size_t i = 0; i < pair.second.size(); ++i) {
                cross_reference_file << pair.second[i];
                if (i < pair.second.size() - 1) {
                    cross_reference_file << ", ";
                }
            }
            cross_reference_file << endl;
        }
    }
    cross_reference_file.close();
}