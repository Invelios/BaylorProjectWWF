/*#include "LoginMenuGUI.h"

const int USER_NAME_MAX_LENGTH = 20;
SDL_Surface * requestName = NULL;
SDL_Surface * loginBackground = NULL;

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

int loginScreenLoop()
{
  bool nameEntered = false;
  bool quit = false;
  StringInput name;
  requestName = TTF_RenderText_Solid( font, "Enter User Name:", textColor );

  loginBackground = load_image("titleBackground.png");

  //While the user hasn't quit
    while( quit == false )
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
                        
                    //Free the old message surface
                    SDL_FreeSurface(requestName);
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
        apply_surface( 0, 0, background, screen );

        //Show the message
        apply_surface( ( SCREEN_WIDTH - requestName->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - requestName->h ) / 2, requestName, screen );
        
        //Show the name on the screen
        name.show_centered();
        
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }
    }
}*/