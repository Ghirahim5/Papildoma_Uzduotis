#include "funkcijos.h"

int main() {
    string file_path = "tekstas.txt";
    remove_formatting(file_path);

    ifstream infile("atnaujintas_tekstas.txt");
    stringstream buffer;
    buffer << infile.rdbuf();
    string text = buffer.str();

    // Zodziu skaiciavimas
    auto word_count = count_words(text);
    auto word_lines = generate_cross_reference(text);

    // Isvedimas i word_counts.txt
    write_word_counts(word_count);

    // Isvedimas i cross_reference.txt
    write_cross_reference(word_lines);

    return 0;
}
