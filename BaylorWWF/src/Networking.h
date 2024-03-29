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

//wwfstream thenet;

class Networking
{
    private:
    static Networking * instance;
    wwfstream net;
    Networking(){}
    /* public:
       static Singleton* getInstance( );
       ~Singleton( );
   private:
       Singleton( );
       static Singleton* instance;*/

    public:
      wwfstream theNet;
    static Networking * getInstance()
    {
      return instance;
    }

    bool createAccount(string user, string pass, string email);

    vector<string> getAllUsers();

    bool login(string user, string pass);

    bool changePassword(string user, string oldPass, string newPass);

    bool createGame(string user1, string user2);

    vector<int> getAllGameID(string user);

    vector<int> getActiveGameID(string user);

    bool setGameStatus(int gameID, bool status);

    string getGame(int gameID);

    bool updateGame(int gameID, GameBoard);

};

Networking * Networking::instance = new Networking();
/*class Log {
  public:
    static Log* Inst(char* filename);
    void Logging(string message);
    void Initialize();
    ~Log();
  protected:
    Log(); // constructor
  private:
    static Log* pInstance;
};

We declare an Inst() function, which will return our static Log class pointer. We have an instance called pInstance, which is our static pointer to our class. As well as the constructor and other functions.
C++ Singleton File

The cpp file (C++ file) below:
Log* Log::pInstance = NULL;

Log* Log::Inst(char* filename){
  if(pInstance == NULL){
    pInstance = new Log(filename);
  }
  return pInstance;
}

Log::Log(){ // constructor
  Initialize(); // you can ignore this function
}*/
//************************************************************
// Desription: Communicated with the server to create an account
// Return: bool
// Pre: networking was constructed
// Post:
//************************************************************

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

//************************************************************
// Desription: Gets all users from the server
// Return: vector<string>
// Pre: networking object constructed
// Post:
//************************************************************

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

//************************************************************
// Desription: Verifys that the user/pass combo is a valid combo on the server
// Return: bool
// Pre: networking Object constructed
// Post:
//************************************************************

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

//************************************************************
// Desription: Tells server to change a users password
// Return: bool
// Pre: networking Object Constructed
// Post:
//************************************************************

bool Networking::changePassword(string user, string oldPass, string newPass)
{
    bool result = false;
    string command = "command=changePassword&user=" + user + "&oldPW=" + oldPass + "&newPW=" + newPass;
    net << command;
    net >> command;

    if(command == "PASS")
        result = true;

    return result;
}

//************************************************************
// Desription: creates a game between 2 users
// Return: bool
// Pre: networking Object Constructed
// Post:
//************************************************************

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

//************************************************************
// Desription: Will get all gameIDs from the server for a user
// Return: vector<int>
// Pre: networking Object Constructed
// Post:
//************************************************************

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

//************************************************************
// Desription: Get active gameIDs from the server for a user
// Return: vector<int>
// Pre: networking Object Constructed
// Post:
//************************************************************

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

//************************************************************
// Desription: Will set the game status as ACTIVE or INACTIVE
// Return: bool
// Pre: networking object constructed
// Post:
//************************************************************

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

//************************************************************
// Desription: Will get the string to construct the game for the given gameID
// Return: string
// Pre: networking Object constructed
// Post:
//************************************************************

string Networking::getGame(int gameID)
{
    string command = "command=getGame&gameID=" + gameID;

    net << command;
    net >> command;

    return  command;
}

//************************************************************
// Desription: Updates the games' string representation on the server
// Return: bool
// Pre: networking Object Constructed
// Post:
//************************************************************

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
