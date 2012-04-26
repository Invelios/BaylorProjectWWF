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
// #include <GameBoard>

using namespace std;

class Networking;

struct gameInfo
{
    int theGameId;
    bool isThePlayersTurn;
    string theOpponetsName;
    GameBoard *theGameBoard;
};

class MenuLogic
{
    private:

    Networking theNetworkStream();
    set<GameBoard> theGameBoardSet;

    public:

      vector<gameInfo> getUsersGames(string theUser){vector<gameInfo> bob; return bob;}

};

#endif // MENULOGIC_H_INCLUDED
