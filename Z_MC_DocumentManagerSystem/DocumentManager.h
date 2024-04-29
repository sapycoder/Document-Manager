#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H
#pragma once
#include<bits/stdc++.h>
#include "UserManager.h"
#include "User.h"
#include "Document.h"
#include "History.h"
#include <mutex>
using namespace std;

class DocumentManager
{
private:
    //User Lists -> To create, update, delete if user loggedIn
    UserManager& userManager;

    map<int,Document> mapDocument; //id, new Document insert
    map<int,vector<History> > docHistory; //id,document (id for which we want to see)
    map<int,set<string> > setUserAccessForDoc; //docid, list of users id having access

    map<string, vector<Document> > userDocumentsStoreHistory; //key:userName_docId -> vector< map <versionId, Document> >

    //Multi-Threading
    static vector<bool> isUpdateInProgress; 

protected:

public:
    DocumentManager(UserManager& um);
    void createDocument(string userName="", string docName= "Untitled Document", string docData="", DOCUMENT_STATUS docStatus = DOCUMENT_STATUS::DRAFT);
    
    void viewAllDocument();
    void viewMyDocument(string userName);
    void viewDocument(int docId); //Anyone can view
    // void viewDocumentsWithFilter(string userName=nullptr, string docName=nullptr, int docVersion, DOCUMENT_STATUS docStatus); //Filter Document based on any of these params
    
    vector<Document> _getDocumentsForUserDocKey(string userDocKey);

    bool updateDocument(int docId, string userName, string newDocData); //Multiple Docs with same name, Id -> Update, Delete
    bool deleteDocument(int docId, string userName); //Author can delete only
    void getActiveVersionDocument(int docId);
    bool revertToPrevVersionDocument(int docId, string userName, int newDocVersion);

    void viewHistoryOfDocument(int docId);

    //grant permission for update to whom given access
    void grantUpdateAccessToUsers(int docId, set<string> listOfAccessUsers); //Document, Multiple Username

    void publishDraftDocument(int docId, string userName);

    ~DocumentManager();

};

#endif