//
//  HW1_4b.cpp
//  Homework 1
//
//  Raymond Dam
//  
//


#include <iostream>
#include <fstream>                          //file io stuff
#include <cstring>                          //using strings
#include <sstream>
#include <stdlib.h>                         //atoi to convert string to int
#include <ctime>                            //for timing

using namespace std;

//***function prototypes & global variables***//
int recursion (int n, int &m);
void fileio (string inputfile, int n);
int *a;
//********************************************//

int main ()
{
    int n = 0;                              // number of elements in the array a
    int m = 0;                              // we’ll use this for the maximum
    string inputfile;                       // holds name of the input file

    
    //ask user how many elements there are in the array
    cout << endl;
    cout << "How many numbers are in your dataset?" << endl;
    cout << "User Entry: ";
    cin >> n;
    
    //ask user to enter name of input file
    cout << endl;
    cout << "Please the name of your input file." << endl;
    cout << "User Entry: ";
    cin >> inputfile;
    
    //dynamically allocate an array based on user entry to pointer, a
    a = new int [n];
    
    //call fileio function
    fileio(inputfile, n);
    
    //subtract by one so we stay within the array when we do recursion
    n -= 1;
    
    //***start the clock!!***//
    clock_t start, finish;
    
    double dur;
    
    start = clock();
    //***********************//
    
    //call recursive function find largest number
    recursion(n, m);
    
    /*
     
    //for loop method
    m = a[0];
    for (int i = 1; i < n; i ++)
    {
        if (a[i] > m)
        {
            m = a[i];
        }
        // This is the end of the loop.
    }

    */
    
    //***stop the clock!!***//
    finish = clock();
    
    dur = (double)(finish - start);
    
    dur /= CLOCKS_PER_SEC;
    
    cout << "Elapsed seconds: " << scientific << dur << endl;
    //**********************//
    
    cout << m << endl;
    
    //release dynamically allocated memory
    delete [] a;
    
    return 0;
}

int recursion (int n, int &m)
{
    if (n == 0)
    {
        if (a[n] > m)               //just in case a[0] is the largest value
        {
            m = a[n];
        }
        
        return m;
    }
    
    else
    {
        if (a[n] > m)
        {
            m = a[n];
        }
        
        return recursion(n-1, m);
    }
}

//reads in a file with a list of numbers and stores the dataset in the array
void fileio (string inputfile, int n)
{
    ifstream filein(inputfile.c_str());
    
    //if and else statements for input validation of the user file
    if (!filein)
    {
        cout << endl;
        cout << "Invalid file. Please check the name and location of your file and try again." << endl;
        cout << endl;
        cout << "----------------------------------------------------------------------------" << endl;
    }
    
    else
    {
        for (int i = 0; i < n; i++)
        {
            int temp;
            
            //parses file for data
            filein >> temp;
            
            //store data in array
            a[i] = temp;
        }
    }
    
    filein.close();
}







