#ifndef LOGINMENUGUI_H
#define LOGINMENUGUI_H
#include <iostream>
#include <string>
#include "Setup.h"
#include "Networking.h"
#include "StringInput.h"

using namespace std;

string loginScreenLoop()
{
  /*//While the user hasn't quit
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
    return name.getStr();*/
    return "lol";
}

#endif