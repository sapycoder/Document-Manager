#include "DocumentManager.h"
#include <bits/stdc++.h>
#include "UserManager.h"
#include "User.h"
#include "Document.h"
#include "History.h"
using namespace std;

vector<bool> DocumentManager::isUpdateInProgress; //On one Document only one Update Operation can take place

DocumentManager::DocumentManager(UserManager& um) : userManager(um), mapDocument(), docHistory(), setUserAccessForDoc(), userDocumentsStoreHistory()
{}

// ------------------------------For Document-----------------------------------------
// Create Document
void DocumentManager::createDocument(string pUserName, string pDocName, string pDocData, DOCUMENT_STATUS pDocStatus)
{
    //Authorization - User not Logged In
    set<string> um_loggedInUsers = userManager.getLoggedInUsers();
    if(um_loggedInUsers.find(pUserName) == um_loggedInUsers.end()){
        cout<<"Your are not Logged In! Please Login to make any changes to Document"<<endl;
        return;
    }

    //Authorization - User Logged In
    //Map-Document stores all the documents
    int docIndx = mapDocument.size()+1;
    int docVersion = 1;
    Document newDocument = Document(docIndx, pUserName, pDocName, pDocData, docVersion, pDocStatus); //Intially at the time of creation version will start from 1
    mapDocument[docIndx] = newDocument;
    Document document;
    string userDocKey = document.getUserDocKey(pUserName,docIndx);
    userDocumentsStoreHistory[userDocKey].push_back(newDocument);

    //History
    time_t currentTime = time(0);
    char *dt = ctime(&currentTime);
    History createHistory = History("Document created", dt, pUserName);
    docHistory[docIndx].push_back(createHistory);

    //Grant List - Access to update Document - Author + Shared Users
    setUserAccessForDoc[docIndx].insert(pUserName); //Add Author to access list for updating Document

    cout << "Document created Successfully!" << endl;
}

// View All Document
void DocumentManager::viewAllDocument()
{
    //Display all Published Documents
    cout<<endl<<"Displaying all Documents"<<endl;
    for (auto it : mapDocument)
    {
        Document document = it.second;
        if (document.getDocStatus() == DOCUMENT_STATUS::PUBLISHED)
            document.displayDoc(it.first);
    }
}

// View My Document
void DocumentManager::viewMyDocument(string pUserName)
{
    //Display Author's Published and not Published Documents
    cout<<endl<<"Displaying Documents for "<<pUserName<<endl;
    for (auto it : mapDocument)
    {
        Document document = it.second; 
        if (document.getUserName() == pUserName)
            document.displayDoc(it.first); 
    }
}

// View Document
void DocumentManager::viewDocument(int pDocId)
{ 
    cout<<endl<<"Displaying Document for Id = "<<pDocId<<endl;
    if (mapDocument.find(pDocId) != mapDocument.end())
    {
        if (mapDocument[pDocId].getDocStatus() == DOCUMENT_STATUS::PUBLISHED)
            mapDocument[pDocId].displayDoc(pDocId);
    }
    else
        cout << "Document dosen't exist" << endl;
}

//--------------------------------------------------------------------
// TODO : Filter Document based on certain @params
// void DocumentManager::viewDocumentsWithFilter(string pDocName){
    
// }
//--------------------------------------------------------------------

// Update Document
bool DocumentManager::updateDocument(int pDocId, string pUserName, string pNewDocData)
{
    //Authorization - User not Logged In
    set<string> um_loggedInUsers = userManager.getLoggedInUsers();
    if(um_loggedInUsers.find(pUserName) == um_loggedInUsers.end()){
        cout<<"Your are not Logged In! Please Login to make any changes to Document"<<endl;
        return false;
    }

    //Authorization - User Logged In - All users in Access List can update
    isUpdateInProgress.resize(mapDocument.size()+1);
    if(isUpdateInProgress[pDocId]){
        cout<<"Another update operation is already in progress. Please try again later!"<<endl;
        return false;
    }
    isUpdateInProgress[pDocId]  = true;

    if (mapDocument.find(pDocId) != mapDocument.end())
    {
        // If User present in Access List -> User can update the document
        if (setUserAccessForDoc[pDocId].find(pUserName) != setUserAccessForDoc[pDocId].end()) 
        {
            mapDocument[pDocId].updateDocData(pDocId, pNewDocData);
            mapDocument[pDocId].displayDoc(pDocId);

            //Every update will change the vesion of the documant
            Document document;
            string userDocKey = document.getUserDocKey(pUserName,pDocId);
            userDocumentsStoreHistory[userDocKey].push_back(mapDocument[pDocId]);

            //History
            time_t currentTime = time(0);
            char *dt = ctime(&currentTime);
            History createHistory = History("Document updated", dt, pUserName);
            docHistory[pDocId].push_back(createHistory);

            cout << "Document updated Succesfully" << endl;
            isUpdateInProgress[pDocId] = false;
            return true;
        }

        else
        {
            isUpdateInProgress[pDocId]  = false;
            cout << "You are not authorized to update the document" << endl;
            return false;
        }
    }
    cout << "Document dosen't exist" << endl;
    return false;
}

