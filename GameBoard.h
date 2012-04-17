#ifndef GAMEBOARD_H_INCLUDED
#define GAMEBOARD_H_INCLUDED

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Setup.h"
#include <set>
#include "GUI.h"

static const string NEW_FILE_NAME = "newboard.txt";
static const string END_OF_FILE_ERROR = "NUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
static const int ALPHABET_SIZE = 26;
static const string CREATOR = "alfred hitchcock";

class GameGUI;
class GUITile;
class GameBoard;

/*class GoButton
{
  SDL_Rect button;

class GameGUI
{
public:
  GameBoard * theGameBoard;
  vector<GUITile> allGUITiles;
  GoButton theButton;
  GameGUI();
  void CreateGUITile(char letter);
  void handle_events();
};

const SDL_Rect GameGUI::goButton = {384, 544, 64, 32};*/

class GameBoard
{   
  friend class GUITile;
  friend class GameGUI;
    class Square
    {
    public:
        //pair<int, int> coord;
        char SquareValue;
        bool active;
        char baseValue;

        public:
        class Square()
        {
            //coord.first = 0;
            //coord.second = 0;
            SquareValue = '-';
            active = false;
            baseValue = '0';
        }
    };
    pair<int, char> squareBag[ALPHABET_SIZE];
    Square theGameBoard[BOARD_LENGTH][BOARD_LENGTH];
    char deck1[DECK_SIZE], deck2[DECK_SIZE];
    set<pair<int, int>> activeSpots;
    string creator; //which player made it?
    string turn; //whose turn is it?
    GameBoard(); // new game

    GameBoard(string boardString);// retrieving existing game

    /*
    baseValue:
    - = Origin
    0  = Blank
    1  = Double Letter
    2  = Triple Letter
    3  = Double Word
    4  = Triple Word
    */

public:
    void initialize();
    void retrieveGame(string boardString);
    bool placeSquare(int x, int y, char givenValue);
    bool placeDeckSquare(int x, char givenValue);
    bool removeSquare(pair<int, int> givenPair);
    bool removeDeckSquare(int x);
    string GameBoard::toString();
    void update();

    //Return integer for multiple failure cases.
    int verifyPlay();
    bool checkSpots(set<pair<int, int>>::iterator it);

    //verifyWord
    //Returns true or false if word is within the dictionary, takes in string.

    //constructStrings

    //calculateWord
    //Identify Square bonuses and erase if utilized. Replace if undone.

};

GameBoard::GameBoard() // new game
{
  initialize();
}

GameBoard::GameBoard(string boardString) // retrieving existing game
{
  retrieveGame(boardString);
}

void GameBoard::initialize()
{
    /*char temp, tempSquare, tempBase;
    ifstream inputFile;
    inputFile.open(fileName.c_str());
        
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
      deck1[i] = 0;
    }*/
  char temp, tempSquare, tempBase;
  ifstream inputFile;
  inputFile.open(NEW_FILE_NAME.c_str());

  for(int i = 0; i < BOARD_LENGTH; i++)
  {
      for(int j = 0; j < BOARD_LENGTH; j++)
      {
          /*if(inputFile.eof())
              throw(END_OF_FILE_ERROR);*/
          inputFile.get(tempSquare);
          inputFile.get(tempBase);
          (theGameBoard[i][j]).SquareValue = tempSquare;
          (theGameBoard[i][j]).baseValue = tempBase;
      }
      inputFile.ignore(1, '\n');
  }
  /*for(int i = 0; i < DECK_SIZE; i++)
      inputFile.get(deck1[i]);
  inputFile.ignore(1, '\n');
  for(int i = 0; i < DECK_SIZE; i++)
      inputFile.get(deck2[i]);*/
  inputFile.ignore(1, '\n');
  for(int i = 0; i < ALPHABET_SIZE; i++)
  {
      inputFile >> squareBag[i].first;
      inputFile.ignore(1, ' ');
      inputFile.get(squareBag[i].second);
      inputFile.ignore(1, ' ');
  }
  creator = CREATOR;
  inputFile.close();
}

bool GameBoard::placeSquare(int x, int y, char givenValue)
{
    if(theGameBoard[x][y].SquareValue == '-')
    {
        this->theGameBoard[x][y].SquareValue = givenValue;
        this->theGameBoard[x][y].active = true;
        activeSpots.insert(*(new pair<int, int>(x, y)));
        return true;
    }
    else
        return false;
}

bool GameBoard::placeDeckSquare(int x, char givenValue)
{
  if(deck1[x] == 0)
  {
    deck1[x] = givenValue;
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
        activeSpots.erase(*(new pair<int, int>(givenPair.first, givenPair.second)));//(new pair<int, int>(givenPair.first, givenPair.second));
        return true;
    }
    else
        return false;
}

bool GameBoard::removeDeckSquare(int x)
{
  this->deck1[x] = 0;
  return true;
}

