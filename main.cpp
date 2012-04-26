#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <vector>
//#include "GameState.h"
#include "GUI.h"
#include "Setup.h"
#include "FirstMenuGUI.h"
#include "Timer.h"

using namespace std;

const int FRAMES_PER_SECOND = 30;

int main( int argc, char* args[] )
{
  bool quit = false;

  // GameState *currentState = NULL;

  if(init() == false)
  {
    return 1;
  }
    
  if(load_files() == false)
  {
    return 1;
  }

  int state = 0;
  set_clips();

  GameGUI theGame;
  //MenuGUI theMenuGUI;
  theGame.CreateGUITile('f');
  theGame.CreateGUITile('r');
  theGame.CreateGUITile('i');
  theGame.CreateGUITile('e');
  theGame.CreateGUITile('n');
  theGame.CreateGUITile('d');
  theGame.CreateGUITile('s');
  LoginState theLoginState;
  NewProfileState theNewProfileState;
  DisplayGamesState theDisplayGamesState;
  MenuGUI * theMenuGUI = NULL;
  string userName;

  //Keep track of the frame count

  //Keep track of the current frame
    int frame = 0;
    
    //Whether or not to cap the frame rate
    bool cap = true;

    //The frame rate regulator
    Timer fpsReg;
    
    //Timer used to calculate the frames per second
    Timer fpsCalc;
    
    //Timer used to update the caption
    Timer update;

    //Start the update timer
    update.start();
    
    //Start the frame timer
    fpsCalc.start();

  //game loop
  while(!quit/*stateID != STATE_EXIT*/)
  {
    //Start the frame timer
        fpsReg.start();
    /*switch (state)
    {
    case 0: state = mainMenuState(); break;
    case 1: state = theLoginState.run(); break;
    case 2: state = theNewProfileState.run(); break;
    case 3: state = theDisplayGamesState.run(); break;
    case 4: if(theMenuGUI == NULL)
            {
              theMenuGUI = new MenuGUI(userName);
            }
            theMenuGUI->run();
            break;
    }*/

    theGame.theGameBoard->cheat(true);

    while(SDL_PollEvent(&event)) 
    { 
      theGame.handle_events();
      if( event.type == SDL_QUIT )
      {
        quit = true;
      } 
    }

    apply_surface(0, 0, background, screen);
    theGame.show();
        
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
      return 1;    
    }
    //Increment the frame counter
        frame++;
        //If a second has passed since the caption was last updated

        //If we want to cap the frame rate
        if( ( cap == true ) && ( fpsReg.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fpsReg.get_ticks() );
        }
        if( update.get_ticks() > 1000 )
        {
            //The frame rate as a string
            std::stringstream caption;
            
            //Calculate the frames per second and create the string
            caption << "Average Frames Per Second: " << frame / ( fpsCalc.get_ticks() / 1000.f );
            
            //Reset the caption
            SDL_WM_SetCaption( caption.str().c_str(), NULL );
            
            //Restart the update timer
            update.start();    
        }
  }

  clean_up();
    
  return 0;    
}
