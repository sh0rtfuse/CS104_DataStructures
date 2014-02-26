//
//  Sorting.h
//  HW8
//
//  Created by Raymond Dam on 11/9/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <list>

#include "User.h"
#include "Wall.h"
#include "WallPost.h"

/*
 This class handles data formating of wallposts/comments
 and sorts using a custom implementation of heap sort.
*/

class Sort
{
    public:
        Sort(User name, bool SortAll);
        ~Sort();
    
        std::list<wallpost> OrderedResults();
    
    private:
        std::list<int> PostTimes;
        int *arrayptr;
        int arraysize;
    
        bool SortPref;
        User SortUser;
    
        void HeapSort(int *arrayptr, int size);
        void Heap(int *arrayptr, int size);
    
        void swapWallpost();
        void swapComments();
    
        void ByWallposts(User name);             //extracts only wallpost times
        void ByWpostsandComments(User name);     //exacts wallpost and comment times
};

#endif
