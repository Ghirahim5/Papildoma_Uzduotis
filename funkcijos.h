#ifndef PGR_FUNKCIJOS_H
#define PGR_FUNKCIJOS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

unordered_map<string, int> count_words(const string& text);
unordered_map<string, vector<int>> generate_cross_reference(const string& text);
void write_word_counts(const unordered_map<string, int>& word_count);
void write_cross_reference(const unordered_map<string, vector<int>>& word_lines);
string replace_lithuanian_characters(const string& text);
void remove_formatting(const string& file_path);

#endif