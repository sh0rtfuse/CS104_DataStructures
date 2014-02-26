//
//  UserList.h
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef USERLIST_H
#define USERLIST_H

#include <iostream>
#include <list>
#include "User.h"

class UserList
{
public:
    UserList();
    ~UserList();
    
    void addUser(User input);
    void UpdateUser(User input);
    
    User getUser(string name);
    
    void writeDatabase();
    void readDatabase();
    
    std::string DatabaseSearch(std::string name);
    void sendFriendRequest(std::string name);
    
private:
    std::list<User> UserDatabase;
};

#endif
