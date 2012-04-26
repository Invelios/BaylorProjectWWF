/*
    Author      :       Christopher Scoggins
    Title       :       MenuLogic.cpp
    Date Created:       4/13/12
    Modified on:        By:
        4/13/12             Christopher Scoggins
        4/26/12             Christopher Scoggins
*/
#include "MenuLogic.h"

using namespace std;

vector<GameInfo> MenuLogic::getUsersGames(string theUser)
{
    vector<int> theActiveGameIDs( theNetworkStream.getActiveGameID(theUser) );
    vector<GameInfo> theGameInfoVector;

    for( int i = 0; i < theActiveGameIDs.size(); i++ )
    {
        string aGameObject =  theNetworkStream.getGame(theActiveGameIDs[i] );
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
