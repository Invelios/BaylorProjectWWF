// Title    : Dictionary Implementation
// Author   : Christopher Scoggins
// Created  : 3/28/12
// Last Mod : 3/28/12
//
// Implements Dictionary Class Functions

#include "Dictionary.h"
#include <set>
#include <fstream>

using namespace std;

//************************************************************
// Desription: Loads the Dictionary from a file
// Return: bool success
// Pre: Dictionary was constructed
// Post: Word Set will contain all words in the file
//************************************************************

bool Dictionary::loadFile(string filename)
{
    bool success = false;
    ifstream dataFile;
    dataFile.open(filename.c_str());

    if(dataFile)
    {
        success = true;
        string reader;

        while(dataFile >> reader)
        {
            words.insert(reader);
        }
    }

    dataFile.close();
    dataFile.clear();

    return success;
}

//************************************************************
// Desription: Will tell weather the input string is in the dictionary
// Return: bool
// Pre: The dictionary has been loaded
// Post: No change to dictionary
//************************************************************

bool Dictionary::verifyWord(string w)
{
    bool found = true;
    if(words.count(w) == 0)
    {
        found = false;
    }

    return found;
}


