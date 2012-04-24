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

bool Networking::createAccount(string user, string pass, string email)
{
    bool result = false;
    string command = "command=createAccount&user=" + user + "&password=" + pass + "&email=" + email;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

vector<string> Networking::getAllUsers()
{
    vector<string> theUserVector;
    string command = "command=getAllUsers";
    net << command;

    while(net >> command)
    {
        theUserVector.push_back(command);
    }

    return theUserVector;
}

bool Networking::login(string user, string pass)
{
    bool result = false;
    string command = "command=login&user=" + user + "&password=" + pass;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

bool Networking::changePassword(string oldPass, string newPass)
{
    bool result = false;
    string command = "command=changePassword&user=" + oldPass + "&oldPW=OldPassword&newPW=" + newPass;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

bool Networking::createGame(string user1, string user2)
{
    bool result = false;
    string command = "command=createGame&" + user1 + "=name&user2=" + user2;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

vector<int> Networking::getAllGameID(string user)
{
    vector<int> data;
    string get;
    int getInt;
    string command = "command=getAllGameID&user=" + user;
    net << command;

    while(net >> get)
    {
        getInt = atoi(get.c_str());
        data.push_back(getInt);
    }

    return data;
}

vector<int> Networking::getActiveGameID(string user)
{
    vector<int> data;
    string get;
    int getInt;
    string command = "command=getActiveGameID&user=" + user;
    net << command;

    while(net >> get)
    {
        getInt = atoi(get.c_str());
        data.push_back(getInt);
    }

    return data;
}

bool Networking::setGameStatus(int gameID, bool status)
{
    bool result = false;
    string command = "command=setGameStatus&" + gameID;
    command += "=ID&status=";

    if(status)
        command += "ACTIVE";
    else
        command += "INACTIVE";

    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

GameBoard * Networking::getGame(int gameID)
{
    string command = "command=getGame&gameID=" + gameID;

    net << command;
    net >> command;

    return  new GameBoard(command);
}

 bool Networking::updateGame(int gameID, GameBoard aGameBoard)
{
    bool result = false;
    string command = "command=updateGame&gameID=" + gameID + '&';
    command = command + "gameObject=" + aGameBoard.toString();

    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

 #endif // NETWORKING_H_INCLUDED
