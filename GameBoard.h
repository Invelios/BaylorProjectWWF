// Title  : GameBoard.h
// Author :
// Date Created :
// Modified On:         By:                         Reason:
//      4/23/12             Christopher Scoggins        Outlined Cheat function and created structs it needs
//      4/24/12             Christopher Scoggins        Possibly Finished up cheat funtion.

#ifndef GAMEBOARD_H_INCLUDED
#define GAMEBOARD_H_INCLUDED

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include "Setup.h"
#include <set>
#include "Permutations.h"

using namespace std;

static const string NEW_FILE_NAME = "newboard.txt";
static const string END_OF_FILE_ERROR = "NUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
static const int ALPHABET_SIZE = 26;
static const string USER_NAME = "alfred hitchcock";
const int TILE_SIZE = 32;
const int BOARD_LENGTH = 15;
const int DECK_SIZE = 7;
const int USER_NAME_MAX_LENGTH = 20;
const int SCREEN_TOP_MARGIN = 64;
const int SCREEN_BOTTOM_MARGIN = 32;
const int letterScores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

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

// Move struct used to represent a Move in a whole MoveMapping

struct Move
{
    int thePositionInDeck;
    int theXCoordinate;
    int theYCoordinate;

    Move()
    {
        thePositionInDeck = 0;
        theXCoordinate = -1;
        theYCoordinate = -1;
    }

    Move(int aPostionInDeck, int aXCoordinate, int aYCoordinate)
    {
        thePositionInDeck = aPostionInDeck;
        theXCoordinate = aXCoordinate;
        theYCoordinate = aYCoordinate;
    }

    bool operator<(Move anotherMove)
    {
        return thePositionInDeck < anotherMove.thePositionInDeck;
    }
};


// MoveMapping struct used by cheat function to show a possible move

struct MoveMapping
{
    vector< Move > theMoves;
    int theScore;

    bool operator<(MoveMapping anotherMoveMapping)
    {
        return theScore < anotherMoveMapping.theScore;
    }

};

// Comparison Function Object to get desired vector ordering in cheat function

struct maxScoreFirst
{
    bool operator()(MoveMapping firstMoveMapping, MoveMapping secondMoveMapping)
    {
        return firstMoveMapping.theScore > secondMoveMapping.theScore;
    }
};


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
    multiset<char> squareBag;
    Square theGameBoard[BOARD_LENGTH][BOARD_LENGTH];
    char deck1[DECK_SIZE], deck2[DECK_SIZE];
    set<pair<int, int>> activeSpots;
    string creator; //which player made it?
    string turn; //whose turn is it?

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
    GameBoard(); // new game
    GameBoard(string boardString);// retrieving existing game
    void initialize();
    void retrieveGame(string boardString);
    bool placeSquare(int x, int y, char givenValue);
    bool placeDeckSquare(int x, char givenValue);
    bool removeSquare(pair<int, int> givenPair);
    bool removeDeckSquare(int x);
    string GameBoard::toString();
    vector<string> GameBoard::constructStrings(bool orientation, int &points);
    void update();
    vector<int> emptyTilesInRow(int theRow);
    vector<int> emptyTilesInColumn(int theColumn);
    void updateDeck();
    char draw();

    vector<pair<int,int> > cheat();

    //Return integer for multiple failure cases.
    int verifyPlay();
    bool checkSpots(set<pair<int, int>>::iterator it);

    //verifyWord
    //Returns true or false if word is within the dictionary, takes in string.

    //constructStrings

    //calculateWord
    //Identify Square bonuses and erase if utilized. Replace if undone.

    //Cheat Function
    // Returns a sorted vector of MoveMappings, with the highest scoring moves at the front

    vector< MoveMapping > cheat(bool thePlayerIsFirst);


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
  while(!inputFile.eof())
  {
      squareBag.insert(inputFile.get());
  }
  creator = USER_NAME;
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

//************************************************************
// Desription: Draws a tile from the bag
// Return: char
// Pre: there are elements in the bag
// Post: the drawn element is removed from the bag
//************************************************************

char GameBoard::draw()
{
    srand( time(NULL));

    int tileToDraw = rand() % squareBag.size();

    multiset<char>::iterator theIterator = squareBag.begin() + tileToDraw;

    char theCharacter = *theIterator;

    squareBag.erase(theIterator);

    return theCharacter;
}

