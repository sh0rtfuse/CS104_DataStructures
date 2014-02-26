//
//  main.cpp
//  HW2_LinkedLists
//
//  Raymond Dam
//

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class lists                                                         //data structure of each item (node) of the list
{
    public:
        string data;
        lists *next, *previous;
};

lists *beginning, *ending;                                          //tracks the two ends of the list

void add (string input)
{
    lists *temp = new lists;                                        //initialize temporary node to store new data
    
    temp->data = input;                                             //store input into data inside the node
    
    temp->next = NULL;                                              //the next node hasn't be created yet so set its pointer to null
    
    temp->previous = ending;                                        //as the lastest node its other end points back to the 1st node at the end
    
    if (beginning == NULL)                                          //when node is the head, set head and tail node to the current node
    {
        beginning = ending = temp;
    }
    
    else                                                            //otherwise, set current node as the tail node
    {
        ending->next = temp;
        
        ending = temp;
    }
    
    temp = NULL;
    
    delete temp;                                                    //clean up!
}

void remove (lists *temp)
{
    if (temp == beginning)                                          //if head node, sets pointer to bypass deleted node
    {
		beginning = temp->next;
    }
    
	else
    {
        temp->previous->next = temp->next;
    }
    
	if (temp == ending)                                             //if tail node, sets pointer to bypass deleted node
    {
		ending = temp->previous;
    }
    
	else
    {
        temp->next->previous = temp->previous;
    }
    
    temp = NULL;
    
    delete temp;                                                    //clean up!
}

void inputfile (string filename)
{
    ifstream filein(filename.c_str());                              //reads in the file
    
    while (!filein.eof())                                           //while loop to keep the stream going until end of file
    {
        string temp;                                                //temporary variable to hold data
        
        getline(filein,temp);                                       //grabs entire line
        
        add(temp);                                                  //adds the line to a linked list
    }
    
    filein.close();                                                 //closes stream
}

lists *theendisthebeginningistheend(lists *input)                   //Smashing Pumpkin fans?
{
    if (input->next == NULL)                                        //base case: we start from the head and go until next pointer points to nothing
    {
        return input;
    }
    
    else
    {
        lists *temp1 = input->next;                                 //advance to 2nd element
        input->next = NULL;                                         //remove link
        lists *temp2 = theendisthebeginningistheend(temp1);         //flip elements recursively
        temp1->next = input;                                        //relink lists
        
        return temp2;                                               //return reversed result
    }
}
 
int main ()
{
    string input;
    
                                                                    //ask user to enter name of input file
    cout << "Please enter the name of your input file." << endl;
    cout << "User Entry: ";
    cin >> input;
    
    beginning = ending = NULL;
    
    inputfile(input);                                               //call file io function to read in and store strings
    
    lists *recursion = theendisthebeginningistheend(beginning);     //reverse strings
    
    for (lists *i = recursion; i != NULL; i = i->next)              //printout reversed strings
    {
        cout << i->data << endl;
    }
    
    return 0;
}
