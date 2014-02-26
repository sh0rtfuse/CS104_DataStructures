//
//  WallPost.h
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef WALLPOST_H
#define WALLPOST_H

#include <iostream>
#include <list>
#include <sstream>

#include "WallPostComment.h"

using namespace std;

class wallpost
{
public:
    wallpost ();
    ~wallpost ();
    
    void newPost (string input);
    void newAuthor (string input);
    void newDate (string input);
    void newTime (string input);
    
    void setDateandTime ();
    
    void setComment(wallpostcomment input);
    list<wallpostcomment> getComments();
    void removeComment(string input);
    
    string getPost();
    string getAuthor();
    string getDate();
    
    string getTime();
    
    void readcomments(string input);
    string writecomments();
    
    void printpost (string output);
    
    void setOrder(int input);
    int getOrder();
    
private:
    string post;
    string author;
    string date;
    
    string time;
    
    int order;
    
    list<wallpostcomment> comments;
};

#endif