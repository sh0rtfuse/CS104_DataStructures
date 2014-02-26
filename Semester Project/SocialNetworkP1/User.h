//
//  User.h
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef USER_H
#define USER_H

#include <iostream>
#include "Wall.h"

using namespace std;

class user
{
    public:
        user ();
        ~user ();
    
        void editname (string input);
        void editpassword (string input);
        void editbirthday (string input);
    
        void posttowall(string post, string date);
        void deletefromwall (string posttodelete);
    
        void printuserinfo (string output);
    
        void readinuserdata (string input);
    
    private:
        string name;
        string password;
        string birthday;
    
        wall userwall;
};

//#include "User.cpp"

#endif
