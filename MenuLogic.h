/*
    Author      :       Christopher Scoggins
    Title       :       MenuLogic.h
    Date Created:       4/13/12
    Modified on:        By:
        4/13/12             Christopher Scoggins
*/

#ifndef MENULOGIC_H_INCLUDED
#define MENULOGIC_H_INCLUDED

#include "Networking.h"
#include "GUI.h"
#include <string>
#include <set>
#include <vector>

using namespace std;

struct GameInfo
{
    int theGameId;
    bool isThePlayersTurn;
    string theOpponetsName;
};

class MenuLogic
{
    private:

    Networking theNetworkStream;
    set<GameInfo> theGameInfoSet;

    public:

      vector<GameInfo> getUsersGames(string theUser);

};

#endif // MENULOGIC_H_INCLUDED
