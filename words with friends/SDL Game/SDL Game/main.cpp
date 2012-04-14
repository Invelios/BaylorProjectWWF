#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <vector>
#include "Setup.h"
//#include "GameState.h"
#include "GUI.h"
#include "GameBoard.h"

using namespace std;

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

   set_clips();

   GameGUI theGame;
   theGame.CreateGUITile('F');
   theGame.CreateGUITile('R');
   theGame.CreateGUITile('I');
   theGame.CreateGUITile('E');
   theGame.CreateGUITile('N');
   theGame.CreateGUITile('D');
   theGame.CreateGUITile('S');

   //game loop
	 while(!quit/*stateID != STATE_EXIT*/)
	 {
     
     //Start the frame timer
        //fps.start();
        
        //Do state event handling
        //currentState->handle_events();
        
        /*Sprite* mySprites = getMySpriteArray(); 
        int numSprites = getNumSprites(); 

        Sprite* dragSprite = NULL; */

        while(SDL_PollEvent(&event)) 
        { 
          theGame.handle_events();
          if( event.type == SDL_QUIT )
          {
            quit = true;
          } 
        } 
        //Do state logic
        /*currentState->logic();
        
        //Change state if needed
        change_state();
        
        //Do state rendering*/
        apply_surface(0, 0, background, screen);
        theGame.show();
        //currentState->render();
        
        //Update the screen*/
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }
        
        //Cap the frame rate
        /*if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }*/
     //EVENTS
     //LOGIC
		 /*RENDERING
      clear_screen();
      show_background();
      show_objects();
      update_screen();
      cap_frame_rate();
      */
	 }

	 clean_up();
    
    return 0;    
}
