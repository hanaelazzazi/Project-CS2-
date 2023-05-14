#include "filesDatabase.h"
#include "string"


 int filesDatabase::callback(void* data, int argc, char** argv, char** azColName) {
     //we got this function from the internet it will be used in the select function to retrive the adata
    // Save the first column (name) in the data pointer
    string* name = static_cast<string*>(data);
    *name = argv[0];
    return 0;
}


int filesDatabase::getcount() {
    //returns the counter of how many files in the table
    return counter;
}



filesDatabase::filesDatabase() {
    //this is the constructor for the class
    //it will connect the sqlite3 pointer(db) to our pre created databse
    //the databse already includes a table called files

    char* zErrMsg = 0;
    int rc = sqlite3_open("/Users/hanaelazzazi/Desktop/Spring 2023/CS 2/Project and Paper/Database/p.db", &db);
    //function from sql library to open database
    //it assigns the pointer db to this databse


    if (rc) {
   
        cerr << "Can't open the files database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        exit(1);
    }
    else {
        cout << "Files databse Opened successfully." << endl;
    }
    //this is an if funtion to check if databse opened properly otherwise it will cout an error message


    counter = getNumFields();
    //set the counter to the number of files in the database

}


void filesDatabase::insertfile(string name, string path) {
      //function to insert File in the databse
    counter++;
    //increments the counter

    char* zErrMsg = 0;
    int rc;
    string sql;


     sql = "INSERT INTO FILES (ID, NAME, PATH) VALUES (?, ?, ?)";
     //sql comand to prepare the filed where the data will be inserted

     sqlite3_stmt* stmt;

     rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);//will prepare the field or row which will take the values

     if (rc != SQLITE_OK) {//to check if preperation was successful
         cerr << "Error preparing SQL statement: " << sqlite3_errmsg(db) << endl;
     }


   

     sqlite3_bind_int(stmt, 1, counter);
     sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);
     sqlite3_bind_text(stmt, 3, path.c_str(), -1, SQLITE_TRANSIENT);
     //it will then input the counter(id), name and path



     rc = sqlite3_step(stmt);


     if (rc != SQLITE_DONE) {//will check if the file was inserted properly
         cerr << "Error executing SQL statement: " << sqlite3_errmsg(db) << endl;
     }

     // Finalize the statement
     sqlite3_finalize(stmt);
}





void filesDatabase::select(int id, string& name, string& path) {
    //function to get the name and path of the file with the id passed to the function
    //name and path will be returned by pass by refrence


    string sql = "SELECT NAME FROM FILES WHERE ID = " + to_string(id) + ";";
    // sql command it includes a function that will turn the id into a string and then return the name of the file in this string

   
   
    char* errmsg = 0;
    int rc = sqlite3_exec(db, sql.c_str(), callback, &name, &errmsg);
    //name string will be passed by refrence here it will store the name

    if (rc != SQLITE_OK) {//checks if the execution was done properly
        cerr << "SQL error: " << errmsg << endl;
        sqlite3_free(errmsg);
      
      
    }
  
 
     sql = "SELECT PATH FROM FILES WHERE ID = " + to_string(id) + ";";
     // sql command it includes a function that will turn the id into a string and then return the path of the file in this string

   
    rc = sqlite3_exec(db, sql.c_str(), callback, &path, &errmsg);
    //path string will be passed by refrence here it will store the path of the file

    if (rc != SQLITE_OK) {//checks if the execution was done properly
        cerr << "SQL error: " << errmsg << endl;
        sqlite3_free(errmsg);
     
    }

    // Close the database
  
   
}


int filesDatabase::getNumFields() {//function to return how many rows in a table

    sqlite3_stmt* stmt;
    const char* query = "SELECT COUNT(*) FROM FILES";
    //command that gets how many rows/fields in the databse named files
    int numRows = 0;

    char* finalQuery = sqlite3_mprintf(query, "FILES"); // format query with table name

    if (sqlite3_prepare_v2(db, finalQuery, -1, &stmt, NULL) != SQLITE_OK) {
        return -1; // Error preparing statement
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        numRows = sqlite3_column_int(stmt, 0); // Get the count from the first column
    }

    sqlite3_finalize(stmt);
    sqlite3_free(finalQuery);
   
    return numRows;
}
