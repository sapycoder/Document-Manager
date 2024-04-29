#include "User.h"
#include<bits/stdc++.h>
using namespace std;

User::User(int pId, string pUsername, string pUserPassword) : id(pId), userName(pUsername), userPassword(pUserPassword) {}

int User::getId(){
    return id;
}

string User::getUserName(){
    return userName;
}

string User::getUserPassword(){
    return userPassword;
}
User::~User()
{

}