#include "funkcijos.h"

using namespace std;

string replace_lithuanian_characters(const string& text) {
    string updated_text = text;

    // Pakeiciamos lietuviskos raides
    updated_text = regex_replace(updated_text, regex("\xc4\x85"), "a"); // a
    updated_text = regex_replace(updated_text, regex("\xc4\x8d"), "c"); // c
    updated_text = regex_replace(updated_text, regex("\xc4\x99"), "e"); // e
    updated_text = regex_replace(updated_text, regex("\xc4\x97"), "e"); // e
    updated_text = regex_replace(updated_text, regex("\xc5\xa1"), "s"); // s
    updated_text = regex_replace(updated_text, regex("\xc5\xb3"), "u"); // u
    updated_text = regex_replace(updated_text, regex("\xc5\xab"), "u"); // u
    updated_text = regex_replace(updated_text, regex("\xc5\xbe"), "z"); // z
    updated_text = regex_replace(updated_text, regex("\xc4\xaf"), "i"); // i
    updated_text = regex_replace(updated_text, regex("\xc4\x84"), "A"); // A
    updated_text = regex_replace(updated_text, regex("\xc4\x8c"), "C"); // C
    updated_text = regex_replace(updated_text, regex("\xc4\x98"), "E"); // E
    updated_text = regex_replace(updated_text, regex("\xc4\x96"), "E"); // E
    updated_text = regex_replace(updated_text, regex("\xc5\xa0"), "S"); // S
    updated_text = regex_replace(updated_text, regex("\xc5\xb2"), "U"); // U
    updated_text = regex_replace(updated_text, regex("\xc5\xaa"), "U"); // U
    updated_text = regex_replace(updated_text, regex("\xc5\xbd"), "Z"); // Z
    updated_text = regex_replace(updated_text, regex("\xc4\xae"), "I"); // I

    return updated_text;
}

string remove_formatting(const string& text) {
    string updated_text = text;

    // Istrinamos nuorodos is teksto ir grazinamas atnaujintas tekstas
    regex url_pattern(R"((https?://)?(www\.)?\w+\.\w+)");
    updated_text = regex_replace(updated_text, url_pattern, "");

    // Pakeiciamos lietuviskos raides
    updated_text = replace_lithuanian_characters(updated_text);

    // Pasalinamos santrumpos
    regex abbreviation_pattern1(R"([A-Za-z]+\.)");
    smatch match1;

    // Ieskoma sablono
    while (regex_search(updated_text, match1, abbreviation_pattern1)) {
        // Pakeiciamas pirmas atitikmuo
        updated_text.replace(match1.position(), match1.length(), "");
    }

    // Pasalinamos santrumpos (pvz. USA)
    regex abbreviation_pattern2(R"(\b[A-Z]+\b)");
    smatch match2;

    while (regex_search(updated_text, match2, abbreviation_pattern2)) {
        // Pakeiciamas pirmas atitikmuo
        updated_text.replace(match2.position(), match2.length(), "");
    }

    // Pasalinamos atskiros didziosios raides (kurios nera sakinio pradzia)
    for (size_t i = 1; i < updated_text.size(); ++i) {
        if (isupper(updated_text[i]) && updated_text[i - 1] == ' ' && updated_text[i - 2] != '.' && updated_text[i + 1] == ' ') {
            updated_text.erase(i, 1);
            --i;
        }
    }

    // Pasalinami matavimo vienetai
    regex length_measurement_pattern(R"(\b\d+(\.\d+)?\s*(km|m|cm|mm|mi|yd|ft|in)\b)");
    smatch match3;

    // Ieskoma sablono
    while (regex_search(updated_text, match3, length_measurement_pattern)) {
        // Pakeiciamas pirmas atitikmuo
        updated_text.replace(match3.position(), match3.length(), "");
    }

    // Pasalinami skyrybos zenklai ir nestandartiniai simboliai
    updated_text.erase(remove_if(updated_text.begin(), updated_text.end(), [](char c) {
        return !isalnum(c) && !isspace(c);
        }), updated_text.end());

    // Pasalinami skliaustai
    updated_text.erase(remove_if(updated_text.begin(), updated_text.end(), [](char c) {
        return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}';
        }), updated_text.end());

    // Pasalinami skaiciai
    updated_text.erase(remove_if(updated_text.begin(), updated_text.end(), [](char c) {
        return isdigit(c);
        }), updated_text.end());

    return updated_text;
}