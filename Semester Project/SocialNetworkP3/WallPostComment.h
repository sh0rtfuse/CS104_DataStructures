//
//  WallPostComment.h
//  HW8
//
//  Created by Raymond Dam on 11/10/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#ifndef WALLPOSTCOMMENT_H
#define WALLPOSTCOMMENT_H

#include <iostream>

using namespace std;

class wallpostcomment
{
    public:
        wallpostcomment();
        ~wallpostcomment();
    
        void setCommentPost(string input);
        void setAuthor(string input);
    
        void setTime();
        void newTime(string input);
    
        string getComment();
        string getAuthor();
        string getTime();
    
        void setOrder(int input);
        int getOrder();
    
    private:
        string comment;
        string author;
        string time;
    
        int order;
};

#endif
