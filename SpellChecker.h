/**
 * File       : SpellChecker.h
 * Authors    : Lucas ELISEI, Dany TCHENTE & David TRUAN
 *
 * Created on : 12.01.2017
 *
 * Contains the SpellChecker class.
 */

#ifndef __SPELL_CHECKER__
#define __SPELL_CHECKER__

#include <string>
#include <vector>

#include "Dictionary.h"

using namespace std;


/**
 * Class which is used to spell check given a text file and a dictionary.
 */
class SpellChecker {

#pragma mark - Private fields

private:
    const string& filename;
    const Dictionary& dictionary;

#pragma mark - Public methods

public:

    /**
     * SpellChecker class constructor.
     *
     * - filename : Path to the file to spell check.
     * - dict     : The dictionary to spell check the file with.
     */
    SpellChecker(const string& filename, const Dictionary& dictionary)
        : filename(filename), dictionary(dictionary) {

        //TODO: Implement.

    }

#pragma mark - Private methods

private:

    /**
     * Generates all correct variations of the word passed as argument by deleting
     * a character at any place (i.e. "worrk" --> "work").
     *
     * Returns a vector that contains all those possibilities.
     */
    vector<string> possibilities1ForWord(const string& word);

};

#endif  // __SPELL_CHECKER__
