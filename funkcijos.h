#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

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
#include <locale>

using namespace std;

// Funkcija, kuri suskaiciuoja zodziu pasikartojimus tekste
unordered_map<string, int> count_words(const string& text);

// Funkcija, kuri generuoja kryzmines nuorodas tekste
unordered_map<string, vector<int>> generate_cross_reference(const string& text);

// Funkcija, kuri nuskaito URL is teksto
unordered_map<string, int> read_urls(const string& text);

// Funkcija, kuri iraso zodziu pasikartojimus
void write_word_counts(const unordered_map<string, int>& word_count);

// Funkcija, kuri iraso kryzmines nuorodas
void write_cross_reference(const unordered_map<string, vector<int>>& word_lines);

// Funkcija, kuri iraso URL
void write_urls(const unordered_map<string, int>& urls);

// Funkcija, kuri pasalina formatavima is teksto
string remove_formatting(const string& text);

// Funkcija, kuri pakeicia lietuviskas raides i standartines
string replace_lithuanian_characters(const string& text);

#endif