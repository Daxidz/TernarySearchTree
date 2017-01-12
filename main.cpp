/**
 * File       : main.cpp
 * Authors    : Lucas ELISEI, Dany TCHENTE & David TRUAN
 *
 * Created on : 12.01.2017
 *
 * Contains the main program.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#include "Dictionary.h"
#include "SpellChecker.h"

// Defaults values.
#define DEFAULT_DATA_TYPE   DictionaryUnorderedSet
#define DEFAULT_DICT_FILE   "data/dictionary.txt"

using namespace std;

/**
 * Display command-line help.
 */
void displayHelp() {
    cout << "Usage: spell_checker [options]" << endl;
    cout << endl;
    cout << "Options:" << endl;

    cout << " -d=<path>\tSpecify the path of the dictionary file. Default: data/dictionary.txt" << endl;

    cout << " -h\t\t" << "Display this help." << endl;

    cout << " -t=<value>\tSpecify the data type to use. <value> must be one of the following:" << endl;
    cout << "\t\t - set: Use an ordered set. (Default)" << endl;
    cout << "\t\t - tst: Use a ternary search trie." << endl;
}

/**
 * Main program.
 */
int main(int argc, char *argv[]) {
    string dictionaryPath(DEFAULT_DICT_FILE);
    string filePath("data/input_lates.txt");
    DictionaryType type(DEFAULT_DATA_TYPE);

    if(argc > 1) {
        if(!strcmp(argv[1], "-h")) {
            displayHelp();

            return EXIT_SUCCESS;
        }

        for(int i = 1; i < argc - 1; ++i) {
            if(!strncmp(argv[i], "-d=", 3)) {
                dictionaryPath = argv[i] + 3;
            }
            else if(!strncmp(argv[i], "-t=", 3)) {
                if(!strcmp(argv[i] + 3, "tst")) {
                    type = DictionaryTST;
                }
            }
            else {
                cout << "Unknown option: " << argv[i] << endl;
                displayHelp();

                return EXIT_FAILURE;
            }
        }
    }

    Dictionary dictionary(dictionaryPath, type);

    SpellChecker checker(filePath, dictionary);

    return EXIT_SUCCESS;
}
