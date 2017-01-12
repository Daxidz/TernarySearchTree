/**
 * File       : Dictionary.h
 * Authors    : Lucas ELISEI, Dany TCHENTE & David TRUAN
 *
 * Created on : 12.01.2017
 *
 * Contains the Dictionary class.
 */

#ifndef __DICTIONARY__
#define __DICTIONARY__

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;


/**
 * Enumeration which defines the possible data structures that can be used with the
 * Dictionary class.
 *
 * - DictionaryUnorderedSet : std::unordered_set;
 * - DictionaryTBT          : Own implementation of a Ternary Search Trie.
 */
enum DictionaryType {
    DictionaryUnorderedSet,
    DictionaryTBT
};


/**
 * Class which represents a dictionary.
 */
class Dictionary {

#pragma mark - Private fields

private:
    DictionaryType type;
    unordered_set<string> dictionary;

#pragma mark - Public methods

public:

    /**
     * Dictionary class contructor.
     *
     * - dictionary : Path to the file which contains the dictionary.
     * - type       : Type of the data structure to use.
     */
    Dictionary(const string& dictionary, DictionaryType type) {
        this->type = type;

        // Alerting the user on which implementation is used.
        switch(this->type) {
            case DictionaryUnorderedSet:
                cout << "Using \"unordered_set\" implementation." << endl;
                break;

            case DictionaryTBT:
                cout << "Using \"Ternary Search Trie\" implementation." << endl;
                break;
        }
        cout << "Loading dictionary from " << dictionary << endl;

        // We open the dictionary file. If there is an error, we exit.
        ifstream file(dictionary);
        if(!file) {
            cerr << "Error loading " << dictionary << ". Exiting." << endl;

            exit(EXIT_FAILURE);
        }

        // To know how much time it took to gather the dictionary.
        chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();

        string word;
        while(getline(file, word)) {
            // getline() suppress the line-ending character from the string but it
            // doesn't suppress the carriage-return character so we have to do it.
            if(!word.empty() && word.at(word.size() - 1) == '\r')
                word.erase(word.end() - 1);

            // We convert the word to lowercase letters.
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            // We add the word to the dictionary.
            switch(this->type) {
                case DictionaryUnorderedSet:
                    this->dictionary.insert(word);
                    break;

                //TODO: Implement.
                case DictionaryTBT:
                    break;
            }
        }

        // We get the duration it took to fill the data-structure and we display it.
        chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Dictionary loaded in " << duration.count() << " seconds." << endl;
    }


    /**
     * Returns 'true' if the word passed as argument is in the dictionary, 'false'
     * otherwise.
     */
    bool contains(const string& word) const {
        switch(this->type) {
            case DictionaryUnorderedSet:
                return (this->dictionary.find(word) != this->dictionary.end());

            case DictionaryTBT:
                return false;

            default:
                return false;
        }
    }

};

#endif  // __DICTIONARY__
