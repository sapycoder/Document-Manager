#ifndef HISTORY_H
#define HISTORY_H
#pragma once
#include "Document.h"
#include<bits/stdc++.h>
using namespace std;

class History
{
private:
    string msg; //creta
    char* currentTime;
    string userName;

    //document
protected:

public:
    History(string pMsg, char* pCurrentTime, string pUserName);
    string getMsg();
    char* getCurrentTime();
    string getHistoryUserName();
    ~History();

};

#endif