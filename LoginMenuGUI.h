#ifndef LOGINMENUGUI_H
#define LOGINMENUGUI_H
#include <iostream>
#include <string>
#include "Setup.h"
#include "Networking.h"

using namespace std;

const int USER_NAME_MAX_LENGTH = 20;

string loginScreenLoop();

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

#include "LoginMenuGUI.h"

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

string loginScreenLoop()
{
  Networking theNetwork;
  SDL_Surface * requestName = NULL;
  SDL_Surface * loginBackground = NULL;
  SDL_Surface * requestPass = NULL;
  SDL_Surface * incorrectCombo = NULL;

  bool nameEntered = false;
  bool passEntered = false;
  bool quit = false;
  bool state = 0; //0 = username, 1 = password
  bool incorrect = 0; //1 to notify user of incorrect password
  bool goodPass = 1; //1 for no error, 0 for error
  StringInput name;
  StringInput password;
  requestName = TTF_RenderText_Solid( font, "Enter User Name:", textColor );
  requestPass = TTF_RenderText_Solid(font, "Enter Password:", textColor);
  incorrectCombo = TTF_RenderText_Solid(font, "Incorrect combination; please try again:", textColor);

  loginBackground = load_image("loginbackground.png");

  //While the user hasn't quit
    while( quit == false && !(nameEntered == true && passEntered == true))
    {
      if(state == 0)
      {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user hasn't entered their name yet
            if( nameEntered == false )
            {
                //Get user input
                name.handle_input();
                
                //If the enter key was pressed
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    //Change the flag
                    nameEntered = true;
                    state = 1;
                }
            }
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        //Apply the background
        apply_surface( 0, 0, loginBackground, screen );

        //Show the message
        apply_surface( ( SCREEN_WIDTH - requestName->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - requestName->h ) / 2, requestName, screen );
        
        //Show the name on the screen
        name.show_centered();
      }
      else
      {
        while( SDL_PollEvent( &event ) )
        {
            //If the user hasn't entered their name yet
            if( passEntered == false )
            {
                //Get user input
                password.handle_input();
                
                //If the enter key was pressed
                if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
                {
                    //Change the flag
                    passEntered = true;
                    goodPass = theNetwork.login(name.getStr(), password.getStr());
                    if(goodPass == false)
                    {
                      passEntered = false;
                      nameEntered = false;
                      state = 0;
                      name.reset();
                      password.reset();
                    }
                }
            }
            
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        //Apply the background
        apply_surface( 0, 0, loginBackground, screen );

        //Show the message
        apply_surface( ( SCREEN_WIDTH - requestPass->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - requestPass->h ) / 2, requestPass, screen );
        
        //Show the name on the screen
        password.show_centered();
      }

      if(goodPass == false)
      {
        apply_surface((SCREEN_WIDTH - incorrectCombo->w) / 2, ((SCREEN_HEIGHT / 2) - incorrectCombo->h) / 2 - incorrectCombo->h, incorrectCombo, screen);
      }

      //Update the screen
      if( SDL_Flip( screen ) == -1 )
      {
          throw "screen flip fail";
      }
    }


    SDL_FreeSurface(requestName);
    SDL_FreeSurface(requestPass);
    SDL_FreeSurface(incorrectCombo);
    return name.getStr();
}

#endif