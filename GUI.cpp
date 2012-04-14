#ifndef GUI_CPP
#define GUI_CPP
/*
#include "GUI.h"
#include "Setup.h"

using namespace std;

GameGUI::GameGUI()
{
  theGameBoard->theGUI = this;
};

void GameGUI::CreateGUITile(char letter)
{
  GUITile * newGUITile = NULL;
  int start;
  for(int i = 0; i < DECK_SIZE; i++)
  {
    if(theGameBoard->deck[i] == 0)
    {
      newGUITile = new GUITile(i, letter, this);
      theGameBoard->deck[i] = letter;
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
    if(Deck[boardSpace.first] == 0)
    {
      return true;
    }
  }
  else if(Grid[boardSpace.second][boardSpace.first] == 0)
  {
    return true;
  }
  return false;*/
  /*return true;
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
*/
#endif