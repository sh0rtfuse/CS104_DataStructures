//
//  UserList.cpp
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "UserList.h"
#include "User.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

UserList::UserList()
{

}

UserList::~UserList()
{
    
}

void UserList::addUser(User input)
{
    UserDatabase.push_front(input);
}

void UserList::UpdateUser(User input)
{
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        
        if (temp.getName() == input.getName())
        {
            UserDatabase.insert(Database_iter, temp);
        }
    }
}

User UserList::getUser(string name)
{
    User output;
    
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        
        if (name == temp.getName())
        {
            output = temp;
        }
    }
    
    return output;
}

//write all data to a file
void UserList::writeDatabase()
{
    string allusers;
    
    //store entire data into file named below
    ofstream fileout("UserDatabase.txt");
    
    //goes through list of users
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        string temp2 = temp.writeUser();
        
        allusers = temp2;
        
        //add to file
        fileout << allusers << endl;
    }
    
    fileout.close();
}

//read data from file
void UserList::readDatabase()
{
    ifstream filein;
    filein.open("UserDatabase.txt");
    
    while (!filein.eof())
    {
        string temp;
        User temp2;
        
        //grab a user and calls user class to process it
        getline(filein,temp);
        temp2.readUser(temp);
        
        //stores user onto private linkedlist database
        UserDatabase.push_front(temp2);
    }
}

//looks up users from database, and returns all related names
std::string UserList::DatabaseSearch(std::string name)
{
    string output;
    
    //go through user database
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        
        string temp2 = temp.getName();
        
        //check to see if User is the one you're looking for
        //if less than zero than the first letter to not match is shorter than query 
        if (name.compare(0, temp2.length(), temp2) < 0)
        {
            output += temp2;
            output += "|";
        }
    }
    
    return output;
}

//sends a friend request from one user to another
void UserList::sendFriendRequest(std::string name)
{
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        
        //if name matches a user, then add to that user's pending friends list
        if (temp.getName() == name)
        {
            temp.setpendingfriend(name);
        }
    }
}














