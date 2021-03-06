//
//  WallPost.cpp
//  HW6
//
//  Created by Raymond Dam on 10/27/13.
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
void wallpost::newPost(string input)
{
    post = input;
}

void wallpost::newAuthor(string input)
{
    author = input;
}

void wallpost::newDate(string input)
{
    date = input;
}

//getter functions
string wallpost::getPost()
{
    return post;
}

string wallpost::getAuthor()
{
    return author;
}

string wallpost::getDate()
{
    return date;
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
