//
//  Wall.cpp
//  HW6
//
//  Created by Raymond Dam on 10/27/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "Wall.h"
#include <sstream>

wall::wall()
{
    index = 0;
}

wall::~wall()
{
    
}

void wall::setWallpost(wallpost input)
{
    theWall.set(index, input);
    index++;
}

void wall::removeWallpost()
{
    theWall.remove(index);
    index--;
}

std::string wall::writeWall()
{
    std::string output;
    
    //cycles through the linkedlist to print the wall onto a string
    for (int i = 0; i < theWall.getlength(); i++)
    {
        wallpost temp = theWall.get(index);
        
        output += temp.getPost();
        output += "|";
        output += temp.getAuthor();
        output += "|";
        output += temp.getDate();
        output += "|";
    }
    
    //delimiter at the end of wall
    output += "#";
    
    return output;
}

//grabs properly-formatted string and parse it into wallposts, then
//store each wallposts into a wall linkedlist
void wall::readWall(std::string input)
{
    std::stringstream stream(input);
    
    //grabs the entire wall first
    std::string wall;
    getline(stream, wall, '#');
    stream.get();
    
    std::stringstream stream2(wall);
    
    while (!stream2.eof())
    {
        wallpost temp;
        std::string tempPost, tempAuthor, tempDate;
        
        getline(stream2, tempPost,'|');
        getline(stream2, tempAuthor,'|');
        getline(stream2, tempDate,'|');
        stream2.get();
        
        temp.newPost(tempPost);
        temp.newAuthor(tempAuthor);
        temp.newDate(tempDate);
        
        theWall.set(index, temp);
        index++;
    }
}




