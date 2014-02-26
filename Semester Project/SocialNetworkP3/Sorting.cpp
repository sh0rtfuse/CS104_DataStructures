//
//  Sorting.cpp
//  HW8
//
//  Created by Raymond Dam on 11/9/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include "Sorting.h"
#include "WallPostComment.h"

#include <string>
#include <list>
#include <sstream>


Sort::Sort(User name, bool SortAll)
{
    //sorting preferences
    if (SortAll == true)
    {
        ByWpostsandComments(name);
    }
    
    else if (SortAll == false)
    {
        ByWallposts(name);
    }
    
    //put processed list into dynamic array
    arrayptr = new int[PostTimes.size()];
    arraysize = 0;
    
    for (std::list<int>::iterator PostTimes_iter = PostTimes.begin(); PostTimes_iter != PostTimes.end(); PostTimes_iter++)
    {
        int element = *PostTimes_iter;
        
        arrayptr[arraysize] = element;
        arraysize++;
    }
    
    //call sorting function
    HeapSort(arrayptr,arraysize);
    
    //Save Sorting Preference & User
    SortPref = SortAll;
    SortUser = name;
}

Sort::~Sort()
{
    arrayptr = NULL;
    delete [] arrayptr;
}

//gets user's wall and interates thru list of wallposts for the time each post was made
void Sort::ByWallposts(User name)
{
    std::list<wallpost> temp = name.getUserwall().gettheWall();
    
    for (std::list<wallpost>::iterator temp_iter = temp.begin(); temp_iter != temp.end(); temp_iter++)
    {
        wallpost temp2 = *temp_iter;
        
        string temp3 = temp2.getTime();
        
        if (!temp3.empty())
        {
            int temp4 = std::stoi(temp3);
            
            PostTimes.push_front(temp4);
        }
    }
}

//gets user's wall and each wall's comments
void Sort::ByWpostsandComments(User name)
{
    std::list<wallpost> temp = name.getUserwall().gettheWall();
    
    for (std::list<wallpost>::iterator temp_iter = temp.begin(); temp_iter != temp.end(); temp_iter++)
    {
        wallpost temp2 = *temp_iter;
        
        //get wallpost times
        string temp3 = temp2.getTime();
        if (!temp3.empty())
        {
            int temp4 = std::stoi(temp3);
            
            PostTimes.push_front(temp4);
        }
        
        //get comment times
        std::list<wallpostcomment> temp4 = temp2.getComments();
        for (std::list<wallpostcomment>::iterator temp4_iter = temp4.begin(); temp4_iter != temp4.end(); temp4_iter++)
        {
            wallpostcomment temp5 = *temp4_iter;
            
            string temp6 = temp5.getTime();
            if(!temp6.empty())
            {
                int temp7 = std::stoi(temp6);
                
                PostTimes.push_front(temp7);
            }
        }
    }
}

//swaps the last element with the first element in the array
void Sort::HeapSort(int *arrayptr, int size)
{
    for(int i = size-1; i >= 1; i--)
    {
        int temp = arrayptr[i];
        
        arrayptr[i] = arrayptr[0];
        
        arrayptr[0] = temp;
        
        //calls heap (trickledown) function
        Heap(arrayptr,i);
    }
    
    arrayptr = NULL;
    delete [] arrayptr;
}

//turns list into a binary tree conforming to the heap property
//maintains heap property by comparing parent to children
//and swaping if the child is larger, we do this until
//child is not larger or the node becomes a leaf
void Sort::Heap(int *arrayptr, int size)
{
    //turn array into a heap
    for (int i = 1; i < size; i++)
    {
        int element = arrayptr[i];
        int parent = (i-1)/2;
        int trickle = i;
        
        while(trickle > 0 && arrayptr[parent] < element)
        {
            arrayptr[trickle] = arrayptr[parent];
            trickle = parent;
            parent = (trickle-1)/2;
        }
        
        arrayptr[trickle] = element;
    }
    
    arrayptr = NULL;
    delete [] arrayptr;
}

