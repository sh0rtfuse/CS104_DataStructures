//
//  User.cpp
//  HW6
//
//  Created by Raymond Dam on 10/29/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "User.h"
#include "WallPost.h"
#include <sstream>

using namespace std;

User::User()
{
    
}

User::~User()
{
    
}

//setter functions
void User::setName(string input)
{
    Name = input;
}

void User::setPassword(string input)
{
    Password = input;
}

void User::setBirthday(string input)
{
    Birthday = input;
}

//getter functions
string User::getName()
{
    return Name;
}

string User::getPassword()
{
    return Password;
}

string User::getBirthday()
{
    return Birthday;
}

//adds a wallpost to the User's wall (a linkedlist)
void User::setUserwall(wallpost input)
{
    Userwall.setWallpost(input);
}

//removes a wallpost from the User's wall
void User::removeUserwall()
{
    Userwall.removeWallpost();
}

void User::addfriend(string input)
{
    friends.set(index, input);
    index++;
}

void User::unfriend()
{
    friends.remove(index);
    index--;
}

//write user's name,pw,bday,wallposts to a string
string User::writeUser()
{
    string output;
    
    //add in user info
    output += Name;
    output += "|";
    output += Password;
    output += "|";
    output += Birthday;
    output += "|";
    
    //delimiter for userinfo
    output += "&";
    
    //add in user wallposts
    output += Userwall.writeWall();
    
    //add in friends list
    for (int i = 0; i < friends.getlength(); i++)
    {
        string temp = friends.get(i);
        
        output += temp;
        
        //delimiter for EACH friend
        output += "~";
    }
    
    //delimiter for friends list
    output += "$";
    
    return output;
}

//reading in user name,pw,bday,wallposts from a string
void User::readUser(string input)
{
    stringstream mainstream(input);
    
    //get user info
    string userinfo;
    getline(mainstream, userinfo, '&');
    mainstream.get();
    
    stringstream stream(userinfo);
    getline(stream, Name,'|');
    getline(stream, Password,'|');
    getline(stream, Birthday,'|');
    
    //gets wallposts
    string wall;
    getline(mainstream, wall, '#');
    wall += mainstream.get();
    Userwall.readWall(wall);
    
    //gets friendslist
    string friendlist;
    getline(mainstream, friendlist, '$');
    mainstream.get();
    
    //parse friends into list "friends"
    stringstream stream2(friendlist);
    while (!stream2.eof())
    {
        //get each friend
        string onefriend;
        getline(stream2, onefriend, '~');
        stream2.get();
        
        //add to list
        friends.set(index, onefriend);
    }
}







