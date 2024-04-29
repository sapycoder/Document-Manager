#ifndef USERMANAGER_H
#define USERMANAGER_H
#pragma once
#include<bits/stdc++.h>
#include "User.h"
using namespace std;

class UserManager
{
private:
    string userName;
    string userPassword;
    static map<string,User> mapUser; //Unique Username, password
    static set<string> loggedInUser;

protected:

public:
    UserManager();
    void createUser(string pUserName, string pUserPassword);
    bool loginUser(string pUserName, string pUserPassword);
    bool logoutUser(string pUserName);

    static map<string,User> getMapUsers();
    static set<string> getLoggedInUsers();
    
    ~UserManager();

};

#endif