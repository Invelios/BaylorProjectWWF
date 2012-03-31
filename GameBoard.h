#ifndef GAMEBOARD_H_INCLUDED
#define GAMEBOARD_H_INCLUDED

#include <utility>
#include <iostream>
#include <fstream>
#include <string>

class GameBoard
{
    static int BOARD_LENGTH = 15;
    static string FILE_NAME = "board.txt";
    static string END_OF_FILE_ERROR = "NUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
    class GameBoard::GameBoard()
    {
        Tile[BOARD_LENGTH][BOARD_LENGTH] theGameBoard;
    }
    class Tile
    {
        private:
        pair<int, int> x, y;
        char tileValue;
        bool used;
        char baseValue;

        public:
        class Tile()
        {
            x = 0;
            y = 0;
            tileValue = '-';
            used = false;
            baseValue = '0';
        }
    }

    /*
    baseValue:
    - = Origin
    0  = Blank
    1  = Double Letter
    2  = Triple Letter
    3  = Double Word
    4  = Triple Word
    */
    initialize()
    {
        char temp;
        ifstream inputFile;
        inputFile.open(FILE_NAME.c_str());
        for(int i = 0; i < BOARD_LENGTH; i++)
        {
            for(int j = 0; j < BOARD_LENGTH; j++)
            {
                if(inputFile.eof())
                    throw(END_OF_FILE_ERROR);
                inputFile.get(tileValue);
                inputFile.get(baseValue);
                inputFile.get(temp);
                if(temp == '+')
                    used = true;
            }
            inputFile.ignore(1, '\n');
        }
    }

    bool placeTile(pair<int, int>, char)
    {

    }

    //removeTile(pair<int, int>)

    //verifySpace(pair<int, int>)

    //verifyPlay
    //Return integer for multiple failure cases.
    //All newly placed tiles must be in the row or column.
    //Must be adjacent to an already-existing tile, or the Origin Spot.

    //verifyWord
    //Returns true or false if word is within the dictionary, takes in string.

    //constructStrings

    //calculateWord
    //Identify tile bonuses and erase if utilized. Replace if undone.

    //toString
    //The grid and tile placement, player scores, player decks, active player, bag count.

    //update
    //reconstruct game board from string form.
}

#endif // GAMEBOARD_H_INCLUDED
