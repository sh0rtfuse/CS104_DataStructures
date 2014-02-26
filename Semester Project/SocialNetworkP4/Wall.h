//
//  Wall.h
//  HW8
//
//  Created by Raymond Dam on 11/7/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef WALL_H
#define WALL_H

#include <iostream>
#include <list>
#include "WallPost.h"

class wall
{
public:
    wall ();
    ~wall ();
    
    void setWallpost(wallpost input);
    std::list <wallpost> gettheWall();
    void removeWallpost(string input);
    
    std::string writeWall();
    void readWall(std::string input);
    
private:
    std::list <wallpost> theWall;
    
};

#endif
