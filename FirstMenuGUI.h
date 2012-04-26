#ifndef FIRSTMENUGUI_H
#define FIRSTMENUGUI_H
#include <iostream>
#include <string>
#include "Setup.h"
#include "Networking.h"
#include "StringInput.h"
#include "Button.h"
#include "Globals.h"
#include "MenuGUI.h"

using namespace std;

int mainMenuState()
{
  SDL_Surface * loginBackground = load_image("loginbackground.png");
  bool quit = false;
  Button newProfileButton(96, 128, 224, 48, 5, 2);
  Button loginButton(96, 176, 224, 48, 6, 1);
  while(SDL_PollEvent( &event ) && !quit)
  {

    if(newProfileButton.handle_events() == 2)
    {
      return 2;
    }
    if(loginButton.handle_events() == 1)
    {
      return 1;
    }
  }
  //Apply the background
  apply_surface( 0, 0, loginBackground, screen );
  newProfileButton.show();
  loginButton.show();
  return 0;
}

class NewProfileState
{
  bool nameEntered;
  bool passEntered;
  int state; //0 = username, 1 = password, 2 = email
  bool incorrect; //1 to notify user of incorrect password
  bool goodAccount; //1 for no error, 0 for error
  bool emailEntered;
  StringInput name;
  StringInput password;
  StringInput email;

  SDL_Surface * requestName;
  SDL_Surface * loginBackground;
  SDL_Surface * requestPass;
  SDL_Surface * requestEmail;
  SDL_Surface * incorrectCombo;

public:
  string getPass()
  {
    return password.getStr();
  }
  string getName()
  {
    return name.getStr();
  }
  string getEmail()
  {
    return email.getStr();
  }
  NewProfileState()
  {
    nameEntered = false;
    passEntered = false;
    emailEntered = false;
    state = 0; //0 = username, 1 = password
    //incorrect = 0; //1 to notify user of incorrect password
    //goodAccount = 1; //1 for no error, 0 for error
    requestName = TTF_RenderText_Solid( font, "Enter User Name:", textColor );
    requestPass = TTF_RenderText_Solid(font, "Enter Password:", textColor);
    requestEmail = TTF_RenderText_Solid(font, "Enter Email Address:", textColor);
    incorrectCombo = TTF_RenderText_Solid(font, "Incorrect combination; please try again:", textColor);

    loginBackground = load_image("loginbackground.png");
  }

  int run()
  {
    Networking * theNetwork = Networking::getInstance();
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
      }
      //Apply the background
      apply_surface( 0, 0, loginBackground, screen );

      //Show the message
      apply_surface( ( SCREEN_WIDTH - requestName->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - requestName->h ) / 2, requestName, screen );
        
      //Show the name on the screen
      name.show_centered();
    }
    else if (state == 1)
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
                  state = 2;
              }
          }
      }
      //Apply the background
      apply_surface( 0, 0, loginBackground, screen );

      //Show the message
      apply_surface( ( SCREEN_WIDTH - requestPass->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - requestPass->h ) / 2, requestPass, screen );
        
      //Show the name on the screen
      
      password.show_centered();
    }
    else
    {
      while( SDL_PollEvent( &event ) )
      {
          //If the user hasn't entered their name yet
          if( emailEntered == false )
          {
              //Get user input
              email.handle_input();
                
              //If the enter key was pressed
              if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
              {
                  //Change the flag
                  emailEntered = true;
                  goodAccount = theNetwork->createAccount(name.getStr(), password.getStr(), email.getStr());
                  if(goodAccount == false)
                  {
                    passEntered = false;
                    nameEntered = false;
                    emailEntered = false;
                    state = 0;
                    name.reset();
                    password.reset();
                    email.reset();
                    return 2;
                  }
                  else
                  {
                    return 0;
                  }
              }
          }
      }
      //Apply the background
      apply_surface( 0, 0, loginBackground, screen );

      //Show the message
      apply_surface( ( SCREEN_WIDTH - requestEmail->w ) / 2, ( ( SCREEN_HEIGHT / 2 ) - requestEmail->h ) / 2, requestEmail, screen );
        
      //Show the name on the screen
      email.show_centered();
    }
    if(goodAccount == false)
    {
      apply_surface((SCREEN_WIDTH - incorrectCombo->w) / 2, ((SCREEN_HEIGHT / 2) - incorrectCombo->h) / 2 - incorrectCombo->h, incorrectCombo, screen);
    }
    return 2;
  }
};

class LoginState
{
  bool nameEntered;
  bool passEntered;
  bool state; //0 = username, 1 = password
  bool incorrect; //1 to notify user of incorrect password
  bool goodPass; //1 for no error, 0 for error

  SDL_Surface * requestName;
  SDL_Surface * loginBackground;
  SDL_Surface * requestPass;
  SDL_Surface * incorrectCombo;

public:

  StringInput name;
  StringInput password;
  string getPass()
  {
    return password.getStr();
  }
  string getName()
  {
    return name.getStr();
  }

  LoginState()
  {
    nameEntered = false;
    passEntered = false;
    state = 0; //0 = username, 1 = password
    incorrect = 0; //1 to notify user of incorrect password
    goodPass = 1; //1 for no error, 0 for error
    requestName = TTF_RenderText_Solid( font, "Enter User Name:", textColor );
    requestPass = TTF_RenderText_Solid(font, "Enter Password:", textColor);
    incorrectCombo = TTF_RenderText_Solid(font, "Incorrect combination; please try again:", textColor);

    loginBackground = load_image("loginbackground.png");
  }

  int run()
  {
    Networking * theNetwork = Networking::getInstance();
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
                  goodPass = theNetwork->login(name.getStr(), password.getStr());
                  if(goodPass == false)
                  {
                    passEntered = false;
                    nameEntered = false;
                    state = 0;
                    name.reset();
                    password.reset();
                    return 1;
                  }
                  else
                  {
                    return 3;
                  }
              }
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
    return 1;
  }
};

string mainScreenLoop()
{
  /*Networking theNetwork;

  bool quit = false;
  int state = 0; //0 = username, 1 = password
  StringInput name;
  StringInput password;
  requestName = TTF_RenderText_Solid( font, "Enter User Name:", textColor );
  requestPass = TTF_RenderText_Solid(font, "Enter Password:", textColor);
  requestEmail = TTF_RenderText_Solid(font, "Enter email address:", textColor);

  loginBackground = load_image("loginbackground.png");

  int blah = 96;


  //While the user hasn't quit
    while(quit == false)
    {
      if(state == 0)
      {
        //While there's events to handle
        while( SDL_PollEvent( &event ) && state == 0)
        {
          state = newProfileButton.handle_events();
          if(state == 0)
          {
            state = loginButton.handle_events();
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
        newProfileButton.show();
        loginButton.show();
      }
      else if(state == 1) //new profile
      {
        while( SDL_PollEvent( &event ) )
        {
          //Get user input
          password.handle_input();
                
          //If the enter key was pressed
          if( ( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_RETURN ) )
          {
                    
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
      else if(state == 2) //login
      {

      }

      //Update the screen
      if( SDL_Flip( screen ) == -1 )
      {
          throw "screen flip fail";
      }
    }


    SDL_FreeSurface(requestName);
    SDL_FreeSurface(requestPass);
    return name.getStr();*/ return "poopoo";
}

#endif