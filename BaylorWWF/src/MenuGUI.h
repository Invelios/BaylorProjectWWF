#ifndef MENUGUI_H
#define MENUGUI_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
//#include "GameState.h"
#include "Setup.h"
#include "GameBoard.h"
#include "MenuLogic.h"
#include "Button.h"
#include <vector>
#include <set>
#include <string>

using namespace std;

class GameIcon
{
private:
    Button * theButton;
    int theGameNumber;
    
public:
  GameInfo theGameInfo;
    GameIcon(GameInfo aGameInfo, int aGameNumber);

    int handle_events();

    void show();
};

GameIcon::GameIcon(GameInfo aGameInfo, int aGameNumber)
{
  theGameInfo = aGameInfo;
  theGameNumber = aGameNumber;
  theButton = (new Button(32 + 224*(aGameNumber/12), 48*(aGameNumber%12), menuClips[aGameNumber % 5].w, menuClips[aGameNumber %5].h, aGameNumber % 5, 5));
}

int GameIcon::handle_events()
{
  return theButton->handle_events();
}

void GameIcon::show()
{
  string turnMessage;
  char buffer[10];
  turnMessage += itoa(theGameInfo.theGameId, buffer, 10);
  if(theGameInfo.isThePlayersTurn)
  {
    turnMessage += ": Your turn!";
  }

  SDL_Surface * tileOut = TTF_RenderText_Solid(font, turnMessage.c_str(), textColor);
  apply_surface(theButton->box.x, theButton->box.y, menuTiles, screen, theButton->clip);
  apply_surface(theButton->box.x, theButton->box.y, tileOut, screen, theButton->clip);
}

class MenuGUI
{
  SDL_Surface * menuBackground;
  vector<GameIcon> theGameIconSet;
  Button * newGameButton;
  MenuGUI();
  MenuLogic * theLogic;
  int numberOfGames;
public:
   int mainGameId;
  MenuGUI(string userName);
  void createGameIcon(GameInfo aGameInfo, int aGameNumber);
  int run();
};

MenuGUI::MenuGUI(string userName)
{
  newGameButton = new Button(0, 0, 32, 32, 9, 10);
  theLogic = new MenuLogic();
  menuBackground = load_image("menuBackground.png");
  vector<GameInfo> gameInfoSet = theLogic->getUsersGames(userName);
  for(int i = 0; i < gameInfoSet.size(); i++)
  {
    createGameIcon(gameInfoSet[i], i);
  }
  /*GameInfo * tempInfo = new GameInfo;
  tempInfo->isThePlayersTurn = true;
  tempInfo->theGameId = 555555;
  tempInfo->theOpponetsName = "George Casela";
  createGameIcon(*tempInfo, 0);*/
}

void MenuGUI::createGameIcon(GameInfo aGameInfo, int aGameNumber)
{
  theGameIconSet.push_back(GameIcon(aGameInfo, aGameNumber));
}

int MenuGUI::run()
{
  while(SDL_PollEvent( &event ))
  {
    for(int i = 0; i < theGameIconSet.size(); i++)
    {
      if(theGameIconSet[i].handle_events() == 5)
      {
        mainGameId = theGameIconSet[i].theGameInfo.theGameId;
        return 5;
      }
    }
    if(newGameButton->handle_events() == 10)
    {
      return 4;
    }
  }

  apply_surface(0, 0, menuBackground, screen);
  for(int i = 0; i < theGameIconSet.size(); i++)
  {
    theGameIconSet[i].show();
  }
  newGameButton->show();
  return 3;
}



class NewGameState
{
public:
  GameGUI * theGameGUI;
  int run();
  NewGameState();
};

NewGameState::NewGameState()
{
  theGameGUI = new GameGUI();
}

int NewGameState::run()
{
  while(SDL_PollEvent(&event)) 
  {
    theGameGUI->handle_events();
  }
  theGameGUI->show();
  return 6;
}
#endif