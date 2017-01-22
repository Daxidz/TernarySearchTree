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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "Dictionary.h"

#define DEFAULT_DATA_DIR "data/"

using namespace std;


/**
 * Class which is used to spell check given a text file and a dictionary->
 */
class SpellChecker {

private:
    Dictionary* dictionary;

public:

    /**
     * SpellChecker class constructor.
     *
     * - filename   : Path to the file to spell check.
     * - dictionary : The dictionary to spell check the file with.
     */
    SpellChecker(const string& filename, Dictionary* dictionary) : dictionary(dictionary) {
        string outputFilename("output_" + dictionary->type() + "_" + filename);

        ifstream textToCheck(DEFAULT_DATA_DIR + filename);
        ofstream output(outputFilename, ofstream::out);

        if(!textToCheck) {
            cerr << "Error loading " << filename << ". Exiting." << endl;
            output.close();
            textToCheck.close();
            exit(EXIT_FAILURE);
        }

        cout << "Spell checking file: " << filename << endl;

        string line;

        // To know how much time it took to spell check the file
        chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
        while (getline(textToCheck, line)) {
            smatch m;

            // We apply a regex to take all the words beginning with an alphabetic
            // character and we only keep alphabetic and ' characters ( ' char
            // is only allowed IN the word i.e.: "Dave's.", 'hello would not be taken).
            regex e("[A-Za-z]+([A-Za-z'][A-Za-z])*");

            while (regex_search (line, m, e)) {
                string word = m.str(0);

                transform(word.begin(), word.end(), word.begin(), ::tolower);

                if(!dictionary->contains(word)) {
                    output << "*" << word << endl;

                    for(string str : possibilities1ForWord(word))
                        output << "1:" << str << endl;

                    for(string str : possibilities2ForWord(word))
                        output << "2:" << str << endl;

                    for(string str : possibilities3ForWord(word))
                        output << "3:" << str << endl;

                    for(string str : possibilities4ForWord(word))
                        output << "4:" << str << endl;
                }

                line = m.suffix().str();
            }
        }

        // We get the duration it took to check the spell and we display it.
        chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "File spell checked in " << duration.count() << " seconds." << endl;

        output.close();
        textToCheck.close();

        cout << "Output: " << outputFilename << endl;
    }


private:

    /**
     * Generates all correct variations of the word passed as argument by deleting
     * a character at any place (i.e. "worrk" --> "work").
     *
     * Returns a vector that contains all those possibilities.
     */
    vector<string> possibilities1ForWord(const string& word) {
        vector<string> result;

        for(size_t i = 0; i < word.length(); ++i) {
            // We work on a copy of the word
            string cpy(word);

            // Suppression of the letter
            cpy.erase(cpy.begin() + (long)i);

            // Check if the new word is in the dictionary
              if(dictionary->contains(cpy) && (find(result.begin(), result.end(), cpy) == result.end()))
                  result.push_back(cpy);
        }

        return result;
    }


    /**
     * Generates all correct variations of the word passed as argument by adding
     * a character at any place (i.e. "wrk" --> "work").
     *
     * Returns a vector that contains all those possibilities.
     */
    vector<string> possibilities2ForWord(const string& word) {
        vector<string> result;

        for (size_t i = 0; i < word.length(); ++i) {
            // We work on a copy of word
            string cpy(word);

            // Insertion of all possible letters
            for(char c = 'a'; c <= 'z'; ++c) {
                cpy.insert(cpy.begin() + (long)i, c);

                // Check if the new word is in the dictionary
                if(dictionary->contains(cpy) && (find(result.begin(), result.end(), cpy) == result.end()))
                  result.push_back(cpy);

                cpy.erase(cpy.begin() + (long)i);
            }

            cpy.insert(cpy.begin() + (long)i, '\'');
            if(dictionary->contains(cpy) && (find(result.begin(), result.end(), cpy) == result.end()))
                result.push_back(cpy);
        }

        return result;
    }

    /**
     * Generates all correct variations of the word passed as argument by replacing
     * a character at any place (i.e. "wprk" --> "work").
     *
     * Returns a vector that contains all those possibilities.
     */
    vector<string> possibilities3ForWord(const string& word) {
        vector<string> result;

        for (size_t i = 0; i < word.length(); ++i) {
            // We work on a copy of the word
            string cpy(word);

            // Insertion of all possible letters
            for(char c = 'a'; c <= 'z'; ++c) {
                cpy[i] = c;
                // Check if the new word is in the dictionary
                if(dictionary->contains(cpy) && (find(result.begin(), result.end(), cpy) == result.end()))
                  result.push_back(cpy);
            }

            // Add the char ' outside of the loop
            cpy[i] = '\'';
            // Check if the new word is in the dictionary
            if(dictionary->contains(cpy) && (find(result.begin(), result.end(), cpy) == result.end()))
                result.push_back(cpy);
        }

        return result;
    }

    /**
     * Generates all correct variations of the word passed as argument by swaping
     * all the two adjacent characters (max once) (i.e. "wrok" --> "work").
     *
     * Returns a vector that contains all those possibilities.
     */
    vector<string> possibilities4ForWord(const string& word) {
        vector<string> result;

        for (size_t i = 0; i < word.length() - 1; ++i) {
            // Ee work on a copy of word
            string cpy(word);

            // Swap of the two characters
            swap(cpy[i], cpy[i + 1]);

            // Check if the new word is in the dictionary
            if(dictionary->contains(cpy) && (find(result.begin(), result.end(), cpy) == result.end()))
                result.push_back(cpy);
        }

        return result;
    }
};

#endif  // __SPELL_CHECKER__
