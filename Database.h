#ifndef Database_H
#define Database_H



#include <iostream>
#include <sqlite3.h>

using namespace std;
class Database
{
protected:
    sqlite3* db;
    //pointer to databse
    //will be used to control the databse
    

public:

    Database();
    //default constructor

    Database(const char * );
    //constructor that will take the name of the databse then open it
    
};

#endif