int GameBoard::verifyPlay()
{
  bool orientation = true; //horizantal = false. vertical = true
  //checking for same row or column
  bool straightLine = true;
  int val;
  set<pair<int, int>>::iterator it = activeSpots.begin();
  if(activeSpots.size() > 0)
  {
    val = (*it).first;
    it++;
    for(; it != activeSpots.end(); it++)
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
      it = activeSpots.begin();
      val = (*it).second;
      it++;
      for(; it != activeSpots.end(); it++)
      {
        if((*it).second != val)
        {
          straightLine = false;
        }
      }
    }
  }
  if(straightLine == false)
  {
    return -1;
  }

  bool connected = true;
  it = activeSpots.begin();
  for(; it != activeSpots.end(); it++)
  {
    if(!checkSpots(it))
    {
      connected = false;
    }
  }

  if(!connected)
  {
    return -2;
  }
  return 1;
}

bool GameBoard::checkSpots(set<pair<int, int>>::iterator it)
{
  bool valid = false;
  if(!theGameBoard[(*it).first + 1][(*it).second].active && theGameBoard[(*it).first + 1][(*it).second].SquareValue != '-')
  {
    valid = true;
  }
  else if(!theGameBoard[(*it).first - 1][(*it).second].active && theGameBoard[(*it).first - 1][(*it).second].SquareValue != '-')
  {
    valid = true;
  }
  else if(!theGameBoard[(*it).first][(*it).second + 1].active && theGameBoard[(*it).first][(*it).second + 1].SquareValue != '-')
  {
    valid = true;
  }
  else if(!theGameBoard[(*it).first][(*it).second - 1].active && theGameBoard[(*it).first][(*it).second - 1].SquareValue != '-')
  {
    valid = true;
  }
  return valid;
}

string GameBoard::toString()//Square** theGameBoard, char deck1[], char deck2[])
{
  stringstream stringOut;
  stringOut << creator << endl;
  for(int i = 0; i < BOARD_LENGTH; i++)
  {
      for(int j = 0; j < BOARD_LENGTH; j++)
      {
          stringOut << theGameBoard[i][j].SquareValue;
          stringOut << theGameBoard[i][j].baseValue;
      }
      //stringOut << '\n';
  }
  for(int i = 0; i < DECK_SIZE; i++)
      stringOut << deck1[i];
 // stringOut << '\n';
  for(int i = 0; i < DECK_SIZE; i++)
      stringOut << deck2[i];
  for(int i = 0; i < ALPHABET_SIZE; i++)
  {
      stringOut << squareBag[i].first << squareBag[i].second << ' ';
  }

  return stringOut.str();
    /*ofstream outputFile;
    outputFile.open(EXISTING_FILE_NAME.c_str());
    outputFile.clear();
    for(int i = 0; i < BOARD_LENGTH; i++)
    {
        for(int j = 0; j < BOARD_LENGTH; j++)
        {
            outputFile << theGameBoard[i][j].SquareValue;
            outputFile << theGameBoard[i][j].baseValue;
        }
        outputFile << '\n';
    }
    for(int i = 0; i < DECK_SIZE; i++)
        outputFile << deck1[i];
    outputFile << '\n';
    for(int i = 0; i < DECK_SIZE; i++)
        outputFile << deck2[i];
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        outputFile << squareBag[i].first << ' ' << squareBag[i].second << ' ';
    }
    */
}

void GameBoard::retrieveGame(string boardString)
{
  char temp, tempSquare, tempBase;
  string tempCreator = 0;
  for(int i = 0; boardString[i] != '\n'; i++)
  {
    tempCreator += boardString[i];
  }
  creator = tempCreator;

  for(int i = 0; i < BOARD_LENGTH; i++)
  {
      for(int j = 0; j < BOARD_LENGTH; j++)
      {
          /*if(inputFile.eof())
              throw(END_OF_FILE_ERROR);*/
          inputFile.get(tempSquare);
          inputFile.get(tempBase);
          (theGameBoard[i][j]).SquareValue = tempSquare;
          (theGameBoard[i][j]).baseValue = tempBase;
      }
      inputFile.ignore(1, '\n');
  }
  /*for(int i = 0; i < DECK_SIZE; i++)
      inputFile.get(deck1[i]);
  inputFile.ignore(1, '\n');
  for(int i = 0; i < DECK_SIZE; i++)
      inputFile.get(deck2[i]);*/
  inputFile.ignore(1, '\n');
  for(int i = 0; i < ALPHABET_SIZE; i++)
  {
      inputFile >> squareBag[i].first;
      inputFile.ignore(1, ' ');
      inputFile.get(squareBag[i].second);
      inputFile.ignore(1, ' ');
  }
  inputFile.close();
    /*ifstream inputFile;

    if(inputFile.open(EXISTING_FILE_NAME))
        initialize(EXISTING_FILE_NAME);
    inputFile.close();*/
}

#endif // GAMEBOARD_H_INCLUDED
