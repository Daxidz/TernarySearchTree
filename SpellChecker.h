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
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>

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
     * - filename   : Path to the file to spell check.
     * - dictionary : The dictionary to spell check the file with.
     */
    SpellChecker(const string& filename, const Dictionary& dictionary)
        : filename(filename), dictionary(dictionary) {

        //TODO: Check if we can do better

        // To know how much time it took to spell check the file
        chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();

        ifstream textToCheck(filename);
        ofstream output ("output.txt",ofstream::out);

        if(!textToCheck) {
            cerr << "Error loading " << filename << ". Exiting." << endl;
            exit(EXIT_FAILURE);
        }

        string line;
        while (getline(textToCheck, line)) {
            smatch m;
            // take all the words beginning with a alphabetic character and with
            // only alphabetic or ' chara
            regex e ("\\b[A-Za-z']+\\b");   // matches words beginning by "sub"
            //regex e ("[A-Za-z]+([A-Za-z'][A-Za-z])*");

            while (regex_search (line, m, e)) {
                string mot = m.str(0);
                transform(mot.begin(), mot.end(), mot.begin(), ::tolower);
                if(!dictionary.contains(mot)){
                    //cout << endl << '*' << mot << endl;
                    output << '*' << mot << endl;
                    for(string str : possibilities1ForWord(mot))
                        //cout << "1. " << str << endl;
                        output << "1. " << str << endl;
                    for(string str : possibilities2ForWord(mot))
                        //cout << "2. " << str << endl;
                        output << "2. " << str << endl;
                    for(string str : possibilities3ForWord(mot))
                        //cout << "3. " << str << endl;
                        output << "3. " << str << endl;
                    for(string str : possibilities4ForWord(mot))
                        //cout << "4. " << str << endl;
                        output << "4. " << str << endl;
                }

                line = m.suffix().str();
            }
        }

        // We get the duration it took to check the spell and we display it.
        chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "\n\nFile spell checked in " << duration.count() << " seconds." << endl;
        textToCheck.close();
    }


#pragma mark - Private methods

private:

    /**
     * Generates all correct variations of the word passed as argument by deleting
     * a character at any place (i.e. "worrk" --> "work").
     *
     * Returns a vector that contains all those possibilities.
     */
    vector<string> possibilities1ForWord(const string& word) {
        vector<string> result;
        for (size_t i = 0; i < word.length(); ++i) {
            // we work on a copy of word
            string cpy = word;
            // suppression of the letter
            cpy.erase(cpy.begin() + i);
            // check if the new word is in the dictionary
              if(dictionary.contains(cpy) && !(find(result.begin(), result.end(), cpy) != result.end()))
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
            // we work on a copy of word
            string cpy = word;
            // insertion of all possible letters
            for(char c = 'a'; c <= 'z'; ++c) {
                cpy.insert(cpy.begin()+i, c);
                // check if the new word is in the dictionary
                if(dictionary.contains(cpy) && !(find(result.begin(), result.end(), cpy) != result.end()))
                  result.push_back(cpy);
                cpy.erase(cpy.begin() + i);
            }
            cpy.insert(cpy.begin() + i, '\'');
            if(dictionary.contains(cpy) && !(find(result.begin(), result.end(), cpy) != result.end()))
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
            // we work on a copy of word
            string cpy = word;
            // insertion of all possible letters
            for(char c = 'a'; c <= 'z'; ++c) {
                cpy[i] = c;
                // check if the new word is in the dictionary
                if(dictionary.contains(cpy) && !(find(result.begin(), result.end(), cpy) != result.end()))
                  result.push_back(cpy);
            }
            // add the char ' outside of the loop
            cpy[i] = '\'';
            // check if the new word is in the dictionary
            if(dictionary.contains(cpy) && !(find(result.begin(), result.end(), cpy) != result.end()))
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
            // we work on a copy of word
            string cpy = word;
            // swap of the two characters
            swap(cpy[i], cpy[i+1]);
            // check if the new word is in the dictionary
            if(dictionary.contains(cpy) && !(find(result.begin(), result.end(), cpy) != result.end()))
                result.push_back(cpy);
        }
        return result;
    }
};

#endif  // __SPELL_CHECKER__
