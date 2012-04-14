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
#include <vector>
#include <set>
#include <string>

using namespace std;

class GameIcon
{
private:
    SDL_Rect box;
    GameInfo theGameInfo;
    int theGameNumber;

    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;
    
public:
    GameIcon(GameInfo aGameInfo, int aGameNumber);

    void handle_events();

    void show();
};

GameIcon::GameIcon(GameInfo aGameInfo, int aGameNumber)
{
  theGameInfo = aGameInfo;
  theGameNumber = aGameNumber;
  SDL_Rect* clip;
}

class MenuGUI
{
  vector<GameIcon> theGameSet;
  MenuGUI();
  void createGameIcon(GameInfo aGameInfo, int aGameNumber);
};

MenuGUI::MenuGUI(string userName)
{
  vector<GameInfo> gameInfoSet = getUsersGames(userName);
  for(int i = 0; i < gameInfoSet.size(); i++)
  {
    createGameIcon(gameInfoSet[i], i);
  }
}

void MenuGUI::createGameIcon(GameInfo aGameInfo, int aGameNumber)
{
  theGameSet.push(aGameInfo, aGameNumber);
}
#endif