#ifndef GUI_H
#define GUI_H
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

using namespace std;

class GameGUI;
class GameBoard;

class GoButton
{
public:
  bool pressed;
  SDL_Rect box;
  SDL_Rect * clip;
  GoButton();
  GameGUI * theGUI;
  GoButton(GameGUI*);
  void handle_events();
  void show();
  void flashImage();
  void resetImage();
};

class GameGUI
{
public:
  GameBoard * theGameBoard;
  vector<GUITile> allGUITiles;
  GoButton * theButton;
  GameGUI();
  void CreateGUITile(char letter);
  void handle_events();
  void show();
};

//const SDL_Rect GameGUI::goButton = {384, 544, 64, 32};
struct Tile
{
  pair<int, int> location;
  char face;
};

class GUITile
{
    private:
    //The attributes of the button
    SDL_Rect box;
    pair<int, int> boardSpace;
    pair<int, int> previousSpace;

    char face;
    
    GameGUI * theGUI;
    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;

    bool dragged;
    
    public:
    //Initialize the variables
    GUITile(int start, char letter, GameGUI * theGUI);
    //Handles events and set the button's sprite region
    void handle_events();
    //Shows the button on the screen
    void show();
    bool isDragged();
    void placeGUITile(int x, int y);
    bool getSpace(int x, int y);
    bool verifySpace();
    void setCoordinates();
};

GameGUI::GameGUI()
{
  theGameBoard = new GameBoard;
  theButton = new GoButton(this);
};


void GameGUI::CreateGUITile(char letter)
{
  GUITile * newGUITile = NULL;
  int start;
  for(int i = 0; i < DECK_SIZE; i++)
  {
    if(theGameBoard->deck1[i] == 0)
    {
      newGUITile = new GUITile(i, letter, this);
      theGameBoard->deck1[i] = letter;
      break;
    }
  }
  allGUITiles.push_back(*newGUITile);
}

GUITile::GUITile(int start, char letter, GameGUI * aGUI)
{
    //Set the button's attributes
    box.x = start * TILE_SIZE;
    box.y = SCREEN_HEIGHT - SCREEN_BOTTOM_MARGIN;
    box.w = 32;
    box.h = 32;

    boardSpace.first = start;
    boardSpace.second = -1;

    previousSpace = boardSpace;

    dragged = false;

    face = letter;

    theGUI = aGUI;
    
    //Set the default sprite
    clip = &clips[letter - 65];
}

void GUITile::show()
{
    //Show the button
    apply_surface( box.x, box.y, TileSheet, screen, clip );
}

void GUITile::handle_events()
{
    //The mouse offsets
    int x = 0, y = 0;

    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                dragged = true;
            }
        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if(dragged && event.button.button == SDL_BUTTON_LEFT)
        {
            dragged = false;
            placeGUITile(event.button.x, event.button.y);
        }
    }
    //if the GUITile is attached
    if(dragged && event.type == SDL_MOUSEMOTION)
    {
        //Get the mouse offsets
        box.x = event.motion.x - TILE_SIZE / 2;
        box.y = event.motion.y - TILE_SIZE / 2;

    } 
}

bool GUITile::isDragged()
{
  return dragged;
}

bool GUITile::getSpace(int x, int y)
{
  if(x > 0 && x < SCREEN_WIDTH && y > SCREEN_TOP_MARGIN && y < SCREEN_HEIGHT)
  {
    if(y < SCREEN_HEIGHT - SCREEN_BOTTOM_MARGIN)
    {
      boardSpace.second = (y - SCREEN_TOP_MARGIN) / TILE_SIZE;
      boardSpace.first = (x - 0) / TILE_SIZE;
      return true;
    }
    else
    {
      if(x < 224)
      {
        boardSpace.second = -1;
        boardSpace.first = (x - 0) / TILE_SIZE;
        return true;
      }
    }
  }
  return false;
  //Board.attachGUITile(GUITile, i, j, face)
}

bool GUITile::verifySpace()
{/*
  if(boardSpace.second == -1)
  {
    if(deck1[boardSpace.first] == 0)
    {
      return true;
    }
  }
  else if(Grid[boardSpace.second][boardSpace.first] == 0)
  {
    return true;
  }
  return false;*/
  return true;
}

void GUITile::placeGUITile(int x, int y)
{
  bool success = false;
  if(getSpace(x, y))
  {
    if(boardSpace.second == -1)
    {
      success = theGUI->theGameBoard->placeDeckSquare(boardSpace.first, face);
    }
    else
    {
      success = theGUI->theGameBoard->placeSquare(boardSpace.first, boardSpace.second, face);
    }
  }
  if(success)
  {
    if(previousSpace.second == -1)
    {
      theGUI->theGameBoard->removeDeckSquare(previousSpace.first);
    }
    else
    {
      theGUI->theGameBoard->removeSquare(previousSpace);
    }
    previousSpace = boardSpace;
  }
  else
  {
    boardSpace = previousSpace;
  }
  setCoordinates();
}

void GUITile::setCoordinates()
{
  if(boardSpace.second == -1)
  {
    box.x = boardSpace.first * TILE_SIZE;
    box.y = 544;
  }
  else
  {
    box.x = boardSpace.first * TILE_SIZE;
    box.y = boardSpace.second * TILE_SIZE + SCREEN_TOP_MARGIN;
  }
}

void GameGUI::handle_events()
{
  for(int i = 0; i < allGUITiles.size(); i++)
  {
    allGUITiles[i].handle_events();
  }
  theButton->handle_events();
}

void GoButton::handle_events()
{
  //The mouse offsets
    int x = 0, y = 0;

    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                pressed = true;
                flashImage();
            }
        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if(pressed && event.button.button == SDL_BUTTON_LEFT)
        {
            pressed = false;
            resetImage();
            theGUI->theGameBoard->verifyPlay();
            //GO GO GO!
        }
    }
    //if the GUITile is attached
    if(pressed && event.type == SDL_MOUSEMOTION)
    {
        //Get the mouse offsets
      if(event.motion.x < 384 || event.motion.x > 480 ||
         event.motion.y < 544 || event.motion.y > 576)
      {
         pressed = false;
         resetImage();
      }
    } 
}

void GoButton::show()
{
    apply_surface( box.x, box.y, TileSheet, screen, clip );
}

void GameGUI::show()
{
  for(int i = 0; i < allGUITiles.size(); i++)
  {
    allGUITiles[i].show();
  }
  theButton->show();
}

void GoButton::flashImage()
{
  clip = &clips[39];
}

void GoButton::resetImage()
{
  clip = &clips[33];
}

GoButton::GoButton(GameGUI* aGUI)
{
  theGUI = aGUI;
  pressed = false;
  box.x = 384;
  box.y = 544;
  box.w = 96;
  box.h = 32;
  clip = &clips[33];
}
#endif