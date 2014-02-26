//
//  Wall.h
//  HW6
//
//  Created by Raymond Dam on 10/27/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef WALL_H
#define WALL_H

#include <iostream>
#include "List.h"
#include "WallPost.h"

class wall
{
    public:
        wall ();
        ~wall ();
    
        void setWallpost(wallpost input);
        void removeWallpost();
    
        std::string writeWall();
        void readWall(std::string input);
    
    private:
        List <wallpost> theWall;
        int index;
};

#endif