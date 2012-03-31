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

    bool createAccount(String user, String pass, String email);

    // User getAllUsers();

    bool login(String user, String pass);

    bool changePassword(String oldPass, String newPass);

    bool createGame(String user1, String user2);

    vector<int> getAllGameID(String user);

    vector<int> getActiveGameID();

    bool setGameStatus(int gameID, bool status);

    // GameObject getGame(int gameID);

    // bool updateGame(int gameID, GameObject, turn);

    int getTurn(int gameID);

}

#endif // NETWORKING_H_INCLUDED
