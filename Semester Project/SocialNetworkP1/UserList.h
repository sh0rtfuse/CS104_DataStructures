//
//  UserList.h
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef USERLIST_H
#define USERLIST_H

#include <iostream>
#include "LinkedListTemplate.h"

class userlist
{
    public:
        userlist ();
        ~userlist ();
    
        void adduser (string name, string password, string birthday);
        void deleteuser (string user);
    
        bool usersearch (string query);
    
        void printall ();
        void loadall (string input);
    
    private:
        LinkedList<string> thelist;
};

//#include "UserList.cpp"

#endif
