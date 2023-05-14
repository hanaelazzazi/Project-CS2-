#include "Database.h"
#include <sqlite3.h>


Database::Database(const char* dbName) {

    
    char* zErrMsg = 0;
    int rc = sqlite3_open(dbName, &db);
    //function from sql library to open database
    //it assigns the pointer db to this databse
    //if the name of the databse was not found it will create one with this name
    

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }
    else {
        cout << "Opened database successfully." << endl;
    }
    //this is an if funtion to check if databse opened properly otherwise it will cout an error message
}


Database::Database() {
    //no implementation i just created a default constructor because other wise it gives a complier error

}



