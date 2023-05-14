#ifndef plg_H
#define plg_H

#include <iostream>
#include "filesDatabase.h"
#include <vector>
#include <fstream>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

//function  save it in a text folder and return the path  (relevent to qt)(takes name and text)(solve the / situation )
//remove cotations before adding the path




struct linePlg {
    int index;
    string file;
    double percentage;
};

class plg
{

protected:
    filesDatabase Db;

    int numOfLines;
    int numOfWords;
    int numOfchar;
    int numOfParagraphs;

    vector<linePlg> lines;
    vector<string> sentences;
    vector<string> paragraphs;

    


    const int p = 31; // prime number for hashing
    const int m = 1e9 + 9; // large prime for modulo


    

public :
    //constructor(will set the databse)
    plg();
    ~plg();

    //setters n getters


    
    

    void detect(string,string);
    void detectML(string, string);


    bool compare(string, string,double&);
    //to compare sentences together
    


    int rabinKarp(string, string);
    //function implement rabin karp and hashing techniques to check if the word occours in a sentence
    //return 1 if it does and 0 if not
    //will be used in the compare function



    int bruteForce(string, string);
    //function implement brute furse algorithm to check if the word occours in a sentence
    //return 1 if it does and 0 if not
    //will be used in the compare function


    vector<string> getsentences(string);
    vector<string> getparagraphs(string);

    vector<string> split_sentence(string);



    void to_lower(string&);


    bool charOcc(string, char);


    int percentage();
    


    void Filelength(string,int&,int&,int&);
    //function to get the length of the file (in lines)


    void insert(linePlg);

    void printAIlines( string&);
    //should be used immediatly after Ai detection function


    void printLines(string&);
    //should be used after default or prefered


    void sortLines();


};


#endif
