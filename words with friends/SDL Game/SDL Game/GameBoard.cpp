#ifndef GAMEBOARD_CPP
#define GAMEBOARD_CPP
/*
#include "GameBoard.h"

using namespace std;

void GameBoard::initialize()
{
    char temp, tempSquare, tempBase;
    ifstream inputFile;
    inputFile.open(FILE_NAME.c_str());
        
    this->theGameBoard = new Square*[BOARD_LENGTH];
    for(int i = 0; i < BOARD_LENGTH; i++)
    {
      theGameBoard[i] = new Square[BOARD_LENGTH];
    }
    for(int i = 0; i < BOARD_LENGTH; i++)
    {
        for(int j = 0; j < BOARD_LENGTH; j++)
        {
            if(inputFile.eof())
                throw(END_OF_FILE_ERROR);
            inputFile.get(tempSquare);
            inputFile.get(tempBase);
            (theGameBoard[i][j]).SquareValue = tempSquare;
            (theGameBoard[i][j]).baseValue = tempBase;
        }
        inputFile.ignore(1, '\n');
    }
    for(int i = 0; i < DECK_SIZE; i++)
    {
      deck[i] = 0;
    }
}

bool GameBoard::placeSquare(int x, int y, char givenValue)
{
    if(theGameBoard[x][y].SquareValue == '-')
    {
        this->theGameBoard[x][y].SquareValue = givenValue;
        this->theGameBoard[x][y].active = true;
        theGUI->activeSpots.insert(*(new pair<int, int>(x, y)));
        return true;
    }
    else
        return false;
}

bool GameBoard::placeDeckSquare(int x, char givenValue)
{
  if(deck[x] == 0)
  {
    deck[x] = givenValue;
    return true;
  }
  return false;
}

bool GameBoard::removeSquare(pair<int, int> givenPair)
{
    if(this->theGameBoard[givenPair.first][givenPair.second].active == true)
    {
        this->theGameBoard[givenPair.first][givenPair.second].SquareValue = '-';
        this->theGameBoard[givenPair.first][givenPair.second].active = false;
        theGUI->activeSpots.erase(*(new pair<int, int>(givenPair.first, givenPair.second)));//(new pair<int, int>(givenPair.first, givenPair.second));
        return true;
    }
    else
        return false;
}

bool GameBoard::removeDeckSquare(int x)
{
  this->deck[x] = 0;
  return true;
}

int GameBoard::verifyPlay()
{
  bool orientation = true; //horizantal = false. vertical = true
  //checking for same row or column
  bool straightLine = true;
  int val;
  set<pair<int, int>>::iterator it = theGUI->activeSpots.begin();
  if(theGUI->activeSpots.size() > 0)
  {
    val = (*it).first;
    it++;
    for(; it != theGUI->activeSpots.end(); it++)
    {
      if((*it).first != val)
      {
        straightLine = false;
      }
    }
    if(straightLine == false)
    {
      orientation = false;
      straightLine = true;
      it = theGUI->activeSpots.begin();
      val = (*it).second;
      it++;
      for(; it != theGUI->activeSpots.end(); it++)
      {
        if((*it).second != val)
        {
          straightLine = false;
        }
      }
    }
  }
  if(straightLine = false)
  {
    return -1;
  }

  it = theGUI->activeSpots.begin();
  ////Must be adjacent to an already-existing Square, or the Origin Spot.
  if(orientation)//vertical
  {

  }
  else //horizontal
  {//first check around the first dude
    //if(theGameBoard[
  }
}
*/
#endif