/*
    Author      :       Christopher Scoggins
    Title       :       MenuLogic.cpp
    Date Created:       4/13/12
    Modified on:        By:
        4/13/12             Christopher Scoggins
*/

#include "MenuLogic.h"
#include <set>
#include <string>

using namespace std;

vector<gameInfo> MenuLogic::getUsersGames(string theUser)
{
    vector<int> theActiveGameIDs( theNetworkStream.getActiveGameID(theUser) );
    vector<gameInfo> theGameInfoVector

    for( int i = 0; i < theActiveGameIDs.size(); i++ )
    {
        GameObject aGameObject =  theNetworkStream.getGame(theActiveGameIDs[i] ) ;
        theGameObjectSet.add(aGameObject);
        gameInfo aGameInfo;                                                                     // Will need to edit when Josh finished actual GameObject
        aGameInfo.theGameId = aGameObject.getId();
        aGameInfo.isThePlayersTurn = aGameObject.isThePlayersTurn();
        aGameInfo.theOpponetsName = aGameObject.theOpponetsName();
        aGameInfo.theGameObject = (GameObject*) theGameObjectSet.find(aGameObject);
        theGameInfoVector.add(aGameInfo);
    }

    return theGameInfoVector;

}