//************************************************************
// Desription: Draws Tiles for each blank spot in the given deck
// Return: void
// Pre: there are blank spots in the deck
// Post: the blank spots have tiles
//************************************************************

void GameBoard::updateDeck(int theDeckNumber)
{
    char * theDeck;

    if(theDeckNumber == 1)
    {
        theDeck = deck1;
    }
    else
    {
        theDeck = deck2;
    }

    for(int i = 0; i < DECK_SIZE; i++)
    {
        if(theDeck[i] == 0)
            theDeck[i] = draw();
    }

    return;
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
  multiset<char>::iterator it;
  for(it = squareBag.begin(); it != squareBag.end(); it++)
  {
      stringOut << (*it);
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
  int s = 0;
  for(; boardString[s] != '\n'; s++)
  {
    tempCreator += boardString[s];
  }
  creator = tempCreator;

  for(int i = 0; i < BOARD_LENGTH; i++)
  {
      for(int j = 0; j < BOARD_LENGTH; j++)
      {
          (theGameBoard[i][j]).SquareValue = boardString[s];
          s++;
          (theGameBoard[i][j]).baseValue = boardString[s];
          s++;
      }
  }
  for(int i = 0; i < DECK_SIZE; i++)
  {
    deck1[i] = boardString[s];
    s++;
  }
  for(int i = 0; i < DECK_SIZE; i++)
  {
      deck2[i] = boardString[s];
      s++;
  }
  while(s < boardString.size())
  {
      squareBag.insert(boardString[s]);
      s++;
  }

    /*ifstream inputFile;

    if(inputFile.open(EXISTING_FILE_NAME))
        initialize(EXISTING_FILE_NAME);
    inputFile.close();*/
}

// Needed for Cheat Function
// Adapted from bruteForce powerSet Assignment

vector< vector<int> > powerSet(vector <int> inS)
{
    vector< vector<int> > answer;

    int bytes = 1;

    for(int i = 0; i < inS.size(); i++)
        bytes *= 2;

    for(int i = 0; i < bytes; i++)
    {
        vector<int> curS;

        for(int j = 0; j < inS.size(); j++)
        {

            if((i >> j) % 2 == 1)
            {
                curS.push_back(inS[j]);
            }
        }

        answer.push_back(curS);
    }

    return answer;
}

//************************************************************
// Desription: Gives a vector of the indicies in the row that are blank
// Return: vector<int>
// Pre: The row exists
// Post:
//************************************************************

vector<int> GameBoard::emptyTilesInRow(int theRow)
{
    vector<int> theEmptyTilesInRow;
    for(int i = 0; i < BOARD_LENGTH; i++ )
    {
        if(theGameBoard[i][theRow].SquareValue == '-')
        {
            theEmptyTilesInRow.push_back(i);
        }
    }

    return theEmptyTilesInRow;
}

//************************************************************
// Desription: Gives a vector of the indicies in the column that are blank
// Return: vector<int>
// Pre: The Column exists
// Post:
//************************************************************

vector<int> GameBoard::emptyTilesInColumn(int theColumn)
{
    vector<int> theEmptyTilesInColumn;
    for(int i = 0; i < BOARD_LENGTH; i++ )
    {
        if(theGameBoard[theColumn][i].SquareValue == '-')
        {
            theEmptyTilesInRow.push_back(i);
        }
    }

    return theEmptyTilesInColumn;
}

vector< MoveMapping > GameBoard::cheat(bool thePlayerIsFirst)
{
    vector< MoveMapping > allPossibleMoves;

    char *thisPlayersDeck;                      // Assign the correct deck

    // All Combinations of tiles in Decks

    vector<int> setOfDeckTiles;

    for(int i = 0; i < DECK_SIZE; i++)
    {
        setOfDeckTiles.push_back(i);
    }

    vector< vector<int> > powerSetOfDeckTiles = powerSet(setOfDeckTiles);

    // Try every combination of tiles

    for(int numOfSetOfTiles = 0; numOfSetOfTiles < powerSetOfDeckTiles.size(); numOfSetOfTiles++)
    {
        vector<int> aSetOfTiles = powerSetOfDeckTiles[numOfSetOfTiles];

        vector< vector<int> > thePermutationsOfTiles = Johnson_Trotter(aSetOfTiles);

        // Try every way this combo can fit in each row

        for(int i = 0; i < BOARD_LENGTH; i++)
        {
            vector<int> theEmptyTilesInThisRow = emptyTilesInRow(i);

            if(aSetOfTiles.size() <= theEmptyTilesInThisRow.size())
            {

                for(int k = 0; k < thePermutationsOfTiles.size(); k++)
                {
                    vector<int> theCurrentPermutation = thePermutationsOfTiles[k];

                    vector< Move > theMoves;

                    GameBoard testingGameBoard(toString()); // Copy the current board

                    for(int l = 0; l <= theEmptyTilesInThisRow.size() - theCurrentPermutation.size(); l++)
                    {

                        for(int m = 0; m < theCurrentPermutation.size(); m++)
                        {
                                testingGameBoard.placeSquare( theEmptyTilesInThisRow[m + l], i, thisPlayersDeck[theCurrentPermutation[m]]);
                                Move aMove(theCurrentPermutation[m], theEmptyTilesInThisRow[m + 1], i);
                                theMoves.push_back(aMove);
                        }

                        int thisMovesScore = testingGameBoard.getMoveScore();           // FNIY needs to be the functions that returns the score of the move

                        if(thisMovesScore > 0)
                        {
                            MoveMapping aMoveMapping;
                            aMoveMapping.theScore = thisMovesScore;
                            aMoveMapping.theMoves = theMoves;

                            allPossibleMoves.push_back(aMoveMapping);
                        }

                    }
                }
            }
        }

        // Try every way this combo can fit in each column

        for(int i = 0; i < BOARD_LENGTH; i++)
        {
            vector<int> theEmptyTilesInThisColumn = emptyTilesInColumn(i);

            if(aSetOfTiles.size() <= theEmptyTilesInThisRow.size())
            {

                for(int k = 0; k < thePermutationsOfTiles.size(); k++)
                {
                    vector<int> theCurrentPermutation = thePermutationsOfTiles[k];

                    vector< Move > theMoves;

                    GameBoard testingGameBoard(toString()); // Copy the current board

                    for(int l = 0; l <= theEmptyTilesInThisRow.size() - theCurrentPermutation.size(); l++)
                    {

                        for(int m = 0; m < theCurrentPermutation.size(); m++)
                        {
                            if(theCurrentPermutation[m] != -1)
                            {
                                testingGameBoard.placeSquare( i, theEmptyTilesInThisColumn[m + l], thisPlayersDeck[theCurrentPermutation[m]]);
                                Move aMove(theCurrentPermutation, i, theEmptyTilesInThisColumn[m + 1]);
                                theMoves.push_back(aMove);
                            }

                        }

                        int thisMovesScore = testingGameBoard.getMoveScore();           // FNIY needs to be the functions that returns the score of the move

                        if(thisMovesScore > 0)
                        {
                            MoveMapping aMoveMapping;
                            aMoveMapping.theScore = thisMovesScore;
                            aMoveMapping.theMoves = theMoves;

                            allPossibleMoves.push_back(aMoveMapping);
                        }

                    }
                }
            }
        }
    }


    // Sort the Vector using my MaxScoreFirst as the comparison object

    sort(allPossibleMoves.front(), allPossibleMoves.back(), maxScoreFirst);

    return allPossibleMoves;
}

vector<string> GameBoard::constructStrings(bool orientation, int &points)//horizantal = false. vertical = true
{
  points = 0;
  int wordPoints = 0;
  int modifier = 0;
  int letterMulti = 1;
  int wordMulti = 1;
  int x, y, originalX, originalY;
  vector<deque<char> > strings;
  set<pair<int, int> >::iterator it = activeSpots.begin();
  deque<char> primaryString;
  if(orientation == false)
  {
    //set<pair<int, int>> activeSpots;
    /*
    baseValue:
    - = Origin
    0  = Blank
    1  = Double Letter
    2  = Triple Letter
    3  = Double Word
    4  = Triple Word
    */
    x = originalX = (*it).first;
    y = originalY = (*it).second;
    primaryString.push_back(theGameBoard[x][y].SquareValue);
    modifier = theGameBoard[x][y].baseValue;
    if(modifier == 1)
    {
      letterMulti *= 2;
    }
    else if(modifier == 2)
    {
      letterMulti *= 3;
    }
    else if(modifier == 3)
    {
      wordMulti *= 2;
    }
    else if(modifier == 4)
    {
      wordMulti *= 3;
    }

    wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
    letterMulti = 1;
    x++;
    while(theGameBoard[x][y].SquareValue != '-')
    {
      primaryString.push_back(theGameBoard[x][y].SquareValue);
      if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
      x++;
    }
    x = originalX - 1;
    while(theGameBoard[x][y].SquareValue != '-')
    {
      primaryString.push_front(theGameBoard[x][y].SquareValue);
      if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
      x--;
    }
    points += wordPoints * wordMulti;
    wordMulti = 1;
    wordPoints = 0;
    strings.push_back(primaryString);
    for(it; it != activeSpots.end(); it++)
    {
      deque<char> nextString;
      x = originalX;
      y = originalY;
      nextString.push_back(theGameBoard[x][y].SquareValue);
      if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
      y++;
      while(theGameBoard[x][y].SquareValue != '-')
      {
        nextString.push_back(theGameBoard[x][y].SquareValue);
        if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
        y++;
      }
      y = originalY - 1;
      while(theGameBoard[x][y].SquareValue != '-')
      {
        nextString.push_front(theGameBoard[x][y].SquareValue);
        if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
        y--;
      }
      strings.push_back(nextString);
      points += wordPoints * wordMulti;
      wordMulti = 1;
      wordPoints = 0;
    }
  }
  if(orientation == true)
  {
    //set<pair<int, int>> activeSpots;
    x = originalX = (*it).first;
    y = originalY = (*it).second;
    primaryString.push_back(theGameBoard[x][y].SquareValue);
    if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
    y++;
    while(theGameBoard[x][y].SquareValue != '-')
    {
      primaryString.push_back(theGameBoard[x][y].SquareValue);
      if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
      y++;
    }
    y = originalY - 1;
    while(theGameBoard[x][y].SquareValue != '-')
    {
      primaryString.push_front(theGameBoard[x][y].SquareValue);
      if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
      y--;
    }
    strings.push_back(primaryString);
    points += wordPoints * wordMulti;
    wordMulti = 1;
    wordPoints = 0;
    for(it; it != activeSpots.end(); it++)
    {
      deque<char> nextString;
      x = originalX;
      y = originalY;
      nextString.push_back(theGameBoard[x][y].SquareValue);
      if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
      x++;
      while(theGameBoard[x][y].SquareValue != '-')
      {
        nextString.push_back(theGameBoard[x][y].SquareValue);
        if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
        x++;
      }
      x = originalX - 1;
      while(theGameBoard[x][y].SquareValue != '-')
      {
        nextString.push_front(theGameBoard[x][y].SquareValue);
        if(theGameBoard[x][y].active)
      {
        if(modifier == 1)
        {
          letterMulti *= 2;
        }
        else if(modifier == 2)
        {
          letterMulti *= 3;
        }
        else if(modifier == 3)
        {
          wordMulti *= 2;
        }
        else if(modifier == 4)
        {
          wordMulti *= 3;
        }
      }
      wordPoints += letterScores[theGameBoard[x][y].SquareValue - 'a'] * letterMulti;
      letterMulti = 1;
        x--;
      }
      strings.push_back(nextString);
      points += wordPoints * wordMulti;
      wordMulti = 1;
      wordPoints = 0;
    }
  }

  /*
  vector<deque<char> > strings;
  set<pair<int, int> >::iterator it = activeSpots.begin();
  deque<char> primaryString;*/
  vector<string> returnedStrings;
  deque<char>::iterator itt;
  for(int i = 0; i < strings.size(); i++)
  {
    string newString;
    for(itt = strings[i].begin(); itt != strings[i].end(); i++)
    {
      newString += *itt;
    }
    returnedStrings.push_back(newString);
  }
  return returnedStrings;
}
#endif // GAMEBOARD_H_INCLUDED
