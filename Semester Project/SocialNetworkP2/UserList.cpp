//
//  UserList.cpp
//  HW6
//
//  Created by Raymond Dam on 10/29/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "UserList.h"
#include "User.h"
#include <fstream>
#include <sstream>

UserList::UserList()
{
    index = 0;
}

UserList::~UserList()
{
    
}

void UserList::addUser(User input)
{
    UserDatabase.set(index, input);
    index++;
}

void UserList::removeUser()
{
    UserDatabase.remove(index);
    index--;
}

User UserList::getUser()
{
    return UserDatabase.get(index);
}

//write all data to a file
void UserList::writeDatabase()
{
    string allusers;
    
    //goes through linkedlist of users
    for (int i = 0; i < UserDatabase.getlength(); i++)
    {
        User temp = UserDatabase.get(index);
        string temp2 = temp.writeUser();
        
        allusers += temp2;
        allusers += "*";    //a delimiter to let me know where each user ends
    }
    
    //store entire data into file named below
    string outfile = "UserDatabase.txt";
    ofstream fileout(outfile.c_str());
    fileout << allusers;
    fileout.close();
}

//read data from file
void UserList::readDatabase()
{
    string infile = "UserDatabase.txt";
    ifstream filein(infile.c_str());
    
    //stores the whole database onto the string
    string allusers;
    filein >> allusers;
    
    //parse for all users
    stringstream stream;
    
    while (!stream.eof())
    {
        string temp;
        User temp2;
        
        //grab a user and calls user class to process it
        getline(stream, temp, '*');
        temp2.readUser(temp);
        
        //stores user onto private linkedlist database
        UserDatabase.set(index, temp2);
        index++;
    }
}

//looks up friend from database
std::string UserList::friendfinder(std::string input)
{
    //go through user database
    for (int i = 0; i < UserDatabase.getlength(); i++)
    {
        User temp = UserDatabase.get(i);
        
        //check to see if User is the one you're looking for
        if (temp.getName() == input)
        {
            return temp.writeUser();
        }
    }
    
    std::string error = "Sorry. User Not Found.";
    return error;
}



















