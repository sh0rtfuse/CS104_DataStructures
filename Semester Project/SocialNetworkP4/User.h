//
//  User.h
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include <list>
#include "Wall.h"
#include "WallPost.h"

class User
{
public:
    User();
    ~User();
    
    void setUsername(std::string input);
    void setName(std::string input);
    void setPassword(std::string input);
    void setBirthday(std::string input);
    
    std::string getUsername();
    std::string getName();
    std::string getPassword();
    std::string getBirthday();
    
    void setUserwall(wallpost input);
    wall getUserwall();
    void removeUserwall(std::string input);
    
    void addfriend(std::string input);
    void unfriend (std::string input);
    std::string getfriends();
    
    std::list<string> FriendsList();
    
    void setpendingfriend(std::string input);
    void removependingfriend(std::string input);
    std::string getpendingfriends();
    
    std::list<string> PendingFriendsList();
    
    std::string writeUser();
    void readUser (std::string input);
    
    bool empty();
    
private:
    std::string Username;
    std::string Name;
    std::string Password;
    std::string Birthday;
    
    std::list<std::string> friends;
    std::list<std::string> pendingfriends;
    
    wall Userwall;
};

#endif
