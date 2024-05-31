#include "funkcijos.h"

int main() {

    ifstream infile("text.txt");
    stringstream buffer;
    buffer << infile.rdbuf();
    string text = buffer.str();

    auto urls = read_urls(text);

    auto updated_text = remove_formatting(text);

    // Zodziu skaiciavimas
    auto word_count = count_words(updated_text);
    auto word_lines = generate_cross_reference(updated_text);    

    // Isvedimas i word_counts.txt
    write_word_counts(word_count);

    // Isvedimas i cross_reference.txt
    write_cross_reference(word_lines);

	// Isvedimas i urls.txt
	write_urls(urls);

    return 0;
}
