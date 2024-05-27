#include "funkcijos.h"

using namespace std;

string replace_lithuanian_characters(const string& text) {
    string updated_text = text;

	// Pakeiciamos lietuviskos raides
    updated_text = regex_replace(updated_text, regex("\xc4\x85"), "a"); // ą
    updated_text = regex_replace(updated_text, regex("\xc4\x8d"), "c"); // č
    updated_text = regex_replace(updated_text, regex("\xc4\x99"), "e"); // ę
    updated_text = regex_replace(updated_text, regex("\xc4\x97"), "e"); // ė
    updated_text = regex_replace(updated_text, regex("\xc5\xa1"), "s"); // š
    updated_text = regex_replace(updated_text, regex("\xc5\xb3"), "u"); // ų
    updated_text = regex_replace(updated_text, regex("\xc5\xab"), "u"); // ū
    updated_text = regex_replace(updated_text, regex("\xc5\xbe"), "z"); // ž
    updated_text = regex_replace(updated_text, regex("\xc4\xaf"), "i"); // į
    updated_text = regex_replace(updated_text, regex("\xc4\x84"), "A"); // Ą
    updated_text = regex_replace(updated_text, regex("\xc4\x8c"), "C"); // Č
    updated_text = regex_replace(updated_text, regex("\xc4\x98"), "E"); // Ę
    updated_text = regex_replace(updated_text, regex("\xc4\x96"), "E"); // Ė
    updated_text = regex_replace(updated_text, regex("\xc5\xa0"), "S"); // Š
    updated_text = regex_replace(updated_text, regex("\xc5\xb2"), "U"); // Ų
    updated_text = regex_replace(updated_text, regex("\xc5\xaa"), "U"); // Ū
    updated_text = regex_replace(updated_text, regex("\xc5\xbd"), "Z"); // Ž
    updated_text = regex_replace(updated_text, regex("\xc4\xae"), "I"); // Į

    return updated_text;
}

void remove_formatting(const string& file_path) {

    // Nuskaitomas failas
    ifstream infile(file_path);
    if (!infile.is_open()) {
        cerr << "Unable to open file: " << file_path << endl;
        return;
    }

    stringstream buffer;
    buffer << infile.rdbuf();
    string text = buffer.str();
    infile.close();

	// Istrinami URL
    regex url_pattern(R"((https?://)?(www\.)?\w+\.\w+)");
    smatch url_matches;
    set<string> urls;
    string::const_iterator searchStart(text.cbegin());
    while (regex_search(searchStart, text.cend(), url_matches, url_pattern)) {
        string url = url_matches[0];
		// Patikrinama ar URL nera skaicius
        if (regex_match(url, regex(R"(\d+\.\d+)"))) {
            searchStart = url_matches.suffix().first;
            continue;
        }
        urls.insert(url);
        searchStart = url_matches.suffix().first;
    }

	// URL irasymas i faila
    string urls_file_path = "urls.txt";
    ofstream urls_file(urls_file_path);
    if (!urls_file.is_open()) {
        cerr << "Unable to open file for writing: " << urls_file_path << endl;
        return;
    }

    for (const auto& url : urls) {
        urls_file << url << endl;
    }

    urls_file.close();

    string updated_text = text;

	// Pakeiciamos lietuviskos raides
    updated_text = replace_lithuanian_characters(updated_text);

	// Atnaujintas tekstas irasomas i faila
    string new_file_path = "updated_text.txt";
    ofstream outfile(new_file_path);
    if (!outfile.is_open()) {
        cerr << "Unable to open file for writing: " << new_file_path << endl;
        return;
    }

    outfile << updated_text;
    outfile.close();
}