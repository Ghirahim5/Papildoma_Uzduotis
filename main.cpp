#include "funkcijos.h"

int main() {

    ifstream infile("text.txt");
    stringstream buffer;
    buffer << infile.rdbuf();
    string text = buffer.str();

    auto tlds = read_tlds("tlds.txt");
    auto urls = read_urls(text, tlds);

    auto updated_text = remove_formatting(text);

    // Zodziu skaiciavimas
    auto word_count = count_words(updated_text);
    auto word_lines = generate_cross_reference(updated_text);

    // Sakiniu su "oro" isvedimas
    write_sentences_with_word(text);

    // Isvedimas i word_counts.txt
    write_word_counts(word_count);

    // Isvedimas i cross_reference.txt
    write_cross_reference(word_lines);

	// Isvedimas i urls.txt
	write_urls(urls);

    return 0;
}
