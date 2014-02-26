//
//  Q5.cpp
//  HW9
//
//  Created by Raymond Dam on 11/20/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include "23tree.h"

using namespace std;

void menu(TwoThreeTree<string, float> Tree)
{
    int input = 0;
    
    do
    {
        cout << endl;
        cout << "Menu (Enter the number)" << endl;
        cout << "1. Add Person." << endl;
        cout << "2. Remove Person." << endl;
        cout << "3. Search for Person." << endl;
        cout << "4. Exit. " << endl;
        cout << "User Entry: ";
        cin >> input;
        cout << endl;
    }
    while ((input != 1) && (input != 2) && (input != 3) && (input != 4));
    
    if (input == 1)
    {
        string name;
        float GPA = 0;
        
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter GPA: ";
        cin >> GPA;
        
        Tree.add(name, GPA);
        
        menu(Tree);
    }
    
    if (input == 2)
    {
        string name;
        
        cout << "Enter Name: ";
        cin >> name;
        
        Tree.remove(name);
        
        menu(Tree);
    }
    
    if (input == 3)
    {
        string name;
        
        cout << "Enter Name: ";
        cin >> name;
        
        float GPA = 0;
        GPA = Tree.get(name);
        
        if (GPA == 0)
        {
            cout << endl;
            cout << "Person does not exist." << endl;
        }
        
        else
        {
            cout <<endl;
            cout << name << "'s GPA is " << GPA << endl;
        }
        
        menu(Tree);
    }
    
    if (input == 4)
    {
        //exit
    }
}

int main()
{
    TwoThreeTree<string, float> Tree;
    
    menu(Tree);
    
    return 0;
}
