//
//  Q3.cpp
//  HW9
//
//  Created by Raymond Dam on 11/19/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

/* Methodology
 I used a dynamic array to store the strings and kept track of duplicates.
 As each string is grabbed, my algorithm checks to see if a duplicate has 
 been previously entered. Though I allocate an array equal to the size of 
 the list, I avoid traversing the entire list by using an incrementor to
 track the growing list of strings being added to the array with the idea
 that many duplicates would make the effective size of the array smaller
 than the actual allocated size. So my program tries to be faster at the
 expense of memory.
*/

struct searchtype
{
    string name;
    int count = 0;
};

void fileio()
{
    string filename;
    searchtype *arrayptr;
    int arraysize = 0;  //tracks how much of the array is actually used
    int max = 0;
    
    cout << endl;
    cout << "Please enter the name of your file." << endl;
    cout << "User Entry: ";
    cin >> filename;
    
    ifstream filein;
    filein.open(filename);
    
    //grab n number of lines
    string nstring;
    getline(filein, nstring);
    int n = atoi(nstring.c_str());
        
    //declares a dynamic array to a pointer
    arrayptr = new searchtype [n];
    
    //grab list of string given list length n
    while(!filein.eof())
    {
        //grabs each string line
        string stringi;
        getline(filein, stringi);
        
        //search array: increase count if same string OR add string
        bool newString = true;
            
        for (int i = 0; i <= arraysize; i++)
        {
            if(arrayptr[i].name == stringi)
            {
                //increases counter by 1
                int temp = arrayptr[i].count;
                temp++;
                arrayptr[i].count = temp;
                newString = false;
            }
        }
        
        if (newString == true)
        {
            arrayptr[arraysize].name = stringi;
            int temp = arrayptr[arraysize].count;
            temp++;
            arrayptr[arraysize].count = temp;
            
            //increase effective array use by 1
            arraysize++;
        }
    }
    
    //process array for most freq strings
    for (int i = 0; i < arraysize; i++)
    {
        if (arrayptr[i].count > max)
        {
            max = arrayptr[i].count;
        }
    }
    
    //find a print all string with the max count
    for (int k = 0; k < arraysize; k++)
    {
        if (arrayptr[k].count == max)
        {
            cout << arrayptr[k].name << endl;
        }
    }
    
    arrayptr = NULL;
    delete [] arrayptr;
}

int main()
{
    fileio();
    
    return 0;
}

