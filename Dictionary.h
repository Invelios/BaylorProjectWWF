// Title    : Dictionary Header
// Author   : Christopher Scoggins
// Created  : 3/28/12
// Last Mod : 3/28/12
//
// Header File for the Dictionary Class

#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED

#include <set>
#include <string>

using namespace std;

class Dictionary
{

    private:

    // A container for the data. Can try different types of containers

    set<string> words;          // The Set is easy to implement, but will probably be harder to use with the cheat function

    public:

    // Constructor

    Dictionary(){};

    // Loads words from a file into the words set.

    bool loadFile(string filename);

    // Check for the existance of a word in the dictionary

    bool verifyWord(string w);


};



#endif // DICTIONARY_H_INCLUDED
