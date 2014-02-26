//
//  Q6.cpp
//  HW10
//
//  Created by Raymond Dam on 11/28/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstddef>
#include <stack>
#include <ctime>

#include "HashTable.h"

using namespace std;

class HashFunction
{
public:
    HashFunction();
    int Hash(string name);
};

HashFunction::HashFunction()
{
    
}

//My hash function takes the string, converts each char into its ASCII code,
//and finds the sum for use as the hash key
int HashFunction::Hash(string name)
{
    int output = 0;
    
    for (int i = 0; i < name.length(); i++)
    {
        char letter = name.at(i);
        output += int(letter);
    }
    
    return output;
}

//Hash Table is a global variable
hashtable<int, string> Table(200000);

void fileio()
{
    string filename;
    int n;
    
    cout << endl;
    cout << "Please enter the name of your file." << endl;
    cout << "User Entry: ";
    cin >> filename;
    
    cout << endl;
    cout << "Processing file..." << endl;
    
    //***start clock***//
    clock_t start, finish;
    double dur;
    start = clock();
    //*****************//
    
    ifstream filein;
    filein.open(filename);
    
    //grab n number of lines
    string nlines;
    getline(filein, nlines, ' ');
    n = atoi(nlines.c_str());
    
    //grab each line, process for words, and map to hashtable
    while (!filein.eof())
    {
        string line;
        getline(filein, line);
        
        stringstream stream(line);
        while (!stream.eof())
        {
            string word;
            getline(stream, word, ' ');
            
            //accounts for more than one white space by looking for first letter
            size_t letter = word.find_first_of("abcdefghijklmnopqrstuvwxyz");
            
            //create a sub-string to remove the extra spaces
            string substring =  word.substr(letter, word.npos);
            
            //hash the substring, then add its corresponding line to the table
            HashFunction H;
            int HashKey = H.Hash(substring);
            Table.add(HashKey, line);
        }
    }
    
    cout << "Processing Complete." << endl;
    
    //***stop clock***//
    finish = clock();
    dur = (double)(finish - start);
    dur /= CLOCKS_PER_SEC;
    cout << "Elapsed seconds: " << scientific << dur << endl;
    //****************//
}

void menu()
{
    int input = 0;
    
    do
    {
        cout << endl;
        cout << "Menu (Enter the number)" << endl;
        cout << "1. Search." << endl;
        cout << "2. Exit. " << endl;
        cout << "User Entry: ";
        cin >> input;
        cout << endl;
    }
    while ((input != 1) && (input != 2));
    
    if (input == 1)
    {
        string query;
        int num_of_results = 0;
        
        cout << "Enter your single-word query: ";
        cin >> query;
        
        //***start clock***//
        clock_t start, finish;
        double dur;
        start = clock();
        //*****************//
        
        //hash query
        HashFunction H;
        int HashKey = H.Hash(query);
        
        stack<string> result;
        result = Table.get2(HashKey);
        
        //print out results
        cout << "Result(s): " << endl;
        
        while (!result.empty())
        {
            cout << "   " << result.top() << endl;
            result.pop();
            num_of_results++;
        }
        
        cout << "********************" << endl;
        cout << num_of_results << " Results." << endl;
        
        //***stop clock***//
        finish = clock();
        dur = (double)(finish - start);
        dur /= CLOCKS_PER_SEC;
        cout << "Search Time: " << scientific << dur << endl;
        //****************//
        
        menu();
    }
    
    if (input == 2)
    {
        
    }
}

int main()
{
    fileio();
    
    menu();
    
    return 0;
}





