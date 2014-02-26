//
//  User.h
//  HW6
//
//  Created by Raymond Dam on 10/29/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include "Wall.h"
#include "WallPost.h"
#include "List.h"

class User
{
    public:
        User();
        ~User();
    
        void setName(std::string input);
        void setPassword(std::string input);
        void setBirthday(std::string input);
    
        std::string getName();
        std::string getPassword();
        std::string getBirthday();
    
        void setUserwall(wallpost input);
        void removeUserwall();
    
        void addfriend(std::string input);
        void unfriend ();
    
        std::string writeUser();
        void readUser (std::string input);
    
    private:
        std::string Name;
        std::string Password;
        std::string Birthday;
    
        List<std::string> friends;
        int index;
    
        wall Userwall;
};

#endif

