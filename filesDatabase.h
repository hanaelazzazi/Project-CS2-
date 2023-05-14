#ifndef filesDatabase_H
#define filesDatabase_H




#include "Database.h"
#include <iostream>

using namespace std;

class filesDatabase :
    public Database
{
    //this a class to use the databse that will save the files
    // it inherits from the databse base class
    // it only has one table
    // the table contain a unique id for each file with its file name and file path
    
private:
    int counter;
    //counter to count how many records in the table in the databse



public:
    filesDatabase();
    //constructor similar to the base databse class constructor
    //it will not take the name of the databse since it will open a speceific databse
    //it will open the databse i created to save the files

    void insertfile(string, string);
    //functino to insert file in the databse taking the file name and file path

    void select(int,string&,string&);
    //function to return the name and path of the file with the specific id

     static int callback(void*, int , char**, char**);
    //function that is needed when executing sql commands

    int getcount();
    //function to return how many fields in the main table in the database


    
    int getNumFields();
    //function to get how many fields in the table , it will be used in the constructor
};

#endif
