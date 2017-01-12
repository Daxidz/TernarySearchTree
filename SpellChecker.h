#ifndef __SPELL_CHECKER__
#define __SPELL_CHECKER__

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

/**
 * SpellCheckerUnorderedSet signifie qu'une STD de type 'unordered_set' sera utilisée
 * pour stocker le dictionnaire. Si SpellCheckerTBT est choisi, alors ce sera un
 * arbre ternaire de recherche qui sera utilisé.
 */
enum SpellCheckerType {
    SpellCheckerUnorderedSet,
    SpellCheckerTBT
};

class SpellChecker {

private:
    SpellCheckerType type;
    unordered_set<string> dictionary;

public:

    SpellChecker(const string& dictionary, SpellCheckerType type) {
        this->type = type;

        cout << "Loading dictionary from " << dictionary << endl;

        // On ouvre le fichier.
        ifstream file(dictionary);
        if(!file) {
            cerr << "Error loading " << dictionary << ". Exiting." << endl;

            exit(EXIT_FAILURE);
        }

        // On démarre le timer.
        chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();

        string word;
        while(getline(file, word)) {
            // On supprime les retours à la ligne s'il y en a.
            if(!word.empty() && word.at(word.size() - 1) == '\r')
                word.erase(word.end() - 1);

            // On passe le mot en minuscules.
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            switch(type) {
                case SpellCheckerUnorderedSet:
                    this->dictionary.insert(word);
                    break;

                case SpellCheckerTBT:
                    break;

                default:
                    cerr << "Error retrieving STD type. Exiting." << endl;
                    exit(EXIT_FAILURE);
            }
        }

        // On arrête le timer.
        chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Dictionary loaded in " << duration.count() << " seconds." << endl;
    }

};

#endif  // __SPELL_CHECKER__