// Delete Document
bool DocumentManager::deleteDocument(int pDocId, string pUserName)
{
    //Authorization - User not Logged In
    set<string> um_loggedInUsers = userManager.getLoggedInUsers();
    if(um_loggedInUsers.find(pUserName) == um_loggedInUsers.end()){
        cout<<"Your are not Logged In! Please Login to make any changes to Document"<<endl;
        return false;
    }

    //Authorization - User Logged In - Only Author can delete
    if (mapDocument.find(pDocId) != mapDocument.end())
    {
        if (mapDocument[pDocId].getUserName() == pUserName)
        {
            mapDocument.erase(pDocId);

            //Deleting the Document will erase all the Version History 
            Document document;
            string userDocKey = document.getUserDocKey(pUserName,pDocId);
            userDocumentsStoreHistory.erase(userDocKey);

            time_t currentTime = time(0);
            char *dt = ctime(&currentTime);
            History createHistory = History("Document deleted", dt, pUserName);
            docHistory[pDocId].push_back(createHistory);//delete 

            cout << "Document deleted Succesfully" << endl;
            return true;
        }
        else
        {
            cout << "You are not authorized to delete the document" << endl;
            return false;
        }
    }
    cout << "Document dosen't exist" << endl;
    return false;
}

vector<Document> DocumentManager :: _getDocumentsForUserDocKey(string pUserDocKey){
    return userDocumentsStoreHistory[pUserDocKey];
}

// Access Document of Previous Version 
bool DocumentManager::revertToPrevVersionDocument(int pDocId, string pUserName, int pNewDocVersion) 
{
    //Authorization - User not Logged In
    set<string> um_loggedInUsers = userManager.getLoggedInUsers();
    if(um_loggedInUsers.find(pUserName) == um_loggedInUsers.end()){
        cout<<"Your are not Logged In! Please Login to make any changes to Document"<<endl;
        return false;
    }

    //Authorization - User Logged In - Only Author can Revert the Document Version
    if (mapDocument.find(pDocId) != mapDocument.end())
    {
        if (mapDocument[pDocId].getUserName() == pUserName)
        {
            /*
                1.Get the userDoc_Key 
                2.Search in the <Documents> list for reverted version
                3.Update the Document with "Searched" one (docIndx, pUserName, pDocName, pDocData, pDocVersion, pDocStatus);
                4.Update in mapDoc from where we are fetching data everywhere
            */
            Document document;
            string userDocKey = document.getUserDocKey(pUserName,pDocId);
            vector<Document> documentsWithUserNameAndDocId = _getDocumentsForUserDocKey(userDocKey);
            if(pNewDocVersion==0 || pNewDocVersion > documentsWithUserNameAndDocId.size()){
                cout<<endl<<"Document does contain this version!"<<endl;
                return false;
            }
            Document displayRevertedVersion = documentsWithUserNameAndDocId[pNewDocVersion-1]; //0 based indexing for vector
            mapDocument[pDocId].revertDocumentDataForVersion(
                displayRevertedVersion.getDocId(), 
                displayRevertedVersion.getUserName(),
                displayRevertedVersion.getDocName(),
                displayRevertedVersion.getDocData(),
                displayRevertedVersion.getDocversion(),
                displayRevertedVersion.getDocStatus()
            );
            mapDocument[pDocId].displayDoc(pDocId);

            //History
            time_t currentTime = time(0);
            char *dt = ctime(&currentTime);
            string msg = "Document Reverted to Version: " + to_string(pNewDocVersion);
            History createHistory = History(msg, dt, pUserName);
            docHistory[pDocId].push_back(createHistory);

            cout << "Document Version Reverted Succesfully to Version: " << mapDocument[pDocId].getLatestDocVersion(pDocId)<<" for Doc Id: "<< pDocId << endl;
            return true;
        }
        else
        {
            cout << "You are not authorized to revert the document version" << endl;
            return false;
        }
    }
    cout << "Document dosen't exist" << endl;
    return false;
}

// Get Active/Latest version of Document
void DocumentManager::getActiveVersionDocument(int pDocId)
{
    if (mapDocument.find(pDocId) != mapDocument.end())
    {
        int latestVersion = mapDocument[pDocId].getLatestDocVersion(pDocId);
        cout << "Latest Version of Doc " << pDocId << " is = " << latestVersion << endl;
        return;
    }
    cout << "Document dosen't exist" << endl;
}

// History of Document
/*
 @param: id -> history (msg, timestamp)
*/
void DocumentManager::viewHistoryOfDocument(int pDocId)
{
    cout <<endl<< "-------------------------------------- Doc History for DocId " << pDocId << " -------------------------------------- " <<endl<< endl;
    for (auto it : docHistory[pDocId])
    {
        cout << it.getMsg() << " by " << it.getHistoryUserName() << " on " << it.getCurrentTime() << endl;
    }
}

//Grant Update Access to User
void DocumentManager::grantUpdateAccessToUsers(int pDocId, set<string> listOfAccessUsers)
{
    for (auto it : listOfAccessUsers)
    {
        setUserAccessForDoc[pDocId].insert(it);
    }
}

// Publish Draft Document - Author
void DocumentManager::publishDraftDocument(int pDocId, string pUserName)
{
    if (mapDocument.find(pDocId) != mapDocument.end())
    {
        if(mapDocument[pDocId].getUserName() == pUserName && mapDocument[pDocId].getDocStatus() == DOCUMENT_STATUS::PUBLISHED){
            cout << "This Document is already Published." << endl;
            return;
        }
        else if (mapDocument[pDocId].getUserName() == pUserName && mapDocument[pDocId].getDocStatus() == DOCUMENT_STATUS::DRAFT)
        {
            mapDocument[pDocId].updateDocStatus(pDocId);
            mapDocument[pDocId].displayDoc(pDocId);

            //History
            time_t currentTime = time(0);
            char *dt = ctime(&currentTime);
            History createHistory = History("Document Published", dt, pUserName);
            docHistory[pDocId].push_back(createHistory);

            cout << "Document Published Successfully!" << endl;
            return;
        }
        else
        {
            cout << "You don't have permission to Publish this Document!" << endl;
            return;
        }
    }
    cout << "Document dosen't exist" << endl;
    return;
}

DocumentManager::~DocumentManager()
{
}