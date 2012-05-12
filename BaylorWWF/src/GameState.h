/*#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Setup.h"
#include "GUI.h"
#include <string>

using namespace std;
/*
//State variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;
*/
//State status manager
/*void set_next_state( int newState );

//State changer
void change_state();

//Game state object

//Game states
enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_GAME,
    STATE_EXIT
};

/*Classes*/
//Game state base class
/*class GameState
{
    public:
    virtual void handle_events() = 0;
    virtual void logic() = 0;
    virtual void render() = 0;
    virtual ~GameState(){};
};

class Game : public GameState
{
    private:
    //Intro background
    SDL_Surface *background;
    
    //Intro message
    SDL_Surface *message;
    
    public:
    //Loads intro resources
    Game();
    //Frees intro resources
    ~Game();
    
    //Main loop functions
    void handle_events();
    void logic();
    void render();
};

Game::Game()
{
    //Load the background
    background = load_image( "background.png" );
    
    //Render the intro message
    message = TTF_RenderText_Solid( font, "Lazy Foo' Productions Presents...", textColor );
}

Game::~Game()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( message );
}

void Game::handle_events()
{
    //While there's events to handle
    while( SDL_PollEvent( &event ) )
    {
        //If the user has Xed out the window
        if( event.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        //If the user pressed enter
        else if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
        {
            //moving tiles around
        }
    }
}

void set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

#endif*/