//
//  UserList.h
//  HW6
//
//  Created by Raymond Dam on 10/29/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef USERLIST_H
#define USERLIST_H

#include <iostream>
#include "List.h"
#include "User.h"

class UserList
{
    public:
        UserList();
        ~UserList();
    
        void addUser(User input);
        void removeUser();
    
        User getUser();
    
        void writeDatabase();
        void readDatabase();
    
        std::string friendfinder(std::string input);
    
    private:
        List<User> UserDatabase;
        int index;
};

#endif
