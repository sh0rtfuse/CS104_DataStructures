//
//  WallPost.h
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef WALLPOST_H
#define WALLPOST_H

#include <iostream>

using namespace std;

class wallpost
{
    public:
        wallpost ();
        ~wallpost ();
    
        void newpost (string input);
        void newauthor (string input);
        void newdate (string input);
    
        void printpost (string output);
    
    private:
        string post;
        string author;
        string date;
    
};

//#include "WallPost.cpp"

#endif
