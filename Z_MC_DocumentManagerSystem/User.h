#ifndef USER_H
#define USER_H
#pragma once
#include<bits/stdc++.h>
using namespace std;

class User
{
private:
    int id;
    string userName;
    string userPassword;
protected:

public:
    User(int id=0, string userName="", string userPassword="");
    int getId();
    string getUserName();
    string getUserPassword();
    ~User();

};
//*defining basic models, service (users manager, document manager) ==> seperate the , functionality must be separated
//solid => flexible, understandable, maintainable 
//groking lld educative.io
//interface(IMP)-->flexibilty, abstarct classes, ()
#endif