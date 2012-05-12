#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Networking.h"
#include <string>
#include <vector>
//#include "GameState.h"
#include "GUI.h"
#include "Setup.h"
#include "FirstMenuGUI.h"
#include "Timer.h"
#include "MenuGUI.h"
#include "MenuLogic.h"

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

  LoginState theLoginState;
  NewProfileState theNewProfileState;
  NewGameState * theNewGameState = NULL;
  MenuGUI * theMenuGUI = NULL;
  string userName;
  GameGUI * theGame = NULL;

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
    userName = "BOB";
  //game loop
  while(!quit/*stateID != STATE_EXIT*/)
  {
    //Start the frame timer
        fpsReg.start();
    switch (state)
    {
    case 0: state = mainMenuState(); break;
    case 1: state = theLoginState.run(); break;
    case 2: state = theNewProfileState.run(); break;
    case 3: if(theMenuGUI == NULL)
            {
              userName = theLoginState.name.getStr();
              theMenuGUI = new MenuGUI(userName);
            }
            state = theMenuGUI->run();
            break;
    case 4: if(theNewGameState == NULL) //new game
            {
              theNewGameState = new NewGameState();
              theNewGameState->theGameGUI->CreateGUITile('f');
              theNewGameState->theGameGUI->CreateGUITile('r');
              theNewGameState->theGameGUI->CreateGUITile('i');
              theNewGameState->theGameGUI->CreateGUITile('e');
              theNewGameState->theGameGUI->CreateGUITile('n');
              theNewGameState->theGameGUI->CreateGUITile('d');
              theNewGameState->theGameGUI->CreateGUITile('s');
            }
            state = theNewGameState->run(); break;
    case 5: theGame = new GameGUI(theMenuGUI->mainGameId); //load existing game
            theGame->run(); break;
    case 6: state = theNewGameState->run(); //actually playing the game
    }

    //theGame.theGameBoard->cheat(true);

    while(SDL_PollEvent(&event)) 
    { 

      if( event.type == SDL_QUIT )
      {
        quit = true;
      } 
    }
        
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
