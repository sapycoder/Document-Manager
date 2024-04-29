#ifndef DOCUMENT_H
#define DOCUMENT_H
#pragma once
#include<bits/stdc++.h>
#include "Constants.h"
using namespace std;

class Document
{
private:
    int docId;
    string userName;
    string docName;
    string docData;
    int docVersion;
    DOCUMENT_STATUS docStatus;
    string user_doc_key;

protected:

public:
    Document();
    Document(int docId, string userName, string docName="Untitled Document", string docData="", int docVersion=1, DOCUMENT_STATUS pDocStatus = DOCUMENT_STATUS::DRAFT);
    int getDocId();
    string getUserName();
    string getDocName();
    string getDocData();
    int getDocversion();
    DOCUMENT_STATUS getDocStatus();
    string getUserDocKey(string userName, int docId);
    
    void updateDocData(int docId, string docData);
    void updateDocVersion(int docId, int newDocVersion);
    int getLatestDocVersion(int docId);
    void updateDocStatus(int docId);

    void revertDocumentDataForVersion(int docId, string userName, string docName="Untitled Document", string docData="", int docVersion=1, DOCUMENT_STATUS pDocStatus = DOCUMENT_STATUS::PUBLISHED);
    
    void displayDoc(int docId);
    ~Document();

};

#endif