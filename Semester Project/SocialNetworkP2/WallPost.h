//
//  WallPost.h
//  HW6
//
//  Created by Raymond Dam on 10/27/13.
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

        void newPost (string input);
        void newAuthor (string input);
        void newDate (string input);
    
        string getPost();
        string getAuthor();
        string getDate();
    
        void printpost (string output);
    
    private:
        string post;
        string author;
        string date;
    
};

#endif
