//
//  User.cpp
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
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

wall User::getUserwall()
{
    return Userwall;
}

//removes a wallpost from the User's wall
void User::removeUserwall(string input)
{
    Userwall.removeWallpost(input);
}

void User::addfriend(string input)
{
    friends.push_front(input);
}

void User::unfriend(string input)
{
    //finds the friend and removes them
    for (std::list<std::string>::iterator friends_iter = friends.begin(); friends_iter != friends.end(); friends_iter++)
    {
        string temp = *friends_iter;
        
        if (temp == input)
        {
            friends.erase(friends_iter);
        }
    }
}

//returns a string of entire friends list
string User::getfriends()
{
    string output;
    
    for (std::list<std::string>::iterator friends_iter = friends.begin(); friends_iter != friends.end(); friends_iter++)
    {
        string temp = *friends_iter;
        
        output += temp;
        output += "|";
    }
    
    return output;
}

void User::setpendingfriend(string input)
{
    pendingfriends.push_front(input);
}

void User::removependingfriend(string input)
{
    for (std::list<std::string>::iterator pendingfriends_iter = pendingfriends.begin(); pendingfriends_iter != pendingfriends.end(); pendingfriends_iter++)
    {
        string temp = *pendingfriends_iter;
        
        if (temp == input)
        {
            friends.erase(pendingfriends_iter);
        }
    }
}

string User::getpendingfriends()
{
    string output;
    
    for (std::list<std::string>::iterator pendingfriends_iter = pendingfriends.begin(); pendingfriends_iter != pendingfriends.end(); pendingfriends_iter++)
    {
        string temp = *pendingfriends_iter;
        
        output += temp;
        output += "|";
    }
    
    return output;
}

std::list<string> User::FriendsList()
{
    return friends;
}

std::list<string> User::PendingFriendsList()
{
    return pendingfriends;
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
    output += "*";
    
    //add in user wallposts
    output += Userwall.writeWall();
    
    //add in friends list
    for (std::list<std::string>::iterator friends_iter = friends.begin(); friends_iter != friends.end(); friends_iter++)
    {
        string temp = *friends_iter;
        
        output += temp;
        output += "|";
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
    getline(mainstream, userinfo, '*');
    //mainstream.get();
    
    stringstream stream(userinfo);
    getline(stream, Name,'|');
    getline(stream, Password,'|');
    getline(stream, Birthday,'|');
    
    //gets wallposts
    string wall;
    getline(mainstream, wall, '~');
    //wall += mainstream.get();
    Userwall.readWall(wall);
    
    //gets friendslist
    string friendlist;
    getline(mainstream, friendlist, '$');
    //mainstream.get();
    
    //parse friends into list "friends"
    stringstream stream2(friendlist);
    while (!stream2.eof())
    {
        //get each friend
        string onefriend;
        getline(stream2, onefriend, '|');
        //stream2.get();
        
        //add to list
        friends.push_front(onefriend);
    }
}
