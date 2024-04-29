#include "History.h"
#include<bits/stdc++.h>
using namespace std;

History::History(string pMsg, char* pCurrentTime, string pUserName) : msg(pMsg), currentTime(pCurrentTime), userName(pUserName)
{

}
string History::getMsg(){
    return msg;
}
char* History::getCurrentTime(){
    return currentTime;
}
string History::getHistoryUserName(){
    return userName;
}
History::~History()
{

}