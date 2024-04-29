#include<bits/stdc++.h>
#include "UserManager.h"
#include "DocumentManager.h"
#include "Constants.h"
#include <thread>
using namespace std;

// Handling Thread Safety - Update document instances
void updateDocumentInstance1(DocumentManager &dm) {
    dm.updateDocument(1, "Anil", "Updated content for Anil Document - 3");
}

void updateDocumentInstance2(DocumentManager &dm) {
    dm.updateDocument(1, "Anjali", "Updated content for Anjali Document - 5");
}

void updateDocumentInstance3(DocumentManager &dm) {
    dm.updateDocument(3, "Anjali", "Updated content for Anjali Document - 2");
}

set<string> getUsersWithAccessPermission(){
    set<string> listOfAccessUsers;
    bool stop;
    while(!stop){
        string userName;
        char c;
        cout<<"Please enter the User Name you want to grant modify permission: ";
        cin>>userName;
        listOfAccessUsers.insert(userName);
        cout<<"Do you wish to add more Users (y/n)? : ";
        cin>>c;
        if(tolower(c)=='n'){stop = true;}
    }
    return listOfAccessUsers;
}

int main(){
    //To be inputed by client
    UserManager um;
    DocumentManager dm(um);

    //Create user -  Input Unique user Name
    um.createUser("Anil","pwd1");
    um.createUser("Anjali","pwd2");
    um.createUser("Ajay","pwd3");
    um.createUser("Anil","pwd3"); //user already exists with this Username

    //Login user - with Username and Userpassword
    um.loginUser("Anil","pwd2"); //password not matched
    um.loginUser("Anil","pwd1");
    um.loginUser("Anjali","pwd2");
    um.loginUser("Ajay","pwd3");
    um.loginUser("Ajay","pwd3"); //already logged in

    //Logout User
    um.logoutUser("Ajay");
    um.loginUser("Ajay","pwd3");


    //Create document - For Logged In Users only
    dm.createDocument("Anil", "Anil Document - 1", "Document content 1", DOCUMENT_STATUS::PUBLISHED); 
    dm.createDocument("Anil", "Anil Document - 2", "Document content 2"); 
    dm.createDocument("Anjali", "Anjali Document - 1", "Document content", DOCUMENT_STATUS::PUBLISHED); 
    dm.createDocument("Ajay", "Ajay Document - 1", "Document content", DOCUMENT_STATUS::PUBLISHED);

    //Update document - For Logged In Users and Users in access List
    dm.viewAllDocument(); //Get Document Id from this and update
    dm.updateDocument(1,"Anil", "Updated content for Anil Document - 1");

    //View Document Methods
    dm.viewAllDocument();
    dm.viewDocument(1);
    dm.viewMyDocument("Anil");

    //Delete Document
    dm.deleteDocument(4, "Anil");// Error -> Other user tries to Delete
    dm.deleteDocument(4, "Ajay");// Delete Document - 4 for Ajay 

    //Get Latest Version
    dm.getActiveVersionDocument(1); //Anil , Document 1 ==> version = 2

    //Revert to previous version
    dm.revertToPrevVersionDocument(1,"Anil", 1); //Reverting to version to 1
    dm.getActiveVersionDocument(1); //Anil , Document 1 ==> version = 1 , as updated to previous version
    dm.revertToPrevVersionDocument(1,"Anil", 3); //Error - Reverting to version to 3 which does not exist
    dm.revertToPrevVersionDocument(1,"Anil", 2); //Reverting to version to 2
    dm.getActiveVersionDocument(1); 


    //View History of Document
    dm.viewHistoryOfDocument(1);

    //Other functionality to Grant Access to Users to Update Doc
    set<string> listOfAccessUsers = getUsersWithAccessPermission();
    dm.grantUpdateAccessToUsers(1, listOfAccessUsers);
    listOfAccessUsers.clear();
    dm.updateDocument(1,"Anil", "Updated content for Anil Document - 1"); //Author wants to update
    dm.updateDocument(1,"Ketan", "Updated content for Anil Document - 3"); //Not given access to update
    dm.updateDocument(1,"Anjali", "Updated content for Anil Document - 4 - by Anjali"); //Other User wants to update

    //publish the draft document if not already published
    dm.publishDraftDocument(1,"Ajay"); //Unauthorized
    dm.publishDraftDocument(1,"Anil"); //Already Published
    dm.publishDraftDocument(2,"Anil"); //Published Successfuly
    dm.viewHistoryOfDocument(1);
    dm.viewHistoryOfDocument(2);

    //TODO: **IMP** -> If 2 Users try to update the document at the same time allow only one to execute ==> Multithreading
    cout<<endl<<"----------------------******-----------------Thread Safety----------------------******-----------------"<<endl; 
    // Create threads for updating documents
    thread t1(updateDocumentInstance1, std::ref(dm)); //Updating on Doc - 1
    thread t2(updateDocumentInstance2, std::ref(dm)); //Updating on Doc - 1
    thread t3(updateDocumentInstance3, std::ref(dm)); //Updating on Doc - 3
    t1.join();
    t2.join();
    t3.join();
    dm.viewDocument(1);
    dm.viewHistoryOfDocument(1);
    dm.viewHistoryOfDocument(3);
    return 0;
}