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

UserList::UserList(): TableUserNames(200000), TableNames(200000)
{

}

UserList::~UserList()
{
    
}

void UserList::addUser(User input)
{
    UserDatabase.push_front(input);
    
    //HW11
    string username = input.getUsername();
    string name = input.getName();
    
    int username_key = Hash(username);
    int name_key = Hash(name);
    
    TableUserNames.add(username_key, username);
    TableNames.add(name_key, name);
}

void UserList::UpdateUser(User input)
{
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        
        if (temp.getName() == input.getName())
        {
            UserDatabase.erase(Database_iter);
            UserDatabase.push_front(input);
            
            //HW11
            string username = input.getUsername();
            string name = input.getName();
            
            int username_key = Hash(username);
            int name_key = Hash(name);
            
            //remove old version and update to new olds
            TableUserNames.remove(username_key);
            TableNames.remove(name_key);
            TableUserNames.add(username_key, username);
            TableNames.add(name_key, name);
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
    //store entire data into file named below
    ofstream fileout("UserDatabase.txt");
    
    //goes through list of users
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        string temp2 = temp.writeUser();
        
        //add to file
        fileout << temp2 << endl;
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
    
    //HW11: Generates a map of the database
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        
        if (!temp.empty())
        {
            string username = temp.getUsername();
            string name = temp.getName();
            
            int username_key = Hash(username);
            int name_key = Hash(name);
            
            TableUserNames.add(username_key, username);
            TableNames.add(name_key, name);
        }
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
        if (temp2.compare(0, temp2.length(), name) >= 0)
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

//HW11 Additions
std::list<User> UserList::getUserDatabase()
{
    return UserDatabase;
}

User UserList::getUser2(string username)
{
    User output;
    
    for (std::list<User>::iterator Database_iter = UserDatabase.begin(); Database_iter != UserDatabase.end(); Database_iter++)
    {
        User temp = *Database_iter;
        
        if (username == temp.getUsername())
        {
            output = temp;
        }
    }
    
    return output;
}

//HW11: Searching w/ a Hashtable (Problem 4)
int UserList::Hash(std::string key)
{
    int output = 0;
    
    for (int i = 0; i < key.length(); i++)
    {
        char letter = key.at(i);
        output += int(letter);
    }
    
    return output;
}

//true = username false = name
std::string UserList::HashDatabaseSearch(std::string name, bool SearchBy)
{
    string output;
    
    //search by username
    if (SearchBy == true)
    {
        int result_key = Hash(name);
        
        string result = TableUserNames.get(result_key);
        
        output += "Username: ";
        output += result;
    }
    
    //search by name
    if (SearchBy == false)
    {
        int result_key = Hash(name);
        
        string result = TableNames.get(result_key);
        
        output += "Name: ";
        output += result;
    }
    
    return output;
}






