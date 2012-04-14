#ifndef MENUGUI_H
#define MENUGUI_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include "GameState.h"
#include "Setup.h"
#include "GameBoard.h"
#include "MenuLogic.h"
#include <vector>
#include <set>
#include <string>

using namespace std;

class GameIcon
{
private:
    SDL_Rect box;
    gameInfo theGameInfo;
    int theGameNumber;

    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;
    
public:
    GameIcon(gameInfo aGameInfo, int aGameNumber);

    void handle_events();

    void show();
};

GameIcon::GameIcon(gameInfo aGameInfo, int aGameNumber)
{
  theGameInfo = aGameInfo;
  theGameNumber = aGameNumber;
  SDL_Rect* clip;
}

class MenuGUI
{
  vector<GameIcon> theGameSet;
  MenuGUI();
  MenuLogic * theLogic;
  void createGameIcon(gameInfo aGameInfo, int aGameNumber);
};

MenuGUI::MenuGUI(string userName)
{
  vector<gameInfo> gameInfoSet = theLogic->getUsersGames(userName);
  for(int i = 0; i < gameInfoSet.size(); i++)
  {
    createGameIcon(gameInfoSet[i], i);
  }
}

void MenuGUI::createGameIcon(gameInfo aGameInfo, int aGameNumber)
{
  theGameSet.push(aGameInfo, aGameNumber);
}
#endif