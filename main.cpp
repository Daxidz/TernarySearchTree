#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "SpellChecker.h"

#define DICT_FILE   "data/dictionary.txt"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 1) {
        cout << "Error! Too much arguments." << endl << endl;

        cout << "Usage: spell_checker" << endl;

        return EXIT_FAILURE;
    }

    SpellChecker checker(DICT_FILE, SpellCheckerUnorderedSet);

    return EXIT_SUCCESS;
}
