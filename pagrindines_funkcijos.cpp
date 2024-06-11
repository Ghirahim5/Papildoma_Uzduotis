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
    // Skaitome eilutes is srauto
    while (getline(stream, line)) {
        ++line_number;
        istringstream line_stream(line);
        string word;
        // Skaitome zodzius is eilutes
        while (line_stream >> word) {
            if (!word.empty()) {
                // Irasome zodzio eilutes numeri i zemelapi
                word_lines[word].push_back(line_number);
            }
        }
    }
    // Graziname zodziu eiluciu numeriu zemelapi
    return word_lines;
}

// TLD skaitymas is failo
vector<string> read_tlds(const string& file_path) {
    vector<string> tlds;
    ifstream file(file_path);
    if (file.is_open()) {
        string tld;
        while (getline(file, tld)) {
            tlds.push_back("." + tld);
        }
        file.close();
    }
    return tlds;
}

// URL skaitymas is teksto
unordered_map<string, int> read_urls(const string& text, const vector<string>& tlds) {
    regex url_pattern(R"((https?://)?(www\.)?\w+\.\w+(\.\w+)?)");
    smatch url_matches;
    unordered_map<string, int> urls;
    string::const_iterator searchStart(text.cbegin());
    while (regex_search(searchStart, text.cend(), url_matches, url_pattern)) {
        string url = url_matches[0];
        if (regex_match(url, regex(R"(\d+\.\d+)"))) {
            searchStart = url_matches.suffix().first;
            continue;
        }
		// Tikrinima ar URL turi tinkama TLD
        bool valid_tld = false;
        for (const auto& tld : tlds) {
            if (url.size() >= tld.size() && url.compare(url.size() - tld.size(), tld.size(), tld) == 0) {
                valid_tld = true;
                break;
            }
        }
        if (valid_tld) {
            ++urls[url];
        }
        searchStart = url_matches.suffix().first;
    }
    return urls;
}


// Sakiniu turinciu "oro" spausdinimas
void write_sentences_with_word(const string& text) {
    // Atidarome faila irasymui
    ofstream output_file("sentences_with_word.txt");
    // Jei nepavyksta atidaryti failo, isvedame klaidos pranesima
    if (!output_file.is_open()) {
        cerr << "Unable to open file for writing: sentences_with_word.txt" << endl;
        return;
    }

    istringstream sentence_stream(text);
    string sentence;
    regex word_regex("oro");

    // Ieskoma sakiniu su "oro"
    while (getline(sentence_stream, sentence, '.')) {
        if (regex_search(sentence, word_regex)) {
            // Isvedami sakiniai su "oro" ir gale sakinio pridedamas taskas
            output_file << sentence << '.' << endl;
        }
    }

    // Uzdaryti faila
    output_file.close();
}

// Zodziu skaiciavimo rezultatu irasymas i faila
void write_word_counts(const unordered_map<string, int>& word_count) {
    // Atidarome faila irasymui
    ofstream word_count_file("word_counts.txt");
    // Iteruojame per zodziu skaiciavimo rezultatus
    for (const auto& pair : word_count) {
        // Irasome tik tuos zodzius, kurie pasikartojo daugiau nei viena karta
        if (pair.second > 1) {
            word_count_file << pair.first << ": " << pair.second << endl;
        }
    }
    // Uzdaryti faila
    word_count_file.close();
}

// Cross-reference lenteles irasymas i faila
void write_cross_reference(const unordered_map<string, vector<int>>& word_lines) {
    // Atidarome faila irasymui
    ofstream cross_reference_file("cross_reference.txt");
    // Iteruojame per zodziu eiluciu numeriu rezultatus
    for (const auto& pair : word_lines) {
        // Irasome tik tuos zodzius, kurie pasikartojo daugiau nei viena karta
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
    // Uzdaryti faila
    cross_reference_file.close();
}

// URL irasymas i faila
void write_urls(const unordered_map<string, int>& urls) {
    // Nurodome failo kelia
    string urls_file_path = "urls.txt";
    // Atidarome faila irasymui
    ofstream urls_file(urls_file_path);
    // Jei nepavyksta atidaryti failo, isvedame klaidos pranesima
    if (!urls_file.is_open()) {
        cerr << "Unable to open file for writing: " << urls_file_path << endl;
        return;
    }

    // Iteruojame per URL zemelapi ir irasome URL i faila
    for (const auto& url : urls) {
        urls_file << url.first << endl;
    }

    // Uzdaryti faila
    urls_file.close();
}