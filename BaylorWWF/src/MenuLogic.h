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

using namespace std;

class Networking;

struct GameInfo
{
public:
    int theGameId;
    bool isThePlayersTurn;
    string theOpponetsName;
};

class MenuLogic
{
private:
    Networking * theNetworkStream;
    set<GameInfo> theGameInfoSet;

public:
  MenuLogic(){theNetworkStream = Networking::getInstance();}
      vector<GameInfo> getUsersGames(string theUser);

};

vector<GameInfo> MenuLogic::getUsersGames(string theUser)
{
    vector<int> theActiveGameIDs( theNetworkStream->getActiveGameID(theUser) );
    vector<GameInfo> theGameInfoVector;

    for( int i = 0; i < theActiveGameIDs.size(); i++ )
    {
        string aGameObject =  theNetworkStream->getGame(theActiveGameIDs[i] );
        GameInfo aGameInfo;

        string tempString;
        string tmpStr;

          int s = 0;

          for(; aGameObject[s] != '\n'; s++)
          {
              tempString += aGameObject[s];
          }

          aGameInfo.theGameId = atoi(tempString.c_str());

          tempString.clear();

          s++;

          for(; aGameObject[s] != '\n'; s++)
          {
            tempString += aGameObject[s];
          }
          tmpStr = tempString;

          s++;

          for(; aGameObject[s] != '\n'; s++)
          {
            tempString += aGameObject[s];
          }

          aGameInfo.theOpponetsName = tempString;

          if(tempString == tmpStr)
          {
              aGameInfo.isThePlayersTurn = false;
          }
          else
          {
              aGameInfo.isThePlayersTurn = true;
          }

        theGameInfoVector.push_back(aGameInfo);
    }

    return theGameInfoVector;

}


#endif // MENULOGIC_H_INCLUDED
