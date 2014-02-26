//
//  UserList.cpp
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "UserList.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

userlist::userlist ()
{
    LinkedList<string> thelist;
}

userlist::~userlist()
{
    
}

void userlist::adduser(string name, string password, string birthday)
{
    user list;
    
    //call setter functions for user data
    list.editname(name);
    list.editpassword(password);
    list.editbirthday(birthday);
    
    //combine them into one string, then store said string in a list of users
    string completeuser;
    list.readinuserdata(completeuser);
    thelist.add(completeuser);
}

void userlist::deleteuser(string user)
{
    //check to see if user exists
    bool search = thelist.find(user);
    
    //if yes, then remove
    if (search == true)
    {
        thelist.remove(user);
    }
    
    //if not, return error message
    else
    {
        cout << "Sorry, the user you want to delete does not exist" << endl;
    }
}

//prints out all the users to a file to "save" the network
void userlist::printall()
{
    string allusers;
    string outfile = "user.txt";
    
    thelist.printlist(allusers);
    
    ofstream fileout(outfile.c_str());
    fileout << allusers;
    fileout.close();
}

//load in from a string
void userlist::loadall(string input)
{
    //reading user data as soon as class is called
    //turns the temp string into a stream
    istringstream stream(input);
    
    while (!stream.eof())
    {
        string name, password, birthday;
        
        //parses the temp string stream and stores each element in a private variable
        getline(stream, name, ' ');
        getline(stream, password, ' ');
        getline(stream, birthday, ' ');
        
        //add to userlist
        adduser(name, password, birthday);
    }
}

//checks if user is in the list
bool userlist::usersearch(string query)
{
    if (thelist.find(query) == true)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}






