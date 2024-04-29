#include "UserManager.h"
#include<bits/stdc++.h>
using namespace std;

set<string> UserManager::loggedInUser;
map<string,User> UserManager::mapUser;

UserManager::UserManager() {}

//----------------------------------For User----------------------------------------
// Create user
void UserManager::createUser(string pUserName, string pUserPassword)
{
    //New User
    if(mapUser.find(pUserName)==mapUser.end()){
        User newUser = User(mapUser.size()+1, pUserName, pUserPassword); //TODO : hashing of password
        mapUser[pUserName] = newUser;
        cout << "User created Successfully!" << endl;
        return;
    }
    //Old User - Ask User to Login
    cout << "User already registered with this Username. Please Login or choose another Username!" << endl;
    return;
}

// Login user
bool UserManager::loginUser(string pUserName, string pUserPassword)
{
    if (mapUser.find(pUserName) != mapUser.end())
    {
        if(loggedInUser.find(pUserName) != loggedInUser.end()){
            cout<<mapUser[pUserName].getUserName()<<", You are already Logged In!"<<endl;
            return true;
        }
        else if (mapUser[pUserName].getUserPassword() == pUserPassword)
        {
            loggedInUser.insert(pUserName);
            cout << mapUser[pUserName].getUserName()<<", You have been Logged In Sucessfully!" << endl;
            return true;
        }
        else
        {
            cout << "Password Incorrect!" << endl;
            return false;
        }
    }
    cout << "User not Registered!" << endl;
    return false;
}

// Logout user
bool UserManager::logoutUser(string pUserName)
{
    if (loggedInUser.find(pUserName) != loggedInUser.end())
    {
        loggedInUser.erase(pUserName);
        cout<<mapUser[pUserName].getUserName()<<", You have been Logged Out Successfully!"<<endl;
        return true;
    }
    cout << "User is not Logged In or not Registered." << endl;
    return false;
}

map<string,User> UserManager :: getMapUsers(){
    return mapUser;
}

set<string> UserManager :: getLoggedInUsers(){
    return loggedInUser;
}
UserManager::~UserManager()
{

}