#ifndef GUI_H
#define GUI_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include "GameState.h"
#include "Setup.h"

using namespace std;

char Grid[15][15];
char Deck[7];

class Tile
{
    private:
    //The attributes of the button
    SDL_Rect box;
    pair<int, int> boardSpace;
    pair<int, int> previousSpace;

    char face;
    
    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;

    bool dragged;
    
    public:
    //Initialize the variables
    Tile(int start, char letter);
    
    //Handles events and set the button's sprite region
    void handle_events();
    
    //Shows the button on the screen
    void show();

    bool isDragged();

    void placeTile(int x, int y);

    void getSpace(int x, int y);

    bool verifySpace();

    void setCoordinates();
};

Tile::Tile(int start, char letter)
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
    
    //Set the default sprite
    clip = &clips[CLIP_TILE_A];
}

void Tile::show()
{
    //Show the button
    apply_surface( box.x, box.y, TileSheet, screen, clip );
}

void Tile::handle_events()
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
            placeTile(event.button.x, event.button.y);
        }
    }
    //if the tile is attached
    if(dragged && event.type == SDL_MOUSEMOTION)
    {
        //Get the mouse offsets
        box.x = event.motion.x - TILE_SIZE / 2;
        box.y = event.motion.y - TILE_SIZE / 2;

    } 
}

bool Tile::isDragged()
{
  return dragged;
}

void Tile::getSpace(int x, int y)
{
  boardSpace.first = (x - 0) / TILE_SIZE;
  boardSpace.second = (y - SCREEN_TOP_MARGIN) / TILE_SIZE;
  //Board.attachTile(Tile, i, j, face)
}

bool Tile::verifySpace()
{
  if(Grid[boardSpace.second][boardSpace.first] == 0)
  {
    return true;
  }
  return false;
}

void Tile::placeTile(int x, int y)
{
  getSpace(x, y);
  if(verifySpace())
  {
    Grid[boardSpace.second][boardSpace.first] = face;
    previousSpace = boardSpace;
  }
  else
  {
    boardSpace = previousSpace;
  }
  setCoordinates();
}

void Tile::setCoordinates()
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
#endif