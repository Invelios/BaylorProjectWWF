#ifndef SETUP_H
#define SETUP_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Globals.h"
#include <string>

using namespace std;

SDL_Event event;

const int SCREEN_BPP = 32;
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 576;

TTF_Font *font = NULL;
SDL_Color textColor = { 0, 0, 0 };

Mix_Music *music = NULL;
Mix_Chunk *scratch = NULL;

SDL_Surface * screen = NULL; //the screen, of course
SDL_Surface * background = NULL; //black screen, border lines, and middle line
SDL_Surface * TileSheet = NULL;
SDL_Surface * menuTiles = NULL;

void set_clips();
bool init();
bool load_files();
SDL_Surface *load_image(string filename);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void clean_up();

SDL_Rect clips[42];
SDL_Rect menuClips[50];

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
  for(int i = 0; i < 9; i++)
  {
    menuClips[i].x = 0;
    menuClips[i].y = 48 * i;
    menuClips[i].w = 224;
    menuClips[i].h = 48;
  }
  menuClips[9].x = 0;
  menuClips[9].y = 448;
  menuClips[9].w = 32;
  menuClips[9].h = 32;
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

    menuTiles = load_image("menuTiles.png");

	 //If there was a problem in loading the background
    if( background == NULL  || TileSheet == NULL || menuTiles == NULL)
    {
        return false;
    }

    //Open the font
    font = TTF_OpenFont( "arialbd.ttf", 16 );

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