// Title    : Networking Implementation
// Author   : Christopher Scoggins
// Created  : 3/30/12
// Last Mod : 3/30/12
//
// Implements Networking Class Functions

#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED

#include "Wwf.h"
#include <vector>

using namespace std;

class Networking
{
    private:

    wwfstream net;

    public:

    bool createAccount(string user, string pass, string email);

    // string getAllUsers();

    bool login(string user, string pass);

    bool changePassword(string oldPass, string newPass);

    bool createGame(string user1, string user2);

    vector<int> getAllGameID(string user);

    vector<int> getActiveGameID(string user);

    bool setGameStatus(int gameID, bool status);

    // GameObject getGame(int gameID);

    // bool updateGame(int gameID, GameObject, turn);

    bool getTurn(int gameID);       // Returns True if it is the game creator's turn, and false if it is the other players turn.

};

#endif // NETWORKING_H_INCLUDED
