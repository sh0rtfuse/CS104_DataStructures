//
//  main.cpp
//  HW5
//
//  Created by Raymond Dam on 10/8/13.
//  Copyright (c) 2013 Raymond Dam. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Stack.h"
#include "Vector.h"

using namespace std;

void calculations (Stack<string> MainStack, Stack<string> OperatorStack, int counter, string output)
{
    Stack<string> Mainstack2;
    Stack<string> OperatorStack2;
    
    for (int i = 0; i < counter; i++)
    {
        string temp = MainStack.top();
        Mainstack2.push(temp);
        
        MainStack.pop();
    }
    
    //You'll always have 1 less operator then your number of vectors
    for (int i = 0; i < counter-1; i++)
    {
        string temp2 = OperatorStack.top();
        OperatorStack2.push(temp2);
        
        OperatorStack.pop();
    }
    
    Vector result(counter);
    
    for (int i = 0; i < counter-1; i++)
    {
        string ops = OperatorStack2.top();
        OperatorStack2.pop();
        
        //only for the first operation
        if (i == 0)
        {
            if (ops == "+")
            {
                string temp = Mainstack2.top();
                Mainstack2.pop();
                string temp2 = Mainstack2.top();
                Mainstack2.pop();
                
                Vector V1(temp);
                Vector V2(temp2);
                
                result = V1 + V2;
            }
            
            if (ops == "-")
            {
                string temp = Mainstack2.top();
                Mainstack2.pop();
                string temp2 = Mainstack2.top();
                Mainstack2.pop();
                
                Vector V1(temp);
                Vector V2(temp2);
                
                result = V1 - V2;
            }
            
            if (ops == "*")
            {
                string temp = Mainstack2.top();
                Mainstack2.pop();
                string temp2 = Mainstack2.top();
                Mainstack2.pop();
                
                Vector V1(temp);
                Vector V2(temp2);
                
                result = V1 * V2;
            }
        }
        
        //for subseqent operations
        if (ops == "+")
        {
            string temp = Mainstack2.top();
            Mainstack2.pop();
            
            Vector V1(temp);
            
            result = result + V1;
        }
        
        if (ops == "-")
        {
            string temp = Mainstack2.top();
            Mainstack2.pop();
            
            Vector V1(temp);
            
            result = result - V1;
        }
        
        if (ops == "*")
        {
            string temp = Mainstack2.top();
            Mainstack2.pop();
            
            Vector V1(temp);
            
            result = result * V1;
        }
    }
    
    //print results to string
    output = result.tostring();
}

void stringanalysis(string input, string output)
{
    //main stack
    Stack<string> MainStack;
    Stack<string> OperatorStack;
    int counter = 0;
    
    //verify string format
    stringstream format(input);
    try
    {
        if (format.get() == '(')
        {
            while(!format.eof())
            {
                if (format.get() == ')')
                {
                    goto here;
                }
            }
            
            //if closing bracket is missing
            throw 1;
        }
        
        //if opening bracket is missing
        throw 1;
    }
    catch (int e)
    {
        cout << "Bad Format Error." << endl;
        
        //if the format is bad, exit program
        exit(0);
    }

//if correct continue here
here:
    stringstream stream(input);
    
    while (!stream.eof())
    {
        //look for 1st vector
        if (stream.get() == '[')
        {
            //return open bracket to stream
            stream.unget();
            
            //grab vector inside brackets
            string Vector;
            getline(stream, Vector, ']');
            
            Vector.append("]");
            
            //sent to vector class for processing
            class Vector temp(Vector);
            
            //return vector back and push to stack
            MainStack.push(temp.tostring());
            
            //keeps track of the number of vectors
            counter++;
            
            //look for the operators and store on separate stack
            if (stream.get() == '+')
            {
                OperatorStack.push("+");
            }
            
            stream.unget();
            
            if (stream.get() == '-')
            {
                OperatorStack.push("-");
            }
            
            stream.unget();
            
            if (stream.get() == '*')
            {
                OperatorStack.push("*");
            }
            
            stream.unget();
        }
    }
    
    //call calculations function
    calculations(MainStack, OperatorStack, counter, output);
}

int main ()
{
    cout << "Vector Calculator" << endl;
    cout << endl;
    cout << "Please enter your correctly formated vector: ";
    
    string userinput; //= "([1,2,3]+[4,5,6])"
    string results;
    
    cin >> userinput;
    
    cout << endl;
    
    stringanalysis(userinput, results);
    
    cout << endl;
    cout << "Your answer is: " << results << endl;
    
    return 0;
}

