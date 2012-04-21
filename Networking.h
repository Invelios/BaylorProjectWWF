// Title    : Networking Implementation
// Author   : Christopher Scoggins
// Created  : 3/30/12
// Last Mod : 4/20/12
//
// Implements Networking Class Functions

#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED

#include "GameBoard.h"
#include "Wwf.h"
#include <vector>
#include <string>

using namespace std;

class Networking
{
    private:

    wwfstream net;

    public:

    bool createAccount(string user, string pass, string email);

    vector<string> getAllUsers();

    bool login(string user, string pass);

    bool changePassword(string oldPass, string newPass);

    bool createGame(string user1, string user2);

    vector<int> getAllGameID(string user);

    vector<int> getActiveGameID(string user);

    bool setGameStatus(int gameID, bool status);

    string getGame(int gameID);

    bool updateGame(int gameID, GameBoard);

};

#endif // NETWORKING_H_INCLUDED
