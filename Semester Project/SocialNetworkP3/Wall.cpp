//
//  Wall.cpp
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "Wall.h"

#include "Wall.h"
#include <sstream>
#include <list>

using namespace std;

wall::wall()
{
    
}

wall::~wall()
{
    
}

void wall::setWallpost(wallpost input)
{
    theWall.push_front(input);
}

//search through the wall and remove most by input author
void wall::removeWallpost(string input)
{
    for (std::list<wallpost>::iterator theWall_iter = theWall.begin(); theWall_iter != theWall.end(); theWall_iter++)
    {
        wallpost temp = *theWall_iter;
        
        if (temp.getAuthor() == input)
        {
            theWall.erase(theWall_iter);
        }
    }
}

std::list<wallpost> wall::gettheWall()
{
    return theWall;
}

std::string wall::writeWall()
{
    std::string output;
    
    //cycles through the linkedlist to print the wall onto a string
    for (std::list<wallpost>::iterator theWall_iter = theWall.begin(); theWall_iter != theWall.end(); theWall_iter++)
    {
        wallpost temp = *theWall_iter;
        
        output += temp.getPost();
        output += "|";
        output += temp.getAuthor();
        output += "|";
        output += temp.getDate();
        output += "|";
        output += temp.getTime();
        output += "|";
        
        //delimiter for EACH wallpost
        output += "_";
        
        //add in the comments
        output += temp.writecomments();
    }
    
    //delimiter at the end of wall
    output += "~";
    
    return output;
}

//grabs properly-formatted string and parse it into wallposts, then
//store each wallposts into a wall linkedlist
void wall::readWall(std::string input)
{
    std::stringstream stream(input);
    
    //grabs the entire wall first
    std::string wall;
    getline(stream, wall, '~');
    //stream.get();
    
    std::stringstream stream2(wall);
    
    while (!stream2.eof())
    {
        //grabs one wallpost within the wall
        std::string Onewallpost;
        getline(stream2, Onewallpost, '_');
        
        //stores that wallpost into list
        stringstream stream3(Onewallpost);
        
        wallpost temp;
        std::string tempPost, tempAuthor, tempDate, tempTime;
        
        getline(stream3, tempPost,'|');
        getline(stream3, tempAuthor,'|');
        getline(stream3, tempDate,'|');
        getline(stream3, tempTime,'|');
        
        temp.newPost(tempPost);
        temp.newAuthor(tempAuthor);
        temp.newDate(tempDate);
        temp.newTime(tempTime);
        
        //grabs all the comments of the one wallpost
        string allcomments;
        getline(stream2, allcomments, '`');
        
        //call function to process comments
        temp.readcomments(allcomments);
        
        //push everything to the list
        theWall.push_front(temp);
    }
}





