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

bool Dictionary::verifyWord(string w)
{
    bool found = true;
    if(words.count(w) == 0)
    {
        found = true;
    }

    return found;
}


