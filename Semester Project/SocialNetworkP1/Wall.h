//
//  Wall.h
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef WALL_H
#define WALL_H

#include <iostream>
#include "LinkedListTemplate.h"

using namespace std;

class wall
{
    public:
        wall ();
        ~wall ();
    
        void addwallpost(string post, string name, string date);
        void removewallpost (string wallpost);
    
        void printwall (string output);
        void readinwall (string input);
    
    private:
        LinkedList<string> thewall;
};

//#include "Wall.cpp"

#endif
