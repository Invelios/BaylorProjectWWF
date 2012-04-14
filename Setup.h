#ifndef SETUP_H
#define SETUP_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>

using namespace std;

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 576;
const int SCREEN_TOP_MARGIN = 64;
const int SCREEN_BOTTOM_MARGIN = 32;
const int SCREEN_BPP = 32;
const int TILE_SIZE = 32;
const int BOARD_LENGTH = 15;
const int DECK_SIZE = 7;

SDL_Surface * screen = NULL; //the screen, of course
SDL_Surface * background = NULL; //black screen, border lines, and middle line
SDL_Surface * TileSheet = NULL;

SDL_Event event;

TTF_Font *font = NULL;
SDL_Color textColor = { 0, 0, 0 };

Mix_Music *music = NULL;
Mix_Chunk *scratch = NULL;

void set_clips();
bool init();
bool load_files();
SDL_Surface *load_image(string filename);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void clean_up();

SDL_Rect clips[42];

void set_clips()
{
    //Clip the sprite sheet
  for(int i = 0; i < 7; i++)
  {
    for(int j = 0; j < 6; j++)
    {
      clips[6 * i + j].x = 32 * j;
      clips[6 * i + j].y = 32 * i;
      clips[6 * i + j].w = 32;
      clips[6 * i + j].h = 32;
    }
  }
  clips[33].w = 96;
  clips[39].w = 96;
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "PONG clone", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );

    TileSheet = load_image("tiles.png");

	 //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //Open the font
    font = TTF_OpenFont( "arialbd.ttf", 30 );

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //Load the music
    /*music = Mix_LoadMUS( "ziggurat.wav" );

	 if(music == NULL)
	 {
		 return false;
	 }*/

    //If everything loaded fine
    return true;
}

SDL_Surface *load_image(string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 239, 228, 176 ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface(background);

    //Free the music
    Mix_FreeMusic(music);

    //Close the font
    TTF_CloseFont(font);

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

#endif