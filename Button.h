#ifndef BUTTON_H
#define BUTTON_H

#include "SDL.h"
#include "Setup.h"

using namespace std;

class Button
{
    private:
    //The attributes of the button
    SDL_Rect box;
    
    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;

    int basicClip;

    int triggerVal;
    
    public:
    //Initialize the variables
    Button(int x, int y, int w, int h, int aClip, int trigger);
    
    //Handles events and set the button's sprite region
    int handle_events();
    
    //Shows the button on the screen
    void show();

    int virtual doTheThing(){return 0;}
};



class NewProfileButton : public Button
{
  int doTheThing();
};

int NewProfileButton::doTheThing()
{
  return 0;
}

Button::Button(int x, int y, int w, int h, int aClip, int trigger)
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    triggerVal = trigger;
    
    //Set the default sprite
    basicClip = aClip;
    clip = &menuClips[basicClip];
}

int Button::handle_events()
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
                //Set the button sprite
                clip = &menuClips[basicClip + 2];
            }
        }
    }
    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        { 
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;
        
            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                //Set the button sprite
                clip = &menuClips[basicClip];
                return triggerVal;
                //doTheThing();
            }
        }
    }
    return 0;
}

void Button::show()
{
    //Show the button
    apply_surface( box.x, box.y, menuTiles, screen, clip );
}

#endif