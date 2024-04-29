#include "Document.h"
#include <bits/stdc++.h>
using namespace std;

Document::Document(){}
Document::Document(int pDocId, string pUserName, string pDocName, string pDocData, int pDocVersion, DOCUMENT_STATUS pDocStatus) : 
docId(pDocId), userName(pUserName), docName(pDocName), docData(pDocData), docVersion(pDocVersion), docStatus(pDocStatus), 
user_doc_key() {}

//Basic Getter
int Document::getDocId()
{
    return docId;
}
string Document::getUserName()
{
    return userName;
}
string Document::getDocName()
{
    return docName;
}
string Document::getDocData()
{
    return docData;
}
int Document::getDocversion()
{
    return docVersion;
}
DOCUMENT_STATUS Document::getDocStatus()
{
    return docStatus;
}

/*USER_DOC_KEY*/
string Document::getUserDocKey(string pUserName, int pDocId)
{
    string key ;
    key = pUserName + to_string(pDocId);
    return key;
}

// Document Operations - update/delete
void Document::updateDocData(int pDocId, string pNewDocData)
{
    docData = pNewDocData;
    docVersion++;
}
void Document::revertDocumentDataForVersion(int pDocId, string pUserName, string pDocName, string pDocData, int pDocVersion, DOCUMENT_STATUS pDocStatus){
    docId = pDocId;
    userName = pUserName;
    docName = pDocName;
    docData = pDocData;
    docVersion = pDocVersion;
    docStatus = pDocStatus;
}
void Document::updateDocVersion(int pDocId, int pNewDocVersion)
{
    docVersion--; // Reverting doc version
}
int Document::getLatestDocVersion(int pDocId)
{
    return getDocversion();
}
void Document::updateDocStatus(int pDocId){
    docStatus = DOCUMENT_STATUS::PUBLISHED;
}

//Display Doc
void Document::displayDoc(int pDocId)
{
    cout <<endl<< "-------------------DOCUMENT DATA FOR " << pDocId << "----------------------" << endl;
    cout << "Document ID: " << getDocId() << endl;
    cout << "Document Author: " << getUserName() << endl;
    cout << "Document Title: " << getDocName() << endl;
    cout << "Doc Data: " << getDocData() << endl;
    cout << "Doc Version: " << getDocversion() << endl;
    string status;
    switch (static_cast<int>(docStatus))
    {
    case static_cast<int>(DOCUMENT_STATUS::DRAFT):
        status = "DRAFT";
        break;
    case static_cast<int>(DOCUMENT_STATUS::PUBLISHED):
        status = "PUBLISHED";
        break;
    }
    cout << "Doc Status: " << status << endl;
    cout<<"-----------------------------xxx---------------------------"<<endl<<endl;
}
Document::~Document()
{
}