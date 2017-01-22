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

#include "TernarySearchTree.h"

#define DEFAULT_DATA_DIR    "data/"

using namespace std;


/**
 * Class which represents a dictionary.
 */
class Dictionary {

protected:

    void populate(const string& filename) {
        cout << "Loading dictionary from " << filename << endl;

        // We open the dictionary file. If there is an error, we exit.
        ifstream file(DEFAULT_DATA_DIR + filename);
        if(!file) {
            cerr << "Error loading " << filename << ". Exiting." << endl;

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
            insert(word);
        }

        // We get the duration it took to fill the data-structure and we display it.
        chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Dictionary loaded in " << duration.count() << " seconds." << endl;
    }

public:

    virtual bool contains(const string& key) = 0;
    virtual void insert(const string& key) = 0;
    virtual string type() = 0;

};


class DictionarySet : public Dictionary {

private:
    unordered_set<string>* set;

public:

    DictionarySet(const string& filename) {
        cout << "Using unordered_set implementation." << endl;

        set = new unordered_set<string>();

        populate(filename);
    }

    /**
     * Returns 'true' if the word passed as argument is in the dictionary, 'false'
     * otherwise.
     */
    bool contains(const string& key) {
        return (set->find(key) != set->end());
    }

    void insert(const string& key) {
        set->insert(key);
    }

    string type() {
        return "set";
    }

};


class DictionaryTST : public Dictionary {

private:
    TernarySearchTree *tree;

public:

    DictionaryTST(const string& filename) {
        cout << "Using Ternary Search Tree implementation." << endl;

        tree = new TernarySearchTree();

        this->populate(filename);
    }

    /**
     * Returns 'true' if the word passed as argument is in the dictionary, 'false'
     * otherwise.
     */
    bool contains(const string& key) {
        return tree->contains(key);
    }

    void insert(const string& key) {
        tree->insert(key);
    }

    string type() {
        return "tst";
    }

};

#endif  // __DICTIONARY__
