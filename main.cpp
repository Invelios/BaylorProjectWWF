#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <vector>
#include "Setup.h"
//#include "GameState.h"
#include "GUI.h"

using namespace std;

int main( int argc, char* args[] )
{
    bool quit = false;
    for(int i = 0; i < 15; i++)
    {
      for(int j = 0; j < 15; j++)
      {
        Grid[i][j] = 0;
      }
    }
    for(int i = 0; i < 7; i++)
    {
      Deck[i] = 0;
    }

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

   vector<Tile> allTiles;
   Tile myTile0(0, 'a');
   Tile myTile1(1, 'b');
   Tile myTile2(2, 'c');
   Tile myTile3(3, 'd');
   Tile myTile4(4, 'e');

   allTiles.push_back(myTile0);
   allTiles.push_back(myTile1);
   allTiles.push_back(myTile2);
   allTiles.push_back(myTile3);
   allTiles.push_back(myTile4);
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
          /*if(event.type == SDL_MOUSEBUTTONDOWN) 
          { 
          // This should loop over all the sprites available for grabbing 
            /*for(int i = 0; i < numSprites; i++) 
            { 
              if(isInBoundingRegion(event.button.x, event.button.y, mySprites[i])) 
              dragSprite = mySprites[i]; 
              else 
              dragSprite = NULL; 
            }
            if(
          } */
         /* if(event.type == SDL_MOUSEBUTTONUP) 
          { 
            dragSprite = NULL; 
          } */
          for(int i = 0; i < allTiles.size(); i++)
          {
            allTiles[i].handle_events();
          }
          if( event.type == SDL_QUIT )
          {
              //Quit the program
            quit = true;
          } 
          /*if(event.type == SDL_MOUSEMOTION) 
          { 
            if(myTile.isDragged())
            { /*
            dragSprite->x += event.motion.xrel; 
            dragSprite->y += event.motion.yrel;
            } 
          } */
        } 
        //Do state logic
        /*currentState->logic();
        
        //Change state if needed
        change_state();
        
        //Do state rendering*/
        apply_surface(0, 0, background, screen);
        for(int i = 0; i < allTiles.size(); i++)
        {
          allTiles[i].show();
        }
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
