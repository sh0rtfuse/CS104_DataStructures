//
//  Q3.cpp
//  HW10
//
//  Created by Raymond Dam on 11/26/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <string>

#include "HashTable.h"

using namespace std;

class StudentName
{
    public:
        StudentName();
        int Hash(string name);
};

StudentName::StudentName()
{
    
}

//My hash function takes the string, converts each char into its ASCII code,
//and finds the sum for use as the hash key
int StudentName::Hash(string name)
{
    int output = 0;
    
    for (int i = 0; i < name.length(); i++)
    {
        char letter = name.at(i);
        output += int(letter);
    }
    
    return output;
}

void menu(hashtable<int, float> Hash)
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
        
        StudentName Student;
        int hashkey = Student.Hash(name);
        
        Hash.add(hashkey, GPA);
        
        menu(Hash);
    }
    
    if (input == 2)
    {
        string name;
        
        cout << "Enter Name: ";
        cin >> name;
        
        StudentName Student;
        int hashkey = Student.Hash(name);
        
        Hash.remove(hashkey);
        
        menu(Hash);
    }
    
    if (input == 3)
    {
        string name;
        int hashkey = 0;
        
        cout << "Enter Name: ";
        cin >> name;
        
        StudentName Student;
        hashkey = Student.Hash(name);
        
        float GPA = Hash.get(hashkey);
        
        if (hashkey == 0)
        {
            cout << endl;
            cout << "Person does not exist." << endl;
        }
        
        else
        {
            cout <<endl;
            cout << name << "'s GPA is " << GPA << endl;
        }
        
        menu(Hash);
    }
    
    if (input == 4)
    {
        //exit
    }
}

int main()
{
    hashtable<int, float> Hash(100);
    
    menu(Hash);
    
    return 0;
}
