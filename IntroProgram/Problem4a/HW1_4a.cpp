//
//  HW1_4a.cpp
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
int recursion (int n, int &sum);
void fileio (string inputfile, int n);
int *a;
//********************************************//

int main ()
{
    int n;                                  // number of elements in the array a
    int sum = 0;                            // we’ll use this for adding numbers
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
    
    /*
    //for loop method
    sum = 0;
    for (int i = 0; i < n; i ++)
    {
        sum += a[i];
    }
    */
    
    //call recursion function to sum up array
    recursion(n, sum);
    
    //***stop the clock!!***//
    finish = clock();
    
    dur = (double)(finish - start);
    
    dur /= CLOCKS_PER_SEC;
    
    cout << "Elapsed seconds: " << scientific << dur << endl;
    //**********************//
    
    cout << endl;
    cout << sum << endl;
    
    //release dynamically allocated memory
    delete [] a;
    
    return 0;
}

//recursive algorithm that sums the array
int recursion (int n, int &sum)
{
    if (n == 0)
    {
        sum += a[n];        //a[0] is still storing a value
        
        return sum;
    }
    
    else
    {
        sum += a[n];
        
        return recursion (n-1, sum);
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