//uses PostTimes list to grab posts in desired order
std::list<wallpost> Sort::OrderedResults()
{
    std::list<wallpost> Output;
    int order = 0;
    
    //if we sorted both wallposts and comments
    if (SortPref == true)
    {
        for (int i = arraysize-1; i >= 0; i--)
        {
            int latestpost = arrayptr[i];
            
            //get user's wall and iterate through to grab wallposts and comments;
            std::list<wallpost> tempWall = SortUser.getUserwall().gettheWall();
            
            for (std::list<wallpost>::iterator tempWall_iter = tempWall.begin(); tempWall_iter != tempWall.end(); tempWall_iter++)
            {
                wallpost tempWallPost = *tempWall_iter;
                int currentpost = 0;
                wallpost input;
                
                //grab wallpost if it fits the sorted order and add to list
                string temp = tempWallPost.getTime();
                if (!temp.empty())
                {
                    currentpost = std::stoi(temp);
                }

                if (latestpost == currentpost)
                {
                    string post, author, date, time;
                    
                    post = tempWallPost.getPost();
                    author = tempWallPost.getAuthor();
                    date = tempWallPost.getDate();
                    time = tempWallPost.getTime();
                    
                    input.newPost(post);
                    input.newAuthor(author);
                    input.newDate(date);
                    input.newTime(time);
                    
                    //tracking 2 lists
                    input.setOrder(order);
                    order++;
                    
                    Output.push_back(input);
                }
                
                //grab comment and interate through to check if it fits the sorted order and add to list
                std::list <wallpostcomment> currentcomment = tempWallPost.getComments();
                
                for (std::list<wallpostcomment>::iterator tempComment_iter = currentcomment.begin(); tempComment_iter != currentcomment.end(); tempComment_iter++)
                {
                    wallpostcomment comment = *tempComment_iter;
                    int CommentTime = 0;
                    
                    string temp2 = comment.getTime();
                    if (!temp2.empty())
                    {
                        CommentTime = std::stoi(temp2);
                    }
                    
                    if (latestpost == CommentTime)
                    {
                        wallpostcomment inputComment;
                        string post, author, time;
                        
                        post = comment.getComment();
                        author = comment.getAuthor();
                        time = comment.getTime();
                        
                        inputComment.setCommentPost(post);
                        inputComment.setAuthor(post);
                        inputComment.newTime(time);
                        
                        //tracking 2 lists
                        inputComment.setOrder(order);
                        order++;
                        
                        input.setComment(inputComment);
                        
                        Output.push_back(input);
                    }
                }
            }
        }
    }
    
    //if we sorted wallposts only
    if (SortPref == false)
    {
        for (int i = arraysize-1; i >= 0; i--)
        {
            int latestpost = arrayptr[i];
            
            //get user's wall and iterate through to grab wallposts and comments;
            std::list<wallpost> tempWall = SortUser.getUserwall().gettheWall();
            
            for (std::list<wallpost>::iterator tempWall_iter = tempWall.begin(); tempWall_iter != tempWall.end(); tempWall_iter++)
            {
                wallpost tempWallPost = *tempWall_iter;
                int currentpost = 0;
                wallpost input;
                
                //grab wallpost if it fits the sorted order and add to list
                string temp = tempWallPost.getTime();
                if (!temp.empty())
                {
                    currentpost = std::stoi(temp);
                }

                if (latestpost == currentpost)
                {
                    string post, author, date, time;
                    
                    post = tempWallPost.getPost();
                    author = tempWallPost.getAuthor();
                    date = tempWallPost.getDate();
                    time = tempWallPost.getTime();
                    
                    input.newPost(post);
                    input.newAuthor(author);
                    input.newDate(date);
                    input.newTime(time);
                    
                    Output.push_back(input);
                }
            }
        }
    }
    
    return Output;
}


















