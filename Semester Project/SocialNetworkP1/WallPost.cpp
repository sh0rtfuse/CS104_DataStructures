//
//  WallPost.cpp
//  Social Network
//
//  Created by Raymond Dam on 9/22/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "WallPost.h"

#include <iostream>

using namespace std;

wallpost::wallpost ()
{
    post = author = date = " ";
}

wallpost::~wallpost ()
{
    //delete stuff
}

//setter functions
void wallpost::newpost(string input)
{
    post = input;
}

void wallpost::newauthor(string input)
{
    author = input;
}

void wallpost::newdate(string input)
{
    date = input;
}

//prints out entire post in one string
void wallpost::printpost(string output)
{
    output += author;
    output += " ";
    output += date;
    output += " ";
    output += "'";
    output += post;
    output += "'";
}
