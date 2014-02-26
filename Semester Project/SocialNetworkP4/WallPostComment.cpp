//
//  WallPostComment.cpp
//  HW8
//
//  Created by Raymond Dam on 11/10/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "WallPostComment.h"

#include <chrono>
#include <ctime>
#include <sstream>

using namespace std;

wallpostcomment::wallpostcomment()
{
    comment = author = time = " ";
}

wallpostcomment::~wallpostcomment()
{
    
}

void wallpostcomment::setCommentPost(string input)
{
    comment = input;
}

void wallpostcomment::setAuthor(string input)
{
    author = input;
}

//automatically set the time
void wallpostcomment::setTime()
{
    using std::chrono::system_clock;
    
    system_clock::time_point now = system_clock::now();
    
    std::time_t t;
    
    t = system_clock::to_time_t(now);
    
    //stores the # of seconds since Jan. 1 1970 for sorting
    int seconds = t;
    
    stringstream stream;
    stream << seconds;
    string secondsconv = stream.str();
    
    time = secondsconv;
}

//takes in a time for saving purposes
void wallpostcomment::newTime(string input)
{
    time = input;
}

string wallpostcomment::getComment()
{
    return comment;
}

string wallpostcomment::getAuthor()
{
    return author;
}

string wallpostcomment::getTime()
{
    return time;
}


//Order lets me keep track of the sorting order across 2 lists
void wallpostcomment::setOrder(int input)
{
    order = input;
}

int wallpostcomment::getOrder()
{
    return order;
}

bool wallpostcomment::empty()
{
    if (comment.empty() || author.empty() || time.empty())
    {
        return true;
    }
    
    else
    {
        return false;
    }
}


