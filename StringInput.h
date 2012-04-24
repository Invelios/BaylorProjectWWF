#ifndef STRINGINPUT_H
#define STRINGINPUT_H

#include <string>
#include "Setup.h"

using namespace std;

class StringInput
{
    private:
    //The storage string
    string str;
    
    //The text surface
    SDL_Surface *text;
    
    public:
    //Initializes variables
    StringInput();
    
    //Does clean up
    ~StringInput();

    string getStr();
    
    //Handles input
    void handle_input();
    
    //Shows the message on screen
    void show_centered();    

    void reset();
};

StringInput::StringInput()
{
    //Initialize the string
    str = "";
    
    //Initialize the surface
    text = NULL;
    
    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );    
}

StringInput::~StringInput()
{
    //Free text surface
    SDL_FreeSurface( text );
    
    //Disable Unicode
    SDL_EnableUNICODE( SDL_DISABLE );  
}

void StringInput::handle_input()
{
  //If a key was pressed
  if( event.type == SDL_KEYDOWN )
  {
    //Keep a copy of the current version of the string
    string temp = str;
        
    //If the string less than maximum size
    if( str.length() <= USER_NAME_MAX_LENGTH )
    {
          //If the key is a number
      if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
      {
        //Append the character
        str += (char)event.key.keysym.unicode;
      }
      //If the key is a uppercase letter
      else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
      {
        //Append the character
        str += (char)event.key.keysym.unicode;
      }
      //If the key is a lowercase letter
      else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
      {
        //Append the character
        str += (char)event.key.keysym.unicode;
      }
      //If backspace was pressed and the string isn't blank
      if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
      {
        //Remove a character from the end
        str.erase( str.length() - 1 );
      }
      //If the string was changed
      if( str != temp )
      {
        //Free the old surface
        SDL_FreeSurface( text );
        
        //Render a new text surface
        text = TTF_RenderText_Solid( font, str.c_str(), textColor );
      }
    }
  }
}

void StringInput::show_centered()  
{
    //If the surface isn't blank
    if( text != NULL )
    {
        //Show the name
        apply_surface( ( SCREEN_WIDTH - text->w ) / 2, ( SCREEN_HEIGHT - text->h ) / 2, text, screen );
    }
}

string StringInput::getStr()
{
  return str;
}

void StringInput::reset()
{
  text = NULL;
  str = "";
}

#endif