// Title    : Networking Implementation
// Author   : Christopher Scoggins
// Created  : 3/30/12
// Last Mod : 3/30/12
//
// Implements Networking Class Functions

#include "Networking.h"
#include <String>

using namespace std;

bool Networking::createAccount(String user, String pass, String email)
{
    bool result = false;
    String command = "command=createAccount&user=" + user + "&password=" + pass + "&email=" + email;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

// User Networking::getAllUsers()
//{
//
//}

bool Networking::login(String user, String pass)
{
    bool result = false;
    String command = "command=login&user=" + user + "&password=" + pass;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

bool Networking::changePassword(String oldPass, String newPass)
{
    bool result = false;
    String command = "command=changePassword&user=" + oldPass + "&oldPW=OldPassword&newPW=" + newPass;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

bool Networking::createGame(String user1, String user2)
{
    bool result = false;
    String command = "command=createGame&" + user1 + "=name&user2=" + user2;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

vector<int> Networking::getAllGameID(String user)
{
    vector<int> data;
    int get;
    String command = "command=getAllGameID&user=" + user;
    net << command;

    while(net >> get)
    {
        data.push_back(get);
    }

    return data;
}

vector<int> Networking::getActiveGameID()
{
    vector<int> data;
    int get;
    String command = "command=getActiveGameID&user=" + user;
    net << command;

    while(net >> get)
    {
        data.push_back(get);
    }

    return data;
}

bool Networking::setGameStatus(int gameID, bool status)
{
    bool result = false;
    String command = "command=setGameStatus&" + gameID + "=ID&status=";

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

// GameObject Networking::getGame(int gameID)
//{
//
//}

// bool Networking::updateGame(int gameID, GameObject, turn)
//{
//
//}

int Networking::getTurn(int gameID)
{
    bool result = false;
    int get;
    String command = " command=getTurn&gameID=" + gameID;
    net << command;
    net >> get;

    if(get == 1)
        result = true;

    return result;
}
