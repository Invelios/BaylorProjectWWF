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
#include <string>
#include <set>
#include <vector>
// #include <GameObject>

using namespace std;

struct gameInfo
{
    int theGameId;
    boolean isThePlayersTurn;
    string theOpponetsName;
    GameObject *theGameObject;
};

class MenuLogic
{
    private:

    Networking theNetworkStream;
    set<GameObject> theGameObjectSet;

    public:

    vector<gameInfo> getUsersGames(string theUser);

};

#endif // MENULOGIC_H_INCLUDED
