//
//  WallPost.cpp
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "WallPost.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <list>

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

//sets date via string (for saving purposes)
void wallpost::newDate(string input)
{
    date = input;
}

//set time via string (for saving purposes)
void wallpost::newTime(string input)
{
    time = input;
}

//sets data and time automatically: for new posts during runtime
void wallpost::setDateandTime()
{
    using std::chrono::system_clock;
    
    system_clock::time_point now = system_clock::now();
    
    std::time_t t;
    
    t = system_clock::to_time_t(now);
    
    string temp = ctime(&t);
    
    //removes the null problem
    temp.pop_back();
    
    date = temp;
    
    //stores the # of seconds since Jan. 1 1970 for sorting
    int seconds = t;
    
    stringstream stream;
    stream << seconds;
    string secondsconv = stream.str();
    
    time = secondsconv;
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

string wallpost::getTime()
{
    return time;
}

//implementations supporting comments
void wallpost::setComment(wallpostcomment input)
{
    comments.push_front(input);
}

list<wallpostcomment> wallpost::getComments()
{
    return comments;
}

void wallpost::removeComment(string input)
{
    for (std::list<wallpostcomment>::iterator comments_iter = comments.begin(); comments_iter != comments.end(); comments_iter++)
    {
        wallpostcomment temp = *comments_iter;
        
        if (temp.getAuthor() == input)
        {
            comments.erase(comments_iter);
        }
    }
}

string wallpost::writecomments()
{
    string output;
    
    //cycles through the linkedlist to print the comments onto a string
    for (std::list<wallpostcomment>::iterator comments_iter = comments.begin(); comments_iter != comments.end(); comments_iter++)
    {
        wallpostcomment temp = *comments_iter;
        
        output += temp.getComment();
        output += "|";
        output += temp.getAuthor();
        output += "|";
        output += temp.getTime();
        output += "|";
    }
    
    //delimiter at the end of comments
    output += "`";
    
    return output;
}

//grabs properly-formatted string and parse it into comments, then
//store each comment into a comments list
void wallpost::readcomments(string input)
{
    stringstream stream(input);
    
    while (!stream.eof())
    {
        wallpostcomment temp;
        string tempComment, tempAuthor, tempTime;
        
        getline(stream, tempComment,'|');
        getline(stream, tempAuthor,'|');
        getline(stream, tempTime, '|');
        
        temp.setCommentPost(tempComment);
        temp.setAuthor(tempAuthor);
        temp.newTime(tempTime);
        
        comments.push_front(temp);
    }
}

//prints out entire post in one string
void wallpost::printpost(string output)
{
    output += post;
    output += "|";
    output += author;
    output += "|";
    output += date;
    output += "|";
    output += time;
    output += "|";
}

//Order lets me keep track of the sorting order across 2 lists
void wallpost::setOrder(int input)
{
    order = input;
}

int wallpost::getOrder()
{
    return order;
}







